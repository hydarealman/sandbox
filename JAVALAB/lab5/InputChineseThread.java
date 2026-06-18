package JAVALAB.lab5;

import java.util.Scanner;

/**
 * 实验4 - 输入汉字线程
 * 接收用户键盘输入的汉字，与系统显示的汉字对比，统计得分
 * 输入 # 结束程序
 */
public class InputChineseThread extends Thread {
    Scanner reader;
    Chinese hanzi;
    int score = 0;

    InputChineseThread() {
        reader = new Scanner(System.in);
    }

    /** 设置共享的 Chinese 对象 */
    public void setChinese(Chinese hanzi) {
        this.hanzi = hanzi;
    }

    @Override
    public void run() {
        while (true) {
            String str = reader.nextLine();
            char c = str.charAt(0);
            if (c == hanzi.getChinese()) {
                score++;
                System.out.printf("\t\t输入对了,目前分数%d\n", score);
            } else {
                System.out.printf("\t\t输入错了,目前分数%d\n", score);
            }
            if (c == '#')
                System.exit(0);
        }
    }
}
