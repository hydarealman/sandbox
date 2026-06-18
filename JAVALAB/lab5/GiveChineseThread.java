package JAVALAB.lab5;

/**
 * 实验4 - 出汉字线程
 * 每隔一定时间随机显示一个汉字，起始于 '好' 字，循环100个汉字
 */
public class GiveChineseThread extends Thread {
    Chinese hanzi;
    char startChar = (char) 22909, endChar = (char) (startChar + 100);
    int sleepLength = 5000;

    /** 设置共享的 Chinese 对象 */
    public void setChinese(Chinese hanzi) {
        this.hanzi = hanzi;
    }

    /** 设置显示汉字的间隔时间（毫秒） */
    public void setSleepLength(int n) {
        sleepLength = n;
    }

    @Override
    public void run() {
        char c = startChar;
        while (true) {
            hanzi.setChinese(c);
            System.out.printf("显示的汉字: %c\n", hanzi.getChinese());
            try {
                // 调用 sleep 方法使得线程中断 sleepLength 毫秒
                sleep(sleepLength);
            } catch (InterruptedException e) {
                System.out.println("出汉字线程被中断");
            }
            c = (char) (c + 1);
            if (c > endChar)
                c = startChar;
        }
    }
}
