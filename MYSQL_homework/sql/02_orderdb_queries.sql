SET NAMES utf8mb4;
USE OrderDB;

UPDATE OrderMaster om
JOIN (
  SELECT orderNo, SUM(quantity * price) AS sum2
  FROM OrderDetail
  GROUP BY orderNo
) d ON om.orderNo = d.orderNo
SET om.orderSum = d.sum2;

SELECT '实验2-1：单表查询与聚合' AS section;

SELECT '2-1(1) 名称中含有“有限”的客户' AS question;
SELECT customerName, address
FROM Customer
WHERE customerName LIKE '%有限%';

SELECT '2-1(2) 姓张且姓名最后一字为梅的员工' AS question;
SELECT employeeNo, employeeName, department, headship
FROM Employee
WHERE employeeName LIKE '张%梅';

SELECT '2-1(3) 住址含上海或南昌的员工' AS question;
SELECT employeeName,
       department,
       headship,
       address,
       IFNULL(DATE_FORMAT(birthday, '%Y-%m-%d'), '不详') AS birthday,
       CASE sex WHEN 'M' THEN '男' ELSE '女' END AS sex
FROM Employee
WHERE address LIKE '%上海%' OR address LIKE '%南昌%';

SELECT '2-1(4) 客户编号不在C20200003到C20210002之间的客户' AS question;
SELECT customerNo, customerName, address
FROM Customer
WHERE customerNo NOT BETWEEN 'C20200003' AND 'C20210002';

SELECT '2-1(5) 订单金额最高的前10%订单' AS question;
WITH ranked_orders AS (
  SELECT om.*,
         ROW_NUMBER() OVER (ORDER BY orderSum DESC) AS rn,
         COUNT(*) OVER () AS total_count
  FROM OrderMaster om
)
SELECT orderNo, customerNo, employeeNo, orderDate, orderSum
FROM ranked_orders
WHERE rn <= CEIL(total_count * 0.10)
ORDER BY orderSum DESC;

SELECT '2-1(6) 一共销售了几种商品' AS question;
SELECT COUNT(DISTINCT productNo) AS sold_product_count
FROM OrderDetail;

SELECT '2-1(7) 每种商品销售数量、平均单价和总金额' AS question;
SELECT productNo,
       SUM(quantity) AS total_quantity,
       ROUND(AVG(price), 2) AS avg_price,
       SUM(quantity * price) AS total_amount
FROM OrderDetail
GROUP BY productNo
ORDER BY total_amount DESC;

SELECT '2-1(8) 每个客户2020年3月订单总金额' AS question;
SELECT customerNo, SUM(orderSum) AS march_2020_amount
FROM OrderMaster
WHERE orderDate >= '2020-03-01' AND orderDate < '2020-04-01'
GROUP BY customerNo;

SELECT '2-1(9) 至少销售10件以上的商品' AS question;
SELECT productNo, SUM(quantity) AS total_quantity
FROM OrderDetail
GROUP BY productNo
HAVING SUM(quantity) >= 10
ORDER BY total_quantity DESC;

SELECT '2-1(10) 业务科且1987或1988年出生员工人数和平均工资' AS question;
SELECT COUNT(*) AS employee_count, ROUND(AVG(salary), 2) AS avg_salary
FROM Employee
WHERE department = '业务科'
  AND YEAR(birthday) IN (1987, 1988);

SELECT '实验2-2：多表查询' AS section;

SELECT '2-2(1) 同一天进入公司服务的员工' AS question;
SELECT e1.hireDate, e1.employeeNo, e1.employeeName
FROM Employee e1
WHERE EXISTS (
  SELECT 1
  FROM Employee e2
  WHERE e2.hireDate = e1.hireDate
    AND e2.employeeNo <> e1.employeeNo
)
ORDER BY e1.hireDate, e1.employeeNo;

SELECT '2-2(2) 薪水超过平均薪水的员工' AS question;
SELECT employeeNo, employeeName, salary
FROM Employee
WHERE salary > (SELECT AVG(salary) FROM Employee)
ORDER BY salary DESC;

SELECT '2-2(3) 没有订购商品的客户' AS question;
SELECT c.customerNo, c.customerName
FROM Customer c
LEFT JOIN OrderMaster om ON c.customerNo = om.customerNo
WHERE om.orderNo IS NULL;

SELECT '2-2(4) “酷睿四核I7-7700k”的销售情况' AS question;
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
  WHERE productName = '酷睿四核I7-7700k'
);

SELECT '2-2(5) 每个员工销售记录' AS question;
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
ORDER BY e.employeeNo, om.orderDate;

SELECT '2-2(6a) 左外连接：单价高于400元商品的订货情况' AS question;
SELECT p.productNo, p.productName, od.quantity, od.price
FROM Product p
LEFT JOIN OrderDetail od ON p.productNo = od.productNo AND od.price > 400
WHERE p.productPrice > 400
ORDER BY p.productNo;

SELECT '2-2(6b) 右外连接：单价高于400元商品的订货情况' AS question;
SELECT p.productNo, p.productName, od.quantity, od.price
FROM OrderDetail od
RIGHT JOIN Product p ON p.productNo = od.productNo AND od.price > 400
WHERE p.productPrice > 400
ORDER BY p.productNo;

SELECT '2-2(6c) MySQL用UNION模拟完整外部连接' AS question;
SELECT p.productNo, p.productName, od.quantity, od.price
FROM Product p
LEFT JOIN OrderDetail od ON p.productNo = od.productNo AND od.price > 400
WHERE p.productPrice > 400
UNION
SELECT p.productNo, p.productName, od.quantity, od.price
FROM OrderDetail od
RIGHT JOIN Product p ON p.productNo = od.productNo AND od.price > 400
WHERE p.productPrice > 400
ORDER BY productNo;

SELECT '2-2(7) 单价高于400元商品订货总数量和总价' AS question;
SELECT p.productNo, p.productName,
       SUM(od.quantity) AS total_quantity,
       SUM(od.quantity * od.price) AS total_amount
FROM Product p
JOIN OrderDetail od ON p.productNo = od.productNo
WHERE od.price > 400
GROUP BY p.productNo, p.productName;

SELECT '2-2(8) OrderMaster中订单金额最高的订单' AS question;
SELECT orderNo, orderSum
FROM OrderMaster
WHERE orderSum = (SELECT MAX(orderSum) FROM OrderMaster);

SELECT '2-2(9) 订购总金额5000元以上的客户' AS question;
SELECT c.customerNo, c.customerName, SUM(om.orderSum) AS total_amount
FROM Customer c
JOIN OrderMaster om ON c.customerNo = om.customerNo
GROUP BY c.customerNo, c.customerName
HAVING SUM(om.orderSum) > 5000
ORDER BY total_amount DESC;

SELECT '2-2(10) 每种商品总销售数量及总金额' AS question;
SELECT p.productNo, p.productName,
       SUM(od.quantity) AS total_quantity,
       SUM(od.quantity * od.price) AS total_amount
FROM Product p
JOIN OrderDetail od ON p.productNo = od.productNo
GROUP BY p.productNo, p.productName
ORDER BY p.productNo;

SELECT '实验2-3：复杂查询' AS section;

SELECT '2-3(1) 订单明细中订单金额最高的订单' AS question;
SELECT orderNo, SUM(quantity * price) AS detail_amount
FROM OrderDetail
GROUP BY orderNo
ORDER BY detail_amount DESC
LIMIT 1;

SELECT '2-3(2) 至少被订购3次的商品明细' AS question;
WITH ordered_three AS (
  SELECT productNo
  FROM OrderDetail
  GROUP BY productNo
  HAVING COUNT(*) >= 3
)
SELECT od.productNo, od.orderNo, od.quantity, od.quantity * od.price AS amount
FROM OrderDetail od
JOIN ordered_three t ON od.productNo = t.productNo
ORDER BY od.quantity DESC;

SELECT '2-3(3) 订购商品总数量不超过10个的客户' AS question;
SELECT c.customerNo, c.customerName, COALESCE(SUM(od.quantity),0) AS total_quantity
FROM Customer c
LEFT JOIN OrderMaster om ON c.customerNo = om.customerNo
LEFT JOIN OrderDetail od ON om.orderNo = od.orderNo
GROUP BY c.customerNo, c.customerName
HAVING COALESCE(SUM(od.quantity),0) <= 10;

SELECT '2-3(4) 至少订购3种商品的客户明细' AS question;
WITH customers_three AS (
  SELECT om.customerNo
  FROM OrderMaster om
  JOIN OrderDetail od ON om.orderNo = od.orderNo
  GROUP BY om.customerNo
  HAVING COUNT(DISTINCT od.productNo) >= 3
)
SELECT c.customerNo, c.customerName, p.productNo, p.productName,
       SUM(od.quantity) AS quantity,
       SUM(od.quantity * od.price) AS amount
FROM customers_three ct
JOIN Customer c ON ct.customerNo = c.customerNo
JOIN OrderMaster om ON c.customerNo = om.customerNo
JOIN OrderDetail od ON om.orderNo = od.orderNo
JOIN Product p ON od.productNo = p.productNo
GROUP BY c.customerNo, c.customerName, p.productNo, p.productName
ORDER BY c.customerNo, p.productNo;

SELECT '2-3(5) 总销售金额最高的销售员订单' AS question;
WITH top_employee AS (
  SELECT employeeNo
  FROM OrderMaster
  GROUP BY employeeNo
  ORDER BY SUM(orderSum) DESC
  LIMIT 1
)
SELECT om.employeeNo, om.orderNo, om.orderDate, om.orderSum
FROM OrderMaster om
JOIN top_employee te ON om.employeeNo = te.employeeNo
ORDER BY om.orderSum DESC;

SELECT '2-3(6) 每位客户订购每种商品的总数量及平均单价' AS question;
SELECT om.customerNo, od.productNo,
       SUM(od.quantity) AS total_quantity,
       ROUND(AVG(od.price), 2) AS avg_price
FROM OrderMaster om
JOIN OrderDetail od ON om.orderNo = od.orderNo
GROUP BY om.customerNo, od.productNo
ORDER BY om.customerNo, od.productNo;

SELECT '2-3(7) 业绩最好的业务员' AS question;
SELECT e.employeeNo, e.employeeName, SUM(om.orderSum) AS total_sales
FROM Employee e
JOIN OrderMaster om ON e.employeeNo = om.employeeNo
GROUP BY e.employeeNo, e.employeeName
ORDER BY total_sales DESC
LIMIT 1;

SELECT '2-3(8) 用EXISTS查找没有订货记录的客户' AS question;
SELECT c.customerName
FROM Customer c
WHERE NOT EXISTS (
  SELECT 1 FROM OrderMaster om WHERE om.customerNo = c.customerNo
);

SELECT '2-3(9) 至少包含“手环”商品的订单明细' AS question;
SELECT om.orderNo, c.customerName, p.productName, od.quantity, od.price
FROM OrderMaster om
JOIN Customer c ON om.customerNo = c.customerNo
JOIN OrderDetail od ON om.orderNo = od.orderNo
JOIN Product p ON od.productNo = p.productNo
WHERE EXISTS (
  SELECT 1
  FROM OrderDetail od2
  JOIN Product p2 ON od2.productNo = p2.productNo
  WHERE od2.orderNo = om.orderNo
    AND p2.productName LIKE '%手环%'
)
ORDER BY om.orderNo, p.productName;

SELECT '2-3(10) 同时订购酷睿四核和华为手环的客户订单' AS question;
SELECT c.customerNo, om.orderNo, om.orderSum
FROM Customer c
JOIN OrderMaster om ON c.customerNo = om.customerNo
WHERE EXISTS (
  SELECT 1
  FROM OrderDetail od
  JOIN Product p ON od.productNo = p.productNo
  WHERE od.orderNo = om.orderNo
    AND p.productName LIKE '%酷睿四核%'
)
AND EXISTS (
  SELECT 1
  FROM OrderDetail od
  JOIN Product p ON od.productNo = p.productNo
  WHERE od.orderNo = om.orderNo
    AND p.productName LIKE '%华为手环%'
);

SELECT '实验2问题简答' AS section;
SELECT 'GROUP BY先按分组列形成分组，再在每个分组内计算COUNT/SUM/AVG等聚合结果。WHERE在分组前过滤行，HAVING在分组后过滤聚合结果；非聚合查询列必须进入GROUP BY，才能保证每组输出值唯一。' AS answer;
