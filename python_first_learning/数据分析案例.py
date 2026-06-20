#实现步骤
#1.设计一个类,可以完成数据的封装
class Record:
    def __init__(self,data,order_id,money,province):
        self.data = data            #订单日期
        self.order_id = order_id    #订单ID
        self.money = money          #订单金额
        self.province = province    #销售省份
#2.设计一个抽象类，定义文件读取的相关功能，并使用子类实现具体功能

#3.读取文件产生数据集
#4.进行数据需求的逻辑运算(计算每一天的销售额)
#5.通过pyecharts进行图形绘制