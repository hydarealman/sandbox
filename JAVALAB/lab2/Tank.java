package JAVALAB.lab2;

public class Tank {
    //【代码1】声明double型变量speed,刻画速度
    double speed;
    //【代码2】声明int型变量bulletAmount,刻画炮弹数量
    int bulletAmount;

    void speedUp(int s) {
        //【代码3】将 s + speed 赋值给speed
        speed = s + speed;
    }

    void speedDown(int d) {
        if (speed - d >= 0)
            //【代码4】将 speed - d 赋值给speed
            speed = speed - d;
        else speed = 0;
    }

    void setBulletAmount(int m) {
        bulletAmount = m;
    }

    int getBulletAmount() {
        return bulletAmount;
    }

    double getSpeed() {
        return speed;
    }

    void fire() {
        if (bulletAmount >= 1) {
            //【代码5】将 bulletAmount - 1 赋值给bulletAmount
            bulletAmount = bulletAmount - 1;
            System.out.println("打出一发炮弹");
        } else {
            System.out.println("没有炮弹了，无法开火");
        }
    }
}