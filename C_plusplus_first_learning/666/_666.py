
from Lib.Unitree_Lib import Unitree_Robot       #导入封装好的类
import time

def robot_control():    #定义控制函数
    t_stand = time.perf_counter()
    while(time.perf_counter() - t_stand < 2.0):  #站立2秒
        state = unitree_robot.robot_walking(gaitType=1,             #步态，行走步态为1，跑步模式步态为2，爬坡步态为3；1是最常使用的步态，一般不用改，前冲也不要切换到跑步模式
                                            forwardSpeed=0.0,       #前进速度，单位m/s，正数为前进，
                                            sidewaySpeed=0.0,       #左右平移速度，单位m/s，正数为为左平移，负数为右平移
                                            rotateSpeed=0.0,        #旋转速度，单位m/s，正数为向左旋转，负数为向右旋转，狗跑偏后通过调整这个参数来修正路线
                                            speedLevel=0,           #速度等级，正常为1，不用改
                                            bodyHeight=0.0,         #身体高度，用到的时候一般是负数，此时机器狗看的太远了，需要压低狗的身体高度看清脚底下的路面
                                            footRaiseHeight=0.0     #机器狗运动时的台脚高度，一般为0.0，不用改
                                            )

    t_forward = time.perf_counter()
    while(time.perf_counter() - t_forward < 2.0):    #以0.5m/s的速度向前行走2秒
        state = unitree_robot.robot_walking(gaitType=1,             #步态设置为1，行走模式
                                            forwardSpeed=0.5,       #将前进速度设置为0.5
                                            sidewaySpeed=0.0,       
                                            rotateSpeed=0.0,        
                                            speedLevel=0,           
                                            bodyHeight=0.0,         
                                            footRaiseHeight=0.0     
                                            )

    t_stand = time.perf_counter()
    while(time.perf_counter() - t_stand < 2.0):    #站稳
        state = unitree_robot.robot_walking(gaitType=1,             #步态可以不用改
                                            forwardSpeed=0.0,       #将前进速度设置为0.0， 停止向前行走
                                            sidewaySpeed=0.0,       
                                            rotateSpeed=0.0,        
                                            speedLevel=0,           
                                            bodyHeight=0.0,         
                                            footRaiseHeight=0.0     
                                            )

    t_rotate = time.perf_counter()
    while(time.perf_counter() - t_rotate < 2.0):    #以1.0m/s的速度向左旋转2秒
        state = unitree_robot.robot_walking(gaitType=1,             
                                            forwardSpeed=0.0,       
                                            sidewaySpeed=0.0,       
                                            rotateSpeed=1.5,        #将旋转速度设置为1.5        
                                            speedLevel=0,           
                                            bodyHeight=0.0,         
                                            footRaiseHeight=0.0     
                                            )

    t_rotate = time.perf_counter()
    while(time.perf_counter() - t_rotate < 2.0):    #以1.0m/s的速度向右旋转2秒
        state = unitree_robot.robot_walking(gaitType=1,             
                                            forwardSpeed=0.0,       
                                            sidewaySpeed=0.0,       
                                            rotateSpeed=1.5,        #将旋转速度设置为-1.5        
                                            speedLevel=0,           
                                            bodyHeight=0.0,         
                                            footRaiseHeight=0.0     
                                            )

def main():
    while(True):
        robot_control()
        break

if __name__ == '__main__':              #初始化
    unitree_robot = Unitree_Robot()     #创建对象实例，命名为unitree_robot，用于控制机器狗的运动
    main()                              #启
