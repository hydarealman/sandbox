#演示面向对象,继承的基础语法

# 演示单继承
class Phone:
    IMEI = None     # 序列号
    producer = "HM" # 厂商


    def call_by_4g(self):
        print("4g通话")


class phone2022(Phone):
    face_id = "10001"#面部识别ID

    def call_by_5g(self):
        print("5g通话")

# 演示多继承
class NFCReader:
    nfc_type = "第五代"
    producer = "ITCAST"

    def read_card(self):
        print("NFC读卡")
    
    def write_card(self):
        print("NFC写卡")

class RemoteControl:
    rc_type = "红外遥控"

    def control(self):
        print("红外遥控开启了")

class MyPhone(Phone,NFCReader,RemoteControl):
    pass

phone = MyPhone()
phone.read_card()
phone.write_card()
phone.control()
phone.call_by_4g()
print(phone.producer)


# 演示多继承下,父类成员名一致的场景
# 谁先继承谁的优先级高


#1.什么是继承？
#继承就是一个类,继承另外一个类的成员变量和成员方法
#2.单继承和多继承
#单继承：一个类继承另一个类
#多继承：一个类继承多个类，按照顺序从左到右依次继承
#多继承中，如果父类有同名方法或属性，先继承的优先级高于后继承的优先级
#3.pass关键字的作用
#pass是占位语句,用来保证函数或类定义的完整性,表示无内容,空的意思


