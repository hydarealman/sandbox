package JAVALAB.lab5;

/**
 * 实验5 - 双线程猜数字主程序
 * 启动两个线程：一个生成随机数并反馈，另一个用二分法猜测
 */
public class TwoThreadGuessNumber {
    public static void main(String args[]) {
        System.out.println("========== 实验5：双线程猜数字 ==========");
        Number number = new Number();
        number.giveNumberThread.start();
        number.guessNumberThread.start();
    }
}
