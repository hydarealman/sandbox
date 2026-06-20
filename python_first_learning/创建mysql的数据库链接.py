from pymysql import Connection
#获取MYSQL数据库的链接对象
conn = Connection(
    host = 'localhost',#主机名
    port=3306,#端口
    user='root',#账户
    password='123456'#密码
)
#打印MYSQL数据库软件信息
print(conn.get_server_info())

#获取游标对象
cursor = conn.cursor()
conn.select_db("world")    #选择数据库 use 数据库

#使用游标对象,执行sql语句
#cursor.execute("CREATE TABLE test_pymysql(id INT, info VARCHAR(255))")
#在pymysql的execute中执行的sql语句;可以不写
cursor.execute("select * from country")

#获取查询结果
results: tuple = cursor.fetchall()
for r in results:
    print(r)

#关闭到数据库的链接
conn.close()





