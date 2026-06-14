SET NAMES utf8mb4;
USE OrderDB;
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;
START TRANSACTION;
SELECT 'T1 READ COMMITTED 第一次查询' AS step, ROUND(AVG(salary),2) AS avg_salary FROM Employee;
SELECT '此时在另一个会话执行08_transaction_T2_insert.sql并提交，然后回到本会话继续执行下一句' AS note;
SELECT 'T1 READ COMMITTED 第二次查询' AS step, ROUND(AVG(salary),2) AS avg_salary FROM Employee;
COMMIT;
