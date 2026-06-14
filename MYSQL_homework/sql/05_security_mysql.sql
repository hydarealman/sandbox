SET NAMES utf8mb4;
USE OrderDB;

DROP USER IF EXISTS 'user01'@'localhost';
DROP USER IF EXISTS 'user02'@'localhost';
DROP USER IF EXISTS 'user03'@'localhost';
DROP USER IF EXISTS 'user05'@'localhost';
DROP USER IF EXISTS 'user06'@'localhost';
DROP USER IF EXISTS 'user07'@'localhost';
DROP USER IF EXISTS 'login03'@'localhost';
DROP ROLE IF EXISTS 'r3'@'localhost';
DROP ROLE IF EXISTS 'r4'@'localhost';
DROP ROLE IF EXISTS 'r5'@'localhost';
DROP ROLE IF EXISTS 'r6'@'localhost';

CREATE USER 'user01'@'localhost' IDENTIFIED BY 'p888888';
CREATE USER 'user02'@'localhost' IDENTIFIED BY 'p888888';
CREATE USER 'login03'@'localhost' IDENTIFIED BY 'p888888';
CREATE USER 'user05'@'localhost' IDENTIFIED BY 'p888888';
CREATE USER 'user06'@'localhost' IDENTIFIED BY 'p888888';
CREATE USER 'user07'@'localhost' IDENTIFIED BY 'p888888';
RENAME USER 'login03'@'localhost' TO 'user03'@'localhost';

GRANT ALL PRIVILEGES ON OrderDB.Employee TO 'user01'@'localhost', 'user02'@'localhost', 'user03'@'localhost';
GRANT SELECT ON OrderDB.Product TO 'user03'@'localhost';
GRANT SELECT (employeeNo, employeeName), UPDATE (employeeNo, employeeName)
  ON OrderDB.Employee TO 'user03'@'localhost';

CREATE ROLE 'r3'@'localhost';
CREATE ROLE 'r4'@'localhost';
GRANT SELECT ON OrderDB.OrderDetail TO 'r3'@'localhost';
GRANT UPDATE (price) ON OrderDB.OrderDetail TO 'r3'@'localhost';

REVOKE ALL PRIVILEGES ON OrderDB.Employee FROM 'user01'@'localhost', 'user02'@'localhost', 'user03'@'localhost';

GRANT 'r3'@'localhost' TO 'user01'@'localhost', 'user02'@'localhost';
SET DEFAULT ROLE 'r3'@'localhost' TO 'user01'@'localhost', 'user02'@'localhost';

REVOKE 'r3'@'localhost' FROM 'user02'@'localhost';
DROP ROLE 'r4'@'localhost';

GRANT CREATE, CREATE VIEW ON OrderDB.* TO 'user01'@'localhost';

DROP TABLE IF EXISTS Table_user01;
CREATE TABLE Table_user01 (
  id INT PRIMARY KEY,
  note VARCHAR(40)
) ENGINE=InnoDB;
INSERT INTO Table_user01 VALUES (1, 'user01 table demo');

CREATE OR REPLACE VIEW View_user01 AS
SELECT id, note FROM Table_user01;

GRANT SELECT ON OrderDB.Table_user01 TO 'user02'@'localhost', 'user03'@'localhost';
GRANT SELECT ON OrderDB.View_user01 TO 'user02'@'localhost', 'user03'@'localhost';

DROP TABLE IF EXISTS Table1;
CREATE TABLE Table1 (
  id INT PRIMARY KEY,
  content VARCHAR(40)
) ENGINE=InnoDB;
INSERT INTO Table1 VALUES (1, 'created for user07');
GRANT SELECT, INSERT ON OrderDB.Table1 TO 'user02'@'localhost';

DROP TABLE IF EXISTS Table2;
DROP TABLE IF EXISTS Table3;
CREATE TABLE Table2 (
  id INT PRIMARY KEY,
  content VARCHAR(40)
) ENGINE=InnoDB;
CREATE TABLE Table3 (
  id INT PRIMARY KEY,
  content VARCHAR(40)
) ENGINE=InnoDB;
INSERT INTO Table2 VALUES (1, 'table2 row');
INSERT INTO Table3 VALUES (1, 'table3 row');
CREATE OR REPLACE VIEW View1 AS
SELECT t2.id, t2.content AS content2, t3.content AS content3
FROM Table2 t2
JOIN Table3 t3 ON t2.id = t3.id;

GRANT SELECT ON OrderDB.Table2 TO 'user05'@'localhost', 'user06'@'localhost' WITH GRANT OPTION;
GRANT SELECT ON OrderDB.Table3 TO 'user05'@'localhost', 'user06'@'localhost' WITH GRANT OPTION;
GRANT SELECT ON OrderDB.View1 TO 'user05'@'localhost', 'user06'@'localhost' WITH GRANT OPTION;
GRANT SELECT ON OrderDB.Table2 TO 'user07'@'localhost';

CREATE ROLE 'r5'@'localhost';
CREATE ROLE 'r6'@'localhost';
GRANT CREATE, CREATE VIEW ON OrderDB.* TO 'r5'@'localhost';
GRANT SELECT, INSERT ON OrderDB.Customer TO 'r6'@'localhost';
GRANT SELECT, UPDATE, INSERT ON OrderDB.Employee TO 'r6'@'localhost';
GRANT ALL PRIVILEGES ON OrderDB.OrderMaster TO 'r6'@'localhost';
GRANT 'r5'@'localhost' TO 'user07'@'localhost';
SET DEFAULT ROLE 'r5'@'localhost' TO 'user07'@'localhost';

DROP TABLE IF EXISTS Table4;
CREATE TABLE Table4 (
  id INT PRIMARY KEY,
  content VARCHAR(40)
) ENGINE=InnoDB;
INSERT INTO Table4 VALUES (1, 'role r5 create table demo');

FLUSH PRIVILEGES;

SELECT '实验5：MySQL安全性定义与权限检查' AS section;
SHOW GRANTS FOR 'user01'@'localhost';
SHOW GRANTS FOR 'user02'@'localhost';
SHOW GRANTS FOR 'user03'@'localhost';
SHOW GRANTS FOR 'user07'@'localhost';

SELECT user, host
FROM mysql.user
WHERE user IN ('user01','user02','user03','user05','user06','user07')
ORDER BY user;

SELECT '权限对象检查' AS section;
SELECT table_name
FROM information_schema.tables
WHERE table_schema = 'OrderDB'
  AND table_name IN ('Table_user01','Table1','Table2','Table3','Table4','View_user01','View1')
ORDER BY table_name;
