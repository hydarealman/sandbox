SET NAMES utf8mb4;
USE OrderDB;
START TRANSACTION;
INSERT INTO Employee(employeeNo, employeeName, sex, department, headship, hireDate, birthday, salary, address)
VALUES
('E2099001','隔离测试A','M','业务科','业务员',CURRENT_DATE,'1996-01-01',12000.00,'测试地址A'),
('E2099002','隔离测试B','F','业务科','业务员',CURRENT_DATE,'1997-01-01',12500.00,'测试地址B');
COMMIT;
