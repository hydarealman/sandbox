SET NAMES utf8mb4;
USE OrderDB;

CREATE INDEX idx_product_name ON Product(productName);
CREATE INDEX idx_orderdetail_product ON OrderDetail(productNo);
CREATE INDEX idx_orderdetail_order ON OrderDetail(orderNo);
CREATE INDEX idx_ordermaster_employee ON OrderMaster(employeeNo);
CREATE INDEX idx_ordermaster_customer ON OrderMaster(customerNo);

SELECT '实验7：查询1执行计划-酷睿四核i5-6500销售情况' AS section;
EXPLAIN FORMAT=TRADITIONAL
SELECT e.employeeName,
       CASE e.sex WHEN 'M' THEN '男' ELSE '女' END AS sex,
       om.orderDate,
       od.quantity,
       od.quantity * od.price AS amount
FROM OrderDetail od
JOIN OrderMaster om ON od.orderNo = om.orderNo
JOIN Employee e ON om.employeeNo = e.employeeNo
WHERE od.productNo = (
  SELECT productNo
  FROM Product
  WHERE productName = '酷睿四核i5-6500'
);

SELECT e.employeeName,
       CASE e.sex WHEN 'M' THEN '男' ELSE '女' END AS sex,
       om.orderDate,
       od.quantity,
       od.quantity * od.price AS amount
FROM OrderDetail od
JOIN OrderMaster om ON od.orderNo = om.orderNo
JOIN Employee e ON om.employeeNo = e.employeeNo
WHERE od.productNo = (
  SELECT productNo
  FROM Product
  WHERE productName = '酷睿四核i5-6500'
);

SELECT '实验7：查询2执行计划-每个员工销售记录' AS section;
EXPLAIN FORMAT=TRADITIONAL
SELECT e.employeeNo,
       e.employeeName,
       CASE e.sex WHEN 'M' THEN '男' ELSE '女' END AS sex,
       p.productName,
       od.quantity,
       od.price,
       od.quantity * od.price AS amount,
       DATE_FORMAT(om.orderDate, '%Y-%m-%d') AS orderDate
FROM Employee e
JOIN OrderMaster om ON e.employeeNo = om.employeeNo
JOIN OrderDetail od ON om.orderNo = od.orderNo
JOIN Product p ON od.productNo = p.productNo
ORDER BY e.employeeNo;

SELECT e.employeeNo,
       e.employeeName,
       CASE e.sex WHEN 'M' THEN '男' ELSE '女' END AS sex,
       p.productName,
       od.quantity,
       od.price,
       od.quantity * od.price AS amount,
       DATE_FORMAT(om.orderDate, '%Y-%m-%d') AS orderDate
FROM Employee e
JOIN OrderMaster om ON e.employeeNo = om.employeeNo
JOIN OrderDetail od ON om.orderNo = od.orderNo
JOIN Product p ON od.productNo = p.productNo
ORDER BY e.employeeNo;

SELECT '实验7问题简答' AS section;
SELECT '优化原则：只取必要列；优先使用等值连接与可索引谓词；为连接列、筛选列和排序列建立合适索引；避免在索引列上包裹函数；用EXPLAIN观察访问类型、候选索引、扫描行数和Extra信息，再根据瓶颈调整SQL或索引。' AS answer;
