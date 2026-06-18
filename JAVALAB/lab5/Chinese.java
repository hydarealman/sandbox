package JAVALAB.lab5;

/**
 * 实验4 - 共享汉字数据类
 * 用于 GiveChineseThread 和 InputChineseThread 之间的数据共享
 */
public class Chinese {
    char c = '\0';

    /** 设置当前显示的汉字 */
    public void setChinese(char c) {
        this.c = c;
    }

    /** 获取当前显示的汉字 */
    public char getChinese() {
        return c;
    }
}
