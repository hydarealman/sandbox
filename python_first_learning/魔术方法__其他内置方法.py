
class student:
    name = None
    age = None
    # __init__魔术方法
    #构造方法，可用于创建类对象的时候设置初始化行为
    def __init__(self,name,age):
        self.age = age
        self.name = name
    #__str__魔术方法
    def __str__(self):
        #用于实现类对象转字符串的行为
        return f"Student类对象,name:{self.name},age:{self.age}"
        #如果不写直接输出内存地址，如果写的话，输出你返回的东西
    #__lt__魔术方法
    def __lt__(self,other):
        #小于魔术方法比较
        return self.age < other.age
    #__le__魔术方法
    def __le__(self,other):
        #小于等于魔术方法
        return self.age <= other.age

    #__eq__魔术方法
    #比较运算符实现方法,判断相不相等
    def __eq__(self,other):
        return self.age == other.age

stu = student("周杰伦",31)
print(stu)
print(str(stu))

stu1 = student("周杰伦",31)
stu2 = student("林俊杰",31)

print(stu1 < stu2)
#没有实现eq方法，等于等于符号默认比较内存地址
print(stu1 == stu2)
print(stu1 > stu2)

print(stu1 <= stu2)
print(stu1 == stu2)
print(stu1 >= stu2)


