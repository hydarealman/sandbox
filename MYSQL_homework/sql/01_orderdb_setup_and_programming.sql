SET NAMES utf8mb4;

DROP DATABASE IF EXISTS OrderDB;
CREATE DATABASE OrderDB DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci;
USE OrderDB;

CREATE TABLE ProductClass (
  classNo CHAR(3) PRIMARY KEY,
  className VARCHAR(40) NOT NULL UNIQUE
) ENGINE=InnoDB;

CREATE TABLE Product (
  productNo CHAR(9) PRIMARY KEY,
  productName VARCHAR(80) NOT NULL,
  classNo CHAR(3) NOT NULL,
  productPrice DECIMAL(10,2) NOT NULL CHECK (productPrice > 0),
  quantity INT NOT NULL DEFAULT 0 CHECK (quantity >= 0),
  lowQuantity INT NOT NULL DEFAULT 5 CHECK (lowQuantity >= 0),
  CONSTRAINT fk_product_class
    FOREIGN KEY (classNo) REFERENCES ProductClass(classNo)
) ENGINE=InnoDB;

CREATE TABLE Employee (
  employeeNo CHAR(8) PRIMARY KEY,
  employeeName VARCHAR(30) NOT NULL,
  sex CHAR(1) NOT NULL CHECK (sex IN ('M','F')),
  department VARCHAR(30) NOT NULL,
  headship VARCHAR(30) NOT NULL,
  hireDate DATE NOT NULL,
  birthday DATE NULL,
  salary DECIMAL(10,2) NOT NULL CHECK (salary >= 0),
  address VARCHAR(100),
  CONSTRAINT chk_employee_no CHECK (employeeNo REGEXP '^E[0-9]{7}$')
) ENGINE=InnoDB;

CREATE TABLE Customer (
  customerNo CHAR(9) PRIMARY KEY,
  customerName VARCHAR(80) NOT NULL,
  address VARCHAR(120),
  zip VARCHAR(10),
  phone VARCHAR(30)
) ENGINE=InnoDB;

CREATE TABLE OrderMaster (
  orderNo CHAR(9) PRIMARY KEY,
  customerNo CHAR(9) NOT NULL,
  employeeNo CHAR(8) NULL,
  orderDate DATE NOT NULL,
  orderSum DECIMAL(12,2) NOT NULL DEFAULT 0,
  CONSTRAINT fk_ordermaster_customer
    FOREIGN KEY (customerNo) REFERENCES Customer(customerNo)
    ON UPDATE CASCADE ON DELETE RESTRICT,
  CONSTRAINT fk_ordermaster_employee
    FOREIGN KEY (employeeNo) REFERENCES Employee(employeeNo)
    ON UPDATE CASCADE ON DELETE SET NULL
) ENGINE=InnoDB;

CREATE TABLE OrderDetail (
  orderNo CHAR(9) NOT NULL,
  productNo CHAR(9) NOT NULL,
  quantity INT NOT NULL CHECK (quantity > 0),
  price DECIMAL(10,2) NOT NULL CHECK (price > 0),
  PRIMARY KEY (orderNo, productNo),
  CONSTRAINT fk_detail_order
    FOREIGN KEY (orderNo) REFERENCES OrderMaster(orderNo)
    ON UPDATE CASCADE ON DELETE CASCADE,
  CONSTRAINT fk_detail_product
    FOREIGN KEY (productNo) REFERENCES Product(productNo)
    ON UPDATE CASCADE ON DELETE RESTRICT
) ENGINE=InnoDB;

INSERT INTO ProductClass VALUES
('C01','计算机配件'),
('C02','智能穿戴'),
('C03','办公设备'),
('C04','存储设备'),
('C05','网络设备');

INSERT INTO Product VALUES
('P20200001','酷睿四核i5-6500','C01',1450.00,80,10),
('P20200002','酷睿四核I7-7700k','C01',2499.00,50,8),
('P20200003','华硕主板Z270','C01',899.00,60,8),
('P20200004','金士顿16G内存','C04',329.00,120,20),
('P20200005','西部数据1T硬盘','C04',399.00,90,15),
('P20210001','华为手环6','C02',299.00,110,20),
('P20210002','小米手环7','C02',239.00,100,20),
('P20210003','罗技无线鼠标','C03',129.00,150,30),
('P20210004','HP激光打印机','C03',1299.00,35,5),
('P20210005','TP-LINK千兆路由器','C05',199.00,100,20),
('P20210006','戴尔显示器24寸','C03',899.00,55,8),
('P20210007','酷睿四核i7散热器','C01',159.00,70,10);

INSERT INTO Employee VALUES
('E2019001','李强','M','业务科','业务员','2019-03-01','1987-05-12',6200.00,'上海市浦东新区'),
('E2019002','张小梅','F','业务科','业务员','2019-03-01','1988-11-20',6100.00,'南昌市红谷滩新区'),
('E2020001','王磊','M','技术科','工程师','2020-01-15','1990-08-03',7800.00,'桂林市七星区'),
('E2020002','陈晨','F','财务科','会计','2020-02-10',NULL,6900.00,'上海市徐汇区'),
('E2020003','刘洋','M','业务科','业务员','2020-03-18','1987-12-05',6500.00,'长沙市岳麓区'),
('E2020004','张梅','F','业务科','业务员','2020-03-20','1988-02-14',6300.00,'南昌市青山湖区'),
('E2020005','赵敏','F','业务科','经理','2020-05-01','1985-07-26',9200.00,'广州市天河区'),
('E2021001','周杰','M','仓储科','管理员','2021-01-08','1992-04-01',5600.00,'桂林市雁山区');

INSERT INTO Customer VALUES
('C20200001','上海海天有限公司','上海市浦东新区','200120','021-66000001'),
('C20200002','南昌红谷有限责任公司','南昌市红谷滩新区','330038','0791-88000002'),
('C20200003','桂林电子有限公司','桂林市七星区','541004','0773-5800003'),
('C20200004','北京智联科技有限公司','北京市海淀区','100080','010-68000004'),
('C20210001','合生元有限公司','广州市天河区','510630','020-38000005'),
('C20210002','广州南方有限集团','广州市越秀区','510030','020-38000006'),
('C20210003','成都创客科技','成都市高新区','610041','028-86000007'),
('C20210004','深圳鹏程贸易','深圳市南山区','518052','0755-86000008'),
('C20220001','杭州未来公司','杭州市西湖区','310012','0571-86000009');

INSERT INTO OrderMaster(orderNo, customerNo, employeeNo, orderDate) VALUES
('O20200001','C20200001','E2019001','2020-03-05'),
('O20200002','C20200002','E2019002','2020-03-07'),
('O20200003','C20200003','E2020003','2020-03-12'),
('O20200004','C20200004','E2019001','2020-04-02'),
('O20200005','C20210001','E2020004','2020-05-09'),
('O20200006','C20210002','E2020005','2020-06-15'),
('O20200007','C20200001','E2019001','2020-07-20'),
('O20200008','C20200002','E2020003','2020-09-11'),
('O20200009','C20210003','E2019002','2020-10-18'),
('O20210001','C20210004','E2020004','2021-01-22'),
('O20210002','C20210001','E2020005','2021-03-16'),
('O20210003','C20200004','E2020003','2021-06-30'),
('O20210004','C20200003','E2019002','2021-08-08'),
('O20220001','C20210002','E2020004','2022-01-10'),
('O20220002','C20200001','E2020005','2022-05-19');

INSERT INTO OrderDetail VALUES
('O20200001','P20200001',2,1450.00),
('O20200001','P20200004',5,329.00),
('O20200001','P20210005',4,199.00),
('O20200002','P20200002',2,2499.00),
('O20200002','P20210001',10,299.00),
('O20200002','P20210002',8,239.00),
('O20200003','P20200003',3,899.00),
('O20200003','P20210003',12,129.00),
('O20200004','P20200001',1,1450.00),
('O20200004','P20210004',2,1299.00),
('O20200005','P20210001',6,299.00),
('O20200005','P20210006',3,899.00),
('O20200006','P20200005',10,399.00),
('O20200006','P20210005',15,199.00),
('O20200007','P20200002',1,2499.00),
('O20200007','P20200004',8,329.00),
('O20200008','P20210002',12,239.00),
('O20200008','P20210003',20,129.00),
('O20200009','P20200002',3,2499.00),
('O20200009','P20210001',5,299.00),
('O20210001','P20200001',2,1450.00),
('O20210001','P20210006',2,899.00),
('O20210002','P20210004',1,1299.00),
('O20210002','P20210005',10,199.00),
('O20210003','P20200003',4,899.00),
('O20210003','P20210002',6,239.00),
('O20210004','P20200005',8,399.00),
('O20210004','P20210003',10,129.00),
('O20220001','P20210001',15,299.00),
('O20220001','P20210002',15,239.00),
('O20220002','P20200002',1,2499.00),
('O20220002','P20210007',20,159.00);

UPDATE OrderMaster om
JOIN (
  SELECT orderNo, SUM(quantity * price) AS amount
  FROM OrderDetail
  GROUP BY orderNo
) d ON om.orderNo = d.orderNo
SET om.orderSum = d.amount;

SELECT '实验1：MySQL运行环境与OrderDB初始化' AS section;
SELECT VERSION() AS mysql_version, DATABASE() AS current_database;
SHOW TABLES;

SELECT '实验1：求252和105的最大公约数与最小公倍数' AS section;
WITH RECURSIVE gcd_calc(a,b) AS (
  SELECT 252, 105
  UNION ALL
  SELECT b, MOD(a,b) FROM gcd_calc WHERE b <> 0
)
SELECT 252 AS first_number,
       105 AS second_number,
       a AS gcd_value,
       252 * 105 / a AS lcm_value
FROM gcd_calc
WHERE b = 0;

SELECT '实验1：0到999之间的水仙花数' AS section;
WITH RECURSIVE nums(n) AS (
  SELECT 0
  UNION ALL
  SELECT n + 1 FROM nums WHERE n < 999
)
SELECT GROUP_CONCAT(n ORDER BY n SEPARATOR ', ') AS narcissistic_numbers
FROM nums
WHERE n = POW(FLOOR(n / 100), 3)
        + POW(FLOOR(MOD(n,100) / 10), 3)
        + POW(MOD(n,10), 3);

SELECT '实验1：分数数列前20项之和' AS section;
WITH RECURSIVE fraction_series(n, numerator, denominator) AS (
  SELECT 1, CAST(2 AS DECIMAL(30,10)), CAST(1 AS DECIMAL(30,10))
  UNION ALL
  SELECT n + 1, numerator + denominator, numerator
  FROM fraction_series
  WHERE n < 20
)
SELECT ROUND(SUM(numerator / denominator), 6) AS sum_first_20_terms
FROM fraction_series;

SELECT '实验1：OrderDB基础数据量' AS section;
SELECT
  (SELECT COUNT(*) FROM ProductClass) AS product_classes,
  (SELECT COUNT(*) FROM Product) AS products,
  (SELECT COUNT(*) FROM Employee) AS employees,
  (SELECT COUNT(*) FROM Customer) AS customers,
  (SELECT COUNT(*) FROM OrderMaster) AS orders,
  (SELECT COUNT(*) FROM OrderDetail) AS order_details;
