#多态,指的是:多种状态,即完成某个行为时,使用不同的对象会得到不同的状态
class Animal:
    def speak(self):
        pass

class Dog(Animal):
    def speak(self):
        print("汪汪汪")

class Cat(Animal):
    def speak(self):
        print("喵喵喵")

def make_noise(animal:Animal):
    animal.speak()

dog = Dog()
cat = Cat()
make_noise(dog)
make_noise(cat)


#这种设计的含义是:
#父类用来确定有哪些方法
#具体的方法实现,由子类自行决定

#这种写法,就叫抽象类(也可以称之为接口)

#抽象类:含有抽象方法的类称为抽象类
#抽象方法:方法体是空实现的(pass)称之为抽象方法


#抽象类(接口)
#包含了一些抽象的方法,要求子类必须实现
class AC:
    def cool_wind(self):
        """制冷"""
        pass
    def hot_wind(self):
        """制热"""
        pass
    def swingL_r(self):
        """左右摆风"""
        pass

class Midea_AC(AC):
    def cool_wind(self):
        print("美的空调核心制冷科技")
    
    def hot_wind(self):
        print("美的空调电热丝加热")

    def swing_l_r(self):
        print("美的空调左右摆风")

class GREE_AC(AC):
    def cool_wind(self):
        print("格力空调核心制冷科技")
    
    def hot_wind(self):
        print("格力空调电热丝加热")

    def swing_l_r(self):
        print("格力空调左右摆风")

meidi = Midea_AC()
gree = GREE_AC()

def make_cool(ac:AC):
    ac.cool_wind()

make_cool(meidi)
make_cool(gree)