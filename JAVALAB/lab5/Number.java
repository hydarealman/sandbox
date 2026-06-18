package JAVALAB.lab5;

/**
 * 实验5 - 双线程猜数字
 * 实现 Runnable 接口，两个线程协作猜数字：
 * - giveNumberThread：生成随机数并给出"猜大了"/"猜小了"的反馈
 * - guessNumberThread：使用二分法猜测数字
 */
public class Number implements Runnable {
    final int SMALLER = -1, LARGER = 1, SUCCESS = 8;
    int realNumber, guessNumber, min = 0, max = 100, message = SMALLER;
    boolean pleaseGuess = false, isGiveNumber = false;
    Thread giveNumberThread, guessNumberThread;

    Number() {
        // 创建 giveNumberThread，当前 Number 实例作为目标对象
        giveNumberThread = new Thread(this);
        // 创建 guessNumberThread，当前 Number 实例作为目标对象
        guessNumberThread = new Thread(this);
    }

    @Override
    public void run() {
        for (int count = 1; true; count++) {
            setMessage(count);
            if (message == SUCCESS)
                return;
        }
    }

    /**
     * 同步方法：处理两个线程的协作逻辑
     * giveNumberThread 负责生成数字和给出反馈
     * guessNumberThread 负责二分法猜测
     */
    public synchronized void setMessage(int count) {
        // ---- giveNumberThread 第一次执行：生成随机数 ----
        if (Thread.currentThread() == giveNumberThread && isGiveNumber == false) {
            realNumber = (int) (Math.random() * 100) + 1;
            System.out.println("随机给你一个 1 至 100 之间的数，猜猜是多少？");
            isGiveNumber = true;
            pleaseGuess = true;
        }

        // ---- giveNumberThread：给出反馈 ----
        if (Thread.currentThread() == giveNumberThread) {
            while (pleaseGuess == true)
                try {
                    wait();
                } catch (InterruptedException e) {
                }
            if (realNumber > guessNumber) {
                message = SMALLER;
                System.out.println("你猜小了");
            } else if (realNumber < guessNumber) {
                message = LARGER;
                System.out.println("你猜大了");
            } else {
                message = SUCCESS;
                System.out.println("恭喜，你猜对了");
            }
            pleaseGuess = true;
        }

        // ---- guessNumberThread：二分法猜测 ----
        if (Thread.currentThread() == guessNumberThread && isGiveNumber == true) {
            while (pleaseGuess == false)
                try {
                    wait();
                } catch (InterruptedException e) {
                }
            if (message == SMALLER) {
                min = guessNumber;
                guessNumber = (min + max) / 2;
                System.out.println("我第" + count + "次猜这个数是:" + guessNumber);
            } else if (message == LARGER) {
                max = guessNumber;
                guessNumber = (min + max) / 2;
                System.out.println("我第" + count + "次猜这个数是:" + guessNumber);
            }
            pleaseGuess = false;
        }
        notifyAll();
    }
}
