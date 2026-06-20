#定义一个类,内含私有成员变量和私有成员方法
class phone:

    __current_voltage = 0.5

    def __keep_single_core(self):
        print("让CPU以单核模式运行")

    def call_by_sg(self):
        if self.__current_voltage >= 1:
            print("5g通话已开始")
        else:
            self.__keep_single_core()
            print("电量不足,无法使用5g童话,并已设置未单核运行进行省电")
phone = phone()
phone.call_by_sg()

#1.封装的概念
#将现实世界事务在类中描述为属性和方法，即为封装
#2.什么是私有成员?为什么需要私有成员
#现实世界事务有部分属性和行为是不公开对使用者开放的.
#同样在类中描述属性和方法的时候也需要达到这个要求，就需要定义私有成员了
#3.如何定义私有成员
#成员变量和成员方法的命名均以__作为开头即可
#4.私有成员的访问限制
#类对象无法访问私有成员
#类中的其他成员可以访问私有成员