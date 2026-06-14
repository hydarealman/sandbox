SET NAMES utf8mb4;
USE OrderDB;

DELETE FROM OrderDetail WHERE orderNo = 'O20220816';
DELETE FROM OrderMaster WHERE orderNo = 'O20220816';
DELETE FROM Customer WHERE customerNo = 'C20220816';

SELECT '实验8：事务1-新客户注册' AS section;
START TRANSACTION;
INSERT INTO Customer(customerNo, customerName, address, zip, phone)
VALUES ('C20220816','柳州新客户有限公司','柳州市城中区','545001','0772-2160816');
COMMIT;

SELECT customerNo, customerName, address
FROM Customer
WHERE customerNo = 'C20220816';

SELECT '实验8：事务2-新订单登记并享受2%优惠' AS section;
START TRANSACTION;
INSERT INTO OrderMaster(orderNo, customerNo, employeeNo, orderDate)
VALUES ('O20220816','C20220816','E2020004','2022-08-16');

SELECT ROUND(productPrice * 0.98, 2) INTO @price_p20210003
FROM Product
WHERE productNo = 'P20210003';

SELECT ROUND(productPrice * 0.98, 2) INTO @price_p20210002
FROM Product
WHERE productNo = 'P20210002';

INSERT INTO OrderDetail(orderNo, productNo, quantity, price)
VALUES ('O20220816', 'P20210003', 3, @price_p20210003);

INSERT INTO OrderDetail(orderNo, productNo, quantity, price)
VALUES ('O20220816', 'P20210002', 2, @price_p20210002);
COMMIT;

SELECT om.orderNo, om.customerNo, om.orderDate, om.orderSum
FROM OrderMaster om
WHERE om.orderNo = 'O20220816';

SELECT od.orderNo, od.productNo, p.productName, od.quantity, od.price, od.quantity * od.price AS amount
FROM OrderDetail od
JOIN Product p ON od.productNo = p.productNo
WHERE od.orderNo = 'O20220816';

SELECT '实验8：事务3-业务员E2020003离职，删除相关信息' AS section;
START TRANSACTION;
UPDATE OrderMaster
SET employeeNo = NULL
WHERE employeeNo = 'E2020003';

DELETE FROM Employee
WHERE employeeNo = 'E2020003';
COMMIT;

SELECT COUNT(*) AS employee_E2020003_count
FROM Employee
WHERE employeeNo = 'E2020003';

SELECT orderNo, employeeNo
FROM OrderMaster
WHERE employeeNo IS NULL
ORDER BY orderNo;

SELECT '实验8：隔离级别并发演示请运行 scripts/run_transaction_isolation_demo.py' AS section;
