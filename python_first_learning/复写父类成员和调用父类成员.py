#复写
#子类继承父类的成员属性和成员方法后，如果对其不满意，那么可以进行复写
class phone:
    IMEI = None
    producer = "ITCAST"

    def call_by_5g(self):
        print("父类的5g通话")

class Myphone(phone):
    producer = "ITHEIMA"

    def call_by_5g(self):
        print("子类的5g通话")
        print(phone.IMEI)
        print(phone.call_by_5g(self))
        super().call_by_5g()
xiaomi = Myphone()
xiaomi.call_by_5g()

#1.复写表示
#对父类的成员属性或成员方法进行重新定义
#2.复写的语法
#在子类中重新实现同名成员方法或成员属性即可
#3，在子类中，如何调用父类成员
#方式1：父类名.
#方式2：super().

