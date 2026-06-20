class student:
    name =None
    age = None

    def say_hi(self):
        print(f"hi大家好,我是{self.name}")
    def say_hi2(self,msg):
        print(f"hello 大家好,{msg}")

stu = student()
stu.say_hi()
stu.say_hi2("很高兴认识大家")

