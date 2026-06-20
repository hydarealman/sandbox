class phone:
    __is_5g_enable = False
    def __init__(self,is_5g_enable):
        self.__is_5g_enable = is_5g_enable
    def __check_5g(self):
        if self.__is_5g_enable:
            print("5g开启")
        else:
            print("5g关闭,使用4g网络")
    def call_by_5g(self):
        self.__check_5g()
        print("正在通话中")
xiaomi = phone(True)
xiaomi.call_by_5g()

    