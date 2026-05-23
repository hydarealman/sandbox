package JAVALAB;

public class InputChinese {
    public static void main(String args[]) {
        char ch = '石';
        int p = 22920, count = 5, position = 0;
        System.out.printf("输出%d个石字符的汉子:\n",count);
        for (char c = ch; c <= ch + count; c++) {
            position = (int) c;
            System.out.printf("%c(%d)",c,position);
        }
        System.out.printf("\n输出%d个女字符的汉字:\n",count);
        for (int n = p; n <= p + count; n++) {
            char zifu = (char) n;
            System.out.printf("%c(%d)", zifu, n);
        }
    }
}
