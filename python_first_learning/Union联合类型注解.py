#使用Union类型,必须先导包
#使用Union可以定义联合类型注解
from typing import Union

my_list: list[Union[int,str]] = [1,2,"itheima","itcast"]

def func(data:Union[int,str]) -> Union[int,str]:
    pass
