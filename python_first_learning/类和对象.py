#设计一个闹钟类
class Clock:
    id = None
    price = None

    def ring(self):
        import winsound
        winsound.Beep(2000,3000)

#构建2个闹钟对象并让其工作
clock1 = Clock()
clock1.id = "003032"
clock1.price = 19.99
print(f"闹钟ID:{clock1.id},价格:{clock1.price}")
clock1.ring()