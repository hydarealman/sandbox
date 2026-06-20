#基础数据类型注解
var_1:int = 10
var_2:float = 3.1415926
var_3:bool = True
var_4:str = "itheima"
#类对象类型注解
class student:
    pass
stu:student = student()
#基础容器类型注解
my_list:list = [1,2,3]
my_tuple: tuple = (1,2,3)
my_set: set = {1,2,3}
my_dict :dict = {"itheima":666}
my_str:str = "itheima"
#基础容器类型详细注解
my_list:list[int] = [1,2,3]
my_tuple:tuple[str,int,bool] = ("itheima",666,True)
my_set:set = {1,2,3}
my_dict:dict[str,int] = {"itheima":666}
#元组类型设置详细注解,需要将每个元素都标记出来
#字典类型设置类型详细注释,需要两个类型，第一个是key，第二个是value

class Student:
    pass

import random
import json
def func():
    return Student
#法二
data = '[{"name":"张大三","age":11},{"name":"王大锤","age":13},{"name":"赵小虎","age":16}]'
var_1 = random.randint(1,10)    #type: int
var_2 = json.loads(data)        #type: dict[str,int]
var_3 = func()                  #type: Student

#类型注解主要功能在于:
#帮助第三方工具IDE工具对代码进行类型推断,协助做代码提示
#帮助开发者自身对变量进行类型注释(备注)


#类型注解仅仅是提示性,不是决定性的