class student:
    name = None
    age = None
    tel = None

    def __init__(self,name,age,tel):
        self.name = name
        self.age = age
        self.tel = tel
        print("student类创建了一个对象")
stu = student("周杰伦",31,"18500006666")
#创建类时传入的参数会自动提供给__init__方法
#构建类的时候__init__方法会自动执行
