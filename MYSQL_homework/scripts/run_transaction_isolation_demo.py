from pathlib import Path

import pymysql


ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / "outputs" / "08_isolation_demo.txt"


def connect():
    return pymysql.connect(
        host="localhost",
        user="root",
        password="123456",
        database="OrderDB",
        charset="utf8mb4",
        autocommit=False,
    )


def scalar(conn, sql, args=None):
    with conn.cursor() as cur:
        cur.execute(sql, args or ())
        return cur.fetchone()[0]


def cleanup(conn):
    with conn.cursor() as cur:
        cur.execute("DELETE FROM Employee WHERE employeeNo IN ('E2099001','E2099002')")
    conn.commit()


def run_case(level):
    conn1 = connect()
    conn2 = connect()
    try:
        cleanup(conn1)

        with conn1.cursor() as cur:
            cur.execute(f"SET SESSION TRANSACTION ISOLATION LEVEL {level}")
            cur.execute("START TRANSACTION")
        avg1 = scalar(conn1, "SELECT ROUND(AVG(salary), 2) FROM Employee")

        with conn2.cursor() as cur:
            cur.execute("START TRANSACTION")
            cur.execute(
                """
                INSERT INTO Employee
                  (employeeNo, employeeName, sex, department, headship,
                   hireDate, birthday, salary, address)
                VALUES
                  ('E2099001','隔离测试A','M','业务科','业务员',CURRENT_DATE,'1996-01-01',12000.00,'测试地址A'),
                  ('E2099002','隔离测试B','F','业务科','业务员',CURRENT_DATE,'1997-01-01',12500.00,'测试地址B')
                """
            )
            conn2.commit()

        avg2 = scalar(conn1, "SELECT ROUND(AVG(salary), 2) FROM Employee")
        conn1.commit()

        cleanup(conn1)
        return avg1, avg2
    finally:
        conn1.close()
        conn2.close()


def main():
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    lines = [
        "实验8：事务隔离级别并发演示",
        "T1负责两次查询Employee平均薪水，T2在两次查询之间插入两名高薪员工并提交。",
        "",
        "+----------------+---------------+---------------+------------------------------+",
        "| 隔离级别       | 第一次平均薪水 | 第二次平均薪水 | 现象说明                     |",
        "+----------------+---------------+---------------+------------------------------+",
    ]

    results = []
    for level in ["READ COMMITTED", "REPEATABLE READ"]:
        avg1, avg2 = run_case(level)
        explanation = "第二次读到T2提交的新数据" if avg1 != avg2 else "同一事务内保持一致读"
        results.append((level, avg1, avg2, explanation))

    for level, avg1, avg2, explanation in results:
        lines.append(f"| {level:<14} | {avg1!s:^13} | {avg2!s:^13} | {explanation:<28} |")
    lines.append("+----------------+---------------+---------------+------------------------------+")
    lines.append("")
    lines.append("结论：READ COMMITTED会在第二次查询时看到其他事务已提交的数据；")
    lines.append("REPEATABLE READ在同一事务内保持第一次读到的快照，因此两次结果一致。")

    OUTPUT.write_text("\n".join(lines), encoding="utf-8")
    print(OUTPUT.read_text(encoding="utf-8"))


if __name__ == "__main__":
    main()
