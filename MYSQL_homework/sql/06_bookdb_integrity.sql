SET NAMES utf8mb4;

DROP DATABASE IF EXISTS BookDB;
CREATE DATABASE BookDB DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci;
USE BookDB;

CREATE TABLE BookClass (
  classNo CHAR(3) PRIMARY KEY,
  className VARCHAR(40) NOT NULL UNIQUE
) ENGINE=InnoDB;

CREATE TABLE Publisher (
  publisherNo CHAR(4) PRIMARY KEY,
  publisherName VARCHAR(80) NOT NULL,
  address VARCHAR(120),
  phone VARCHAR(30)
) ENGINE=InnoDB;

CREATE TABLE Reader (
  readerNo CHAR(8) PRIMARY KEY,
  readerName VARCHAR(40) NOT NULL,
  sex CHAR(1) NOT NULL CHECK (sex IN ('男','女')),
  identifyCard CHAR(18) NOT NULL UNIQUE,
  workUnit VARCHAR(100),
  maxBorrowCount INT NOT NULL DEFAULT 0 CHECK (maxBorrowCount BETWEEN 0 AND 8),
  currentBorrowCount INT NOT NULL DEFAULT 0 CHECK (currentBorrowCount BETWEEN 0 AND 8),
  CONSTRAINT chk_reader_no CHECK (
    readerNo REGEXP '^R[0-9]{7}$'
    AND CAST(SUBSTRING(readerNo, 2, 4) AS UNSIGNED) <= 2026
  )
) ENGINE=InnoDB;

CREATE TABLE Book (
  bookNo CHAR(10) PRIMARY KEY,
  classNo CHAR(3) NOT NULL,
  publisherNo CHAR(4) NOT NULL,
  bookName VARCHAR(100) NOT NULL,
  author VARCHAR(60),
  price DECIMAL(8,2) NOT NULL CHECK (price BETWEEN 10 AND 80),
  stock INT NOT NULL DEFAULT 0 CHECK (stock >= 0),
  CONSTRAINT chk_book_no CHECK (
    bookNo REGEXP '^B[0-9]{9}$'
    AND CAST(SUBSTRING(bookNo, 2, 4) AS UNSIGNED) <= 2026
  ),
  CONSTRAINT fk_book_class_int FOREIGN KEY (classNo) REFERENCES BookClass(classNo)
    ON UPDATE CASCADE ON DELETE RESTRICT,
  CONSTRAINT fk_book_publisher_int FOREIGN KEY (publisherNo) REFERENCES Publisher(publisherNo)
    ON UPDATE CASCADE ON DELETE RESTRICT
) ENGINE=InnoDB;

CREATE TABLE Borrow (
  readerNo CHAR(8) NOT NULL,
  bookNo CHAR(10) NOT NULL,
  borrowDate DATE NOT NULL DEFAULT (CURRENT_DATE),
  returnDueDate DATE NOT NULL,
  actualReturnDate DATE NULL DEFAULT NULL,
  PRIMARY KEY (readerNo, bookNo, borrowDate),
  CONSTRAINT fk_borrow_reader_int FOREIGN KEY (readerNo) REFERENCES Reader(readerNo)
    ON UPDATE CASCADE ON DELETE RESTRICT,
  CONSTRAINT fk_borrow_book_int FOREIGN KEY (bookNo) REFERENCES Book(bookNo)
    ON UPDATE CASCADE ON DELETE RESTRICT,
  CONSTRAINT chk_borrow_dates_int CHECK (
    returnDueDate > borrowDate
    AND (actualReturnDate IS NULL OR actualReturnDate > borrowDate)
  )
) ENGINE=InnoDB;

INSERT INTO BookClass VALUES
('001','计算机类'),
('002','经济类'),
('003','外语类'),
('004','文学类'),
('005','机械类');

INSERT INTO Publisher VALUES
('P001','清华大学出版社','北京市海淀区','010-11110001'),
('P002','人民邮电出版社','北京市东城区','010-11110002'),
('P003','机械工业出版社','北京市西城区','010-11110003'),
('P004','外语教学与研究出版社','北京市海淀区','010-11110004'),
('P005','高等教育出版社','北京市朝阳区','010-11110005');

INSERT INTO Reader(readerNo, readerName, sex, identifyCard, workUnit, maxBorrowCount) VALUES
('R2020001','欧阳','男','412723199209014321','合生元有限公司',5),
('R2020002','张颖','女','450302199812120022','兴隆股份有限公司',6),
('R2020003','李雷','男','450302199706180033','桂林理工大学',5),
('R2020004','韩梅','女','450302199905060044','南方科技公司',4),
('R2021001','王涛','男','450302200001010055','合生元有限公司',4),
('R2021002','赵芳','女','450302200002020066','联合立华股份有限公司',5),
('R2021003','陈晨','女','450302200103030077','兴隆股份有限公司',6),
('R2022001','刘杰','男','450302200204040088','桂林电子有限公司',3),
('R2022002','周敏','女','450302200205050099','红谷有限责任公司',4),
('R2022003','孙宁','男','450302200206060100','未借阅公司',2);

INSERT INTO Book VALUES
('B201801001','001','P001','数据库系统原理','王珊',58.00,40),
('B201801002','001','P002','数据结构','严蔚敏',45.00,30),
('B201801003','001','P001','MySQL数据库应用','李明',39.00,45),
('B201901001','001','P003','操作系统概论','张军',42.00,35),
('B201901002','001','P002','计算机网络','谢希仁',49.00,38),
('B202001001','002','P005','西方经济学','高鸿业',28.00,50),
('B202001002','002','P003','会计学基础','刘红',26.00,55),
('B202001003','002','P005','管理经济学','周林',29.00,60),
('B202001004','003','P004','大学英语','郑树棠',32.00,70),
('B202001005','003','P004','英语语法实践','章振邦',24.00,42),
('B202101001','004','P005','中国现代文学','钱理群',35.00,33),
('B202101002','004','P005','写作教程','刘海',22.00,36),
('B202101003','005','P003','机械设计基础','濮良贵',56.00,28),
('B202101004','005','P003','工程制图','何铭新',48.00,32),
('B202101005','001','P001','数据仓库与数据挖掘','陈文伟',52.00,27),
('B202201001','001','P002','Python数据分析','周志华',50.00,29),
('B202201002','002','P005','财政学','陈共',27.00,31),
('B202201003','003','P004','商务英语','李华',30.00,44),
('B202201004','004','P005','唐诗鉴赏','袁行霈',25.00,37),
('B202201005','005','P003','液压传动','王积伟',46.00,26);

INSERT INTO Borrow(readerNo, bookNo, borrowDate, returnDueDate, actualReturnDate) VALUES
('R2020001','B201801001','2020-01-10','2020-02-10','2020-02-01'),
('R2020001','B201801002','2020-02-10','2020-03-10',NULL),
('R2020001','B202001004','2020-03-11','2020-04-11',NULL),
('R2020002','B202001004','2020-03-12','2020-04-12',NULL),
('R2020002','B201801003','2020-04-15','2020-05-15','2020-05-10'),
('R2020002','B202101005','2020-05-18','2020-06-18',NULL),
('R2020003','B202001001','2020-06-01','2020-07-01',NULL),
('R2020003','B202001002','2020-06-03','2020-07-03','2020-06-28'),
('R2020003','B202001003','2020-07-01','2020-08-01',NULL),
('R2020004','B202101001','2020-08-01','2020-09-01',NULL);

INSERT INTO Borrow(readerNo, bookNo, borrowDate, returnDueDate, actualReturnDate)
WITH RECURSIVE seq(n) AS (
  SELECT 11
  UNION ALL
  SELECT n + 1 FROM seq WHERE n < 50
)
SELECT
  ELT((n MOD 9) + 1,
      'R2020001','R2020002','R2020003','R2020004','R2021001',
      'R2021002','R2021003','R2022001','R2022002') AS readerNo,
  ELT((n MOD 20) + 1,
      'B201801001','B201801002','B201801003','B201901001','B201901002',
      'B202001001','B202001002','B202001003','B202001004','B202001005',
      'B202101001','B202101002','B202101003','B202101004','B202101005',
      'B202201001','B202201002','B202201003','B202201004','B202201005') AS bookNo,
  DATE_ADD('2021-01-01', INTERVAL n DAY) AS borrowDate,
  DATE_ADD('2021-01-31', INTERVAL n DAY) AS returnDueDate,
  CASE WHEN n MOD 3 = 0 THEN DATE_ADD('2021-01-20', INTERVAL n DAY) ELSE NULL END AS actualReturnDate
FROM seq;

UPDATE Reader r
LEFT JOIN (
  SELECT readerNo, COUNT(*) AS active_count
  FROM Borrow
  WHERE actualReturnDate IS NULL
  GROUP BY readerNo
) b ON r.readerNo = b.readerNo
SET r.currentBorrowCount = LEAST(COALESCE(b.active_count, 0), 8);

CREATE TABLE IntegrityTestLog (
  id INT AUTO_INCREMENT PRIMARY KEY,
  testItem VARCHAR(200) NOT NULL,
  result VARCHAR(40) NOT NULL,
  message TEXT,
  createdAt TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB;

DELIMITER $$

CREATE PROCEDURE run_integrity_test(IN p_label VARCHAR(200), IN p_sql TEXT)
BEGIN
  DECLARE v_success INT DEFAULT 1;
  DECLARE v_message TEXT DEFAULT '执行成功';
  DECLARE CONTINUE HANDLER FOR SQLEXCEPTION
  BEGIN
    SET v_success = 0;
    GET DIAGNOSTICS CONDITION 1 v_message = MESSAGE_TEXT;
  END;

  SET @integrity_sql = p_sql;
  PREPARE stmt FROM @integrity_sql;
  EXECUTE stmt;
  DEALLOCATE PREPARE stmt;

  INSERT INTO IntegrityTestLog(testItem, result, message)
  VALUES (p_label, IF(v_success = 1, '执行成功', '被完整性约束拦截'), v_message);
END$$

DELIMITER ;

SELECT '实验6：完整性约束定义完成，基础数据量' AS section;
SELECT
  (SELECT COUNT(*) FROM BookClass) AS class_count,
  (SELECT COUNT(*) FROM Publisher) AS publisher_count,
  (SELECT COUNT(*) FROM Book) AS book_count,
  (SELECT COUNT(*) FROM Reader) AS reader_count,
  (SELECT COUNT(*) FROM Borrow) AS borrow_count;

CALL run_integrity_test('插入BookClass重复主键：(''001'',''机械类'')',
  'INSERT INTO BookClass VALUES (''001'', ''机械类'')');

CALL run_integrity_test('插入Reader重复编号或身份证：R2020001',
  'INSERT INTO Reader(readerNo,readerName,sex,identifyCard,workUnit,maxBorrowCount) VALUES (''R2020001'', ''欧阳'', ''男'', ''412723199209014321'', ''欧氏公司'', 0)');

CALL run_integrity_test('插入Borrow不存在的读者R2021003或日期检查',
  'INSERT INTO Borrow(readerNo,bookNo,borrowDate,returnDueDate,actualReturnDate) VALUES (''R2021003'', ''B201801002'', ''2018-09-18'', ''2018-10-18'', NULL)');

CALL run_integrity_test('删除已有借阅记录的读者R2020001',
  'DELETE FROM Reader WHERE readerNo = ''R2020001''');

CALL run_integrity_test('删除无借阅记录的读者R2022003',
  'DELETE FROM Reader WHERE readerNo = ''R2022003''');

CALL run_integrity_test('将R2020002借阅B202001004日期改为2021-04-22',
  'UPDATE Borrow SET borrowDate = ''2021-04-22'' WHERE readerNo = ''R2020002'' AND bookNo = ''B202001004''');

CALL run_integrity_test('将R2020002最大借书数量改为9',
  'UPDATE Reader SET maxBorrowCount = 9 WHERE readerNo = ''R2020002''');

CALL run_integrity_test('数据库系统原理价格上调30元',
  'UPDATE Book SET price = price + 30 WHERE bookName = ''数据库系统原理''');

SELECT '实验6：完整性检查结果' AS section;
SELECT id,
       testItem,
       result,
       CASE
         WHEN result = '执行成功' THEN LEFT(message, 90)
         ELSE '该操作违反主键、外键或CHECK约束，已被MySQL完整性机制拦截'
       END AS message
FROM IntegrityTestLog
ORDER BY id;
