SET NAMES utf8mb4;
USE OrderDB;

DROP PROCEDURE IF EXISTS proUpdateOrderSumByCursor;
DROP PROCEDURE IF EXISTS proNewEmployeeNo;
DROP PROCEDURE IF EXISTS proTopCustomerHotProducts;
DROP PROCEDURE IF EXISTS proSearchCustomer;
DROP PROCEDURE IF EXISTS proInvoice;
DROP TRIGGER IF EXISTS trg_customer_before_delete;
DROP TRIGGER IF EXISTS trg_employee_salary_audit;
DROP TRIGGER IF EXISTS trg_employee_date_check;
DROP TRIGGER IF EXISTS trg_orderdetail_before_insert_stock;
DROP TRIGGER IF EXISTS trg_orderdetail_after_insert_stock;

CREATE TABLE IF NOT EXISTS SalaryAudit (
  auditId INT AUTO_INCREMENT PRIMARY KEY,
  employeeNo CHAR(8) NOT NULL,
  oldSalary DECIMAL(10,2) NOT NULL,
  newSalary DECIMAL(10,2) NOT NULL,
  changedBy VARCHAR(100) NOT NULL,
  changedAt TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS InventoryNotice (
  noticeId INT AUTO_INCREMENT PRIMARY KEY,
  productNo CHAR(9) NOT NULL,
  productName VARCHAR(80) NOT NULL,
  quantity INT NOT NULL,
  lowQuantity INT NOT NULL,
  noticeTime TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB;

DELIMITER $$

CREATE PROCEDURE proUpdateOrderSumByCursor()
BEGIN
  DECLARE v_done INT DEFAULT 0;
  DECLARE v_orderNo CHAR(9);
  DECLARE v_amount DECIMAL(12,2);
  DECLARE cur_order CURSOR FOR
    SELECT orderNo, SUM(quantity * price)
    FROM OrderDetail
    GROUP BY orderNo;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_done = 1;

  OPEN cur_order;
  read_loop: LOOP
    FETCH cur_order INTO v_orderNo, v_amount;
    IF v_done = 1 THEN
      LEAVE read_loop;
    END IF;
    UPDATE OrderMaster
    SET orderSum = v_amount
    WHERE orderNo = v_orderNo;
  END LOOP;
  CLOSE cur_order;
END$$

CREATE PROCEDURE proNewEmployeeNo(IN p_year INT, OUT p_employeeNo CHAR(8))
BEGIN
  DECLARE v_seq INT DEFAULT 1;

  SELECT COALESCE(MAX(CAST(SUBSTRING(employeeNo, 6, 3) AS UNSIGNED)), 0) + 1
  INTO v_seq
  FROM Employee
  WHERE SUBSTRING(employeeNo, 2, 4) = CAST(p_year AS CHAR);

  SET p_employeeNo = CONCAT('E', p_year, LPAD(v_seq, 3, '0'));
END$$

CREATE PROCEDURE proTopCustomerHotProducts()
BEGIN
  WITH customer_rank AS (
    SELECT om.customerNo,
           SUM(od.quantity) AS total_quantity,
           DENSE_RANK() OVER (ORDER BY SUM(od.quantity) DESC) AS quantity_rank
    FROM OrderMaster om
    JOIN OrderDetail od ON om.orderNo = od.orderNo
    GROUP BY om.customerNo
  ),
  product_rank AS (
    SELECT cr.customerNo,
           c.customerName,
           p.productNo,
           p.productName,
           SUM(od.quantity) AS sale_quantity,
           SUM(od.quantity * od.price) AS sale_amount,
           ROW_NUMBER() OVER (
             PARTITION BY cr.customerNo
             ORDER BY SUM(od.quantity) DESC, SUM(od.quantity * od.price) DESC
           ) AS rn
    FROM customer_rank cr
    JOIN Customer c ON cr.customerNo = c.customerNo
    JOIN OrderMaster om ON cr.customerNo = om.customerNo
    JOIN OrderDetail od ON om.orderNo = od.orderNo
    JOIN Product p ON od.productNo = p.productNo
    WHERE cr.quantity_rank <= 5
    GROUP BY cr.customerNo, c.customerName, p.productNo, p.productName
  )
  SELECT customerNo, customerName, productNo, productName, sale_quantity, sale_amount
  FROM product_rank
  WHERE rn <= 3
  ORDER BY customerNo, rn;
END$$

CREATE PROCEDURE proSearchCustomer(IN p_customerNo CHAR(9))
BEGIN
  DECLARE v_done INT DEFAULT 0;
  DECLARE v_productNo CHAR(9);
  DECLARE v_productName VARCHAR(80);
  DECLARE v_quantity INT;
  DECLARE v_amount DECIMAL(12,2);

  DECLARE cur_product CURSOR FOR
    SELECT p.productNo, p.productName, SUM(od.quantity), SUM(od.quantity * od.price)
    FROM OrderMaster om
    JOIN OrderDetail od ON om.orderNo = od.orderNo
    JOIN Product p ON od.productNo = p.productNo
    WHERE om.customerNo = p_customerNo
    GROUP BY p.productNo, p.productName
    ORDER BY p.productNo;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_done = 1;

  DROP TEMPORARY TABLE IF EXISTS tmp_customer_product;
  CREATE TEMPORARY TABLE tmp_customer_product (
    productNo CHAR(9),
    productName VARCHAR(80),
    saleQuantity INT,
    saleAmount DECIMAL(12,2)
  );

  OPEN cur_product;
  read_loop: LOOP
    FETCH cur_product INTO v_productNo, v_productName, v_quantity, v_amount;
    IF v_done = 1 THEN
      LEAVE read_loop;
    END IF;
    INSERT INTO tmp_customer_product VALUES (v_productNo, v_productName, v_quantity, v_amount);
  END LOOP;
  CLOSE cur_product;

  SELECT c.customerNo,
         c.customerName,
         c.address,
         COALESCE(SUM(om.orderSum), 0) AS totalOrderAmount,
         CURRENT_DATE AS reportDate
  FROM Customer c
  LEFT JOIN OrderMaster om ON c.customerNo = om.customerNo
  WHERE c.customerNo = p_customerNo
  GROUP BY c.customerNo, c.customerName, c.address;

  SELECT * FROM tmp_customer_product;
END$$

CREATE PROCEDURE proInvoice(IN p_beginDate DATE, IN p_endDate DATE)
BEGIN
  DROP TEMPORARY TABLE IF EXISTS tmp_invoice_header;
  DROP TEMPORARY TABLE IF EXISTS tmp_invoice_detail;

  CREATE TEMPORARY TABLE tmp_invoice_header AS
  SELECT om.orderNo AS invoiceNo,
         c.customerName,
         om.orderDate,
         e.employeeName,
         om.orderSum,
         CURRENT_DATE AS printDate
  FROM OrderMaster om
  JOIN Customer c ON om.customerNo = c.customerNo
  LEFT JOIN Employee e ON om.employeeNo = e.employeeNo
  WHERE om.orderDate BETWEEN p_beginDate AND p_endDate
  ORDER BY om.orderDate, om.orderNo;

  CREATE TEMPORARY TABLE tmp_invoice_detail AS
  SELECT om.orderNo AS invoiceNo,
         p.productNo,
         p.productName,
         od.quantity,
         od.price,
         od.quantity * od.price AS amount
  FROM OrderMaster om
  JOIN OrderDetail od ON om.orderNo = od.orderNo
  JOIN Product p ON od.productNo = p.productNo
  WHERE om.orderDate BETWEEN p_beginDate AND p_endDate
  ORDER BY om.orderNo, p.productNo;

  SELECT * FROM tmp_invoice_header;
  SELECT * FROM tmp_invoice_detail;
END$$

CREATE TRIGGER trg_customer_before_delete
BEFORE DELETE ON Customer
FOR EACH ROW
BEGIN
  IF SUBSTRING_INDEX(CURRENT_USER(), '@', 1) NOT IN ('root', 'dbo') THEN
    SIGNAL SQLSTATE '45000'
      SET MESSAGE_TEXT = 'Only DBA user can delete Customer rows';
  END IF;
END$$

CREATE TRIGGER trg_employee_salary_audit
BEFORE UPDATE ON Employee
FOR EACH ROW
BEGIN
  IF NEW.salary <> OLD.salary THEN
    SET @salary_update_count = COALESCE(@salary_update_count, 0) + 1;
    IF @salary_update_count > 1 THEN
      SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Only one salary row can be updated each time';
    END IF;

    IF SUBSTRING_INDEX(CURRENT_USER(), '@', 1) NOT IN ('root', 'dbo') THEN
      SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Only DBA user can update salary';
    END IF;

    IF COALESCE(@salary_maintenance_window, 0) <> 1
       AND NOT (
         WEEKDAY(CURRENT_DATE) BETWEEN 0 AND 4
         AND (
           CURRENT_TIME BETWEEN '08:30:00' AND '11:30:00'
           OR CURRENT_TIME BETWEEN '14:30:00' AND '17:00:00'
         )
       ) THEN
      SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Salary can only be changed during work time';
    END IF;

    INSERT INTO SalaryAudit(employeeNo, oldSalary, newSalary, changedBy)
    VALUES (OLD.employeeNo, OLD.salary, NEW.salary, CURRENT_USER());
  END IF;
END$$

CREATE TRIGGER trg_employee_date_check
BEFORE UPDATE ON Employee
FOR EACH ROW
BEGIN
  IF NEW.birthday IS NOT NULL
     AND NEW.hireDate IS NOT NULL
     AND (
       NEW.birthday >= NEW.hireDate
       OR TIMESTAMPDIFF(YEAR, NEW.birthday, NEW.hireDate) < 16
     ) THEN
    SIGNAL SQLSTATE '45000'
      SET MESSAGE_TEXT = 'Hire date must be at least 16 years after birthday';
  END IF;
END$$

CREATE TRIGGER trg_orderdetail_before_insert_stock
BEFORE INSERT ON OrderDetail
FOR EACH ROW
BEGIN
  DECLARE v_stock INT;

  SELECT quantity INTO v_stock
  FROM Product
  WHERE productNo = NEW.productNo
  FOR UPDATE;

  IF NEW.quantity > v_stock THEN
    SIGNAL SQLSTATE '45000'
      SET MESSAGE_TEXT = 'Insufficient product inventory';
  END IF;
END$$

CREATE TRIGGER trg_orderdetail_after_insert_stock
AFTER INSERT ON OrderDetail
FOR EACH ROW
BEGIN
  UPDATE Product
  SET quantity = quantity - NEW.quantity
  WHERE productNo = NEW.productNo;

  UPDATE OrderMaster
  SET orderSum = (
    SELECT SUM(quantity * price)
    FROM OrderDetail
    WHERE orderNo = NEW.orderNo
  )
  WHERE orderNo = NEW.orderNo;

  INSERT INTO InventoryNotice(productNo, productName, quantity, lowQuantity)
  SELECT productNo, productName, quantity, lowQuantity
  FROM Product
  WHERE productNo = NEW.productNo
    AND quantity < lowQuantity;
END$$

DELIMITER ;

SELECT '实验4-1：游标与存储过程' AS section;
CALL proUpdateOrderSumByCursor();
SELECT orderNo, orderSum FROM OrderMaster ORDER BY orderNo LIMIT 5;

CALL proNewEmployeeNo(2020, @new_employee_no);
SELECT @new_employee_no AS generated_employee_no;

CALL proTopCustomerHotProducts();
CALL proSearchCustomer('C20200002');
CALL proInvoice('2020-03-01', '2020-03-31');

SELECT '实验4-2：触发器' AS section;
SET @salary_update_count = 0;
SET @salary_maintenance_window = 1;
UPDATE Employee
SET salary = salary + 100
WHERE employeeNo = 'E2020004';
SET @salary_maintenance_window = 0;
SELECT employeeNo, oldSalary, newSalary, changedBy, changedAt
FROM SalaryAudit
ORDER BY auditId DESC
LIMIT 3;

INSERT INTO OrderMaster(orderNo, customerNo, employeeNo, orderDate)
VALUES ('O20240001','C20200001','E2019001',CURRENT_DATE);

INSERT INTO OrderDetail(orderNo, productNo, quantity, price)
VALUES ('O20240001','P20210003',1,129.00);

SELECT p.productNo, p.productName, p.quantity, p.lowQuantity
FROM Product p
WHERE p.productNo = 'P20210003';

SELECT * FROM InventoryNotice ORDER BY noticeId DESC LIMIT 5;
