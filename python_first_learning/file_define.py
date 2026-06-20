"""
和文件相关的类定义
"""

from 
# 先定义一个抽象类用来做顶层设计,确定有哪些功能需要实现
class FileReader:

    def read_data(self)->list[Record]:
        """读取文件数据,读到的每一条数据都转化为Record对象,将他们都封装到list内返回即可"""
        pass