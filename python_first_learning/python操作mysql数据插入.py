from pymysql import Connection

conn = Connection(
    host="localhost",#主机名
    port=3306,#端口
    user="root",#账户
    password="123456",#密码
    autocommit=True#设置自动提交
)

cursor = conn.cursor()

conn.select_db("world")

cursor.execute("insert into student values(100013,'周杰伦',31,'男')")

#通过commit确认
#conn.commit()

conn.close()