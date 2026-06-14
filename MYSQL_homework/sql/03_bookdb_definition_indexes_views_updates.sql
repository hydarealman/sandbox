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

CREATE TABLE Book (
  bookNo CHAR(10) PRIMARY KEY,
  classNo CHAR(3) NOT NULL,
  publisherNo CHAR(4) NOT NULL,
  bookName VARCHAR(100) NOT NULL,
  author VARCHAR(60),
  price DECIMAL(8,2) NOT NULL CHECK (price BETWEEN 10 AND 80),
  stock INT NOT NULL DEFAULT 0 CHECK (stock >= 0),
  CONSTRAINT fk_book_class FOREIGN KEY (classNo) REFERENCES BookClass(classNo),
  CONSTRAINT fk_book_publisher FOREIGN KEY (publisherNo) REFERENCES Publisher(publisherNo)
) ENGINE=InnoDB;

CREATE TABLE Reader (
  readerNo CHAR(8) PRIMARY KEY,
  readerName VARCHAR(40) NOT NULL,
  sex CHAR(1) NOT NULL CHECK (sex IN ('男','女')),
  identifyCard CHAR(18) NOT NULL UNIQUE,
  workUnit VARCHAR(100),
  maxBorrowCount INT NOT NULL DEFAULT 0 CHECK (maxBorrowCount BETWEEN 0 AND 8),
  currentBorrowCount INT NOT NULL DEFAULT 0 CHECK (currentBorrowCount BETWEEN 0 AND 8),
  borrowPeriodDays INT NOT NULL DEFAULT 30
) ENGINE=InnoDB;

CREATE TABLE Borrow (
  readerNo CHAR(8) NOT NULL,
  bookNo CHAR(10) NOT NULL,
  borrowDate DATE NOT NULL DEFAULT (CURRENT_DATE),
  returnDueDate DATE NOT NULL,
  actualReturnDate DATE NULL DEFAULT NULL,
  PRIMARY KEY (readerNo, bookNo, borrowDate),
  CONSTRAINT fk_borrow_reader FOREIGN KEY (readerNo) REFERENCES Reader(readerNo)
    ON UPDATE CASCADE ON DELETE RESTRICT,
  CONSTRAINT fk_borrow_book FOREIGN KEY (bookNo) REFERENCES Book(bookNo)
    ON UPDATE CASCADE ON DELETE RESTRICT,
  CONSTRAINT chk_borrow_date CHECK (
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
('R2020004','B202101001','2020-08-01','2020-09-01',NULL),
('R2020004','B202101002','2020-08-05','2020-09-05','2020-08-25'),
('R2021001','B201801001','2021-01-10','2021-02-10',NULL),
('R2021001','B201801002','2021-01-12','2021-02-12',NULL),
('R2021001','B201801003','2021-01-14','2021-02-14',NULL),
('R2021002','B202101003','2021-03-01','2021-04-01',NULL),
('R2021002','B202101004','2021-03-05','2021-04-05','2021-03-28'),
('R2021003','B202201001','2021-05-01','2021-06-01',NULL),
('R2022001','B202201002','2022-01-12','2022-02-12',NULL),
('R2022002','B202201003','2022-02-15','2022-03-15',NULL),
('R2022002','B202201004','2022-02-18','2022-03-18','2022-03-01');

UPDATE Reader r
LEFT JOIN (
  SELECT readerNo, COUNT(*) AS active_count
  FROM Borrow
  WHERE actualReturnDate IS NULL
  GROUP BY readerNo
) b ON r.readerNo = b.readerNo
SET r.currentBorrowCount = COALESCE(b.active_count, 0);

SELECT '实验3-1：BookDB数据库与5张基本表创建完成' AS section;
SHOW TABLES;

CREATE INDEX PublishingnoIdx ON Book(publisherNo);
CREATE INDEX IdentifycardIdx ON Reader(identifyCard);
CREATE INDEX WorkunitCountIdx ON Reader(workUnit ASC, maxBorrowCount DESC);

CREATE OR REPLACE VIEW BookView AS
SELECT bookNo, bookName, author, price
FROM Book
WHERE bookName LIKE '%数据%';

CREATE OR REPLACE VIEW BorrowView AS
SELECT r.readerNo, r.readerName, b.bookNo, bk.bookName, b.borrowDate, b.returnDueDate
FROM Reader r
JOIN Borrow b ON r.readerNo = b.readerNo
JOIN Book bk ON b.bookNo = bk.bookNo;

CREATE OR REPLACE VIEW ReaderView AS
SELECT r.readerNo, r.readerName, r.sex, r.workUnit, COUNT(*) AS borrowTimes
FROM Reader r
JOIN Borrow b ON r.readerNo = b.readerNo
GROUP BY r.readerNo, r.readerName, r.sex, r.workUnit
HAVING COUNT(*) >= 3;

SELECT '实验3-2：BookView中书名含“数据”的图书' AS section;
SELECT * FROM BookView;

SELECT '实验3-2：BorrowView中2016年3月1日以前借阅的图书' AS section;
SELECT * FROM BorrowView
WHERE borrowDate < '2016-03-01';

SELECT '实验3-2：ReaderView中姓张的读者' AS section;
SELECT * FROM ReaderView
WHERE readerName LIKE '张%';

CREATE OR REPLACE VIEW BorrowView1 AS
SELECT *
FROM BorrowView
WHERE readerNo IN (
  SELECT readerNo FROM Reader WHERE workUnit = '合生元有限公司'
);

SELECT '实验3-2：合生元有限公司读者借书视图BorrowView1' AS section;
SELECT * FROM BorrowView1;

DROP VIEW BorrowView;

SELECT '实验3-3：数据更新操作' AS section;

UPDATE Reader
SET workUnit = '联合立华股份有限公司'
WHERE workUnit = '合生元有限公司';

UPDATE Book
SET price = ROUND(price * 0.95, 2)
WHERE stock = (
  SELECT max_stock FROM (SELECT MAX(stock) AS max_stock FROM Book) t
);

UPDATE Book b
JOIN BookClass c ON b.classNo = c.classNo
SET b.price = ROUND(b.price * 1.10, 2)
WHERE c.className = '经济类';

UPDATE Book b
JOIN (
  SELECT bookNo, COUNT(*) AS borrow_count
  FROM Borrow
  GROUP BY bookNo
  HAVING COUNT(*) > 2
) x ON b.bookNo = x.bookNo
SET b.stock = FLOOR(b.stock * 1.5);

UPDATE Reader
SET borrowPeriodDays = 90
WHERE workUnit = '兴隆股份有限公司';

UPDATE Reader r
LEFT JOIN (
  SELECT readerNo, COUNT(*) AS active_count
  FROM Borrow
  WHERE actualReturnDate IS NULL
  GROUP BY readerNo
) b ON r.readerNo = b.readerNo
SET r.currentBorrowCount = COALESCE(b.active_count, 0);

DELETE br
FROM Borrow br
JOIN Book bk ON br.bookNo = bk.bookNo
WHERE bk.price > 30;

DELETE br
FROM Borrow br
JOIN Book bk ON br.bookNo = bk.bookNo
WHERE bk.bookName = '大学英语';

DELETE r
FROM Reader r
LEFT JOIN Borrow b ON r.readerNo = b.readerNo
WHERE b.readerNo IS NULL;

SELECT '实验3-3：更新后数据统计' AS section;
SELECT
  (SELECT COUNT(*) FROM Reader) AS reader_count,
  (SELECT COUNT(*) FROM Borrow) AS borrow_count,
  (SELECT COUNT(*) FROM Book WHERE classNo = '002') AS economic_book_count;
