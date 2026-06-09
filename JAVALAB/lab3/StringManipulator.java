package JAVALAB.lab3;

/**
 * 文件名：StringManipulator.java
 * 功能：反转字符串并判断是否为回文
 */
import java.util.Scanner;

public class StringManipulator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入一个字符串：");
        String input = scanner.nextLine();
        scanner.close();
        
        // 反转字符串
        String reversed = new StringBuilder(input).reverse().toString();
        System.out.println("原字符串：" + input);
        System.out.println("反转后：" + reversed);
        
        // 判断回文（忽略大小写和非字母数字）
        if (isPalindrome(input)) {
            System.out.println("该字符串是回文串（忽略大小写及标点）。");
        } else {
            System.out.println("该字符串不是回文串。");
        }
    }
    
    /**
     * 判断是否为回文（只考虑字母数字，忽略大小写）
     */
    public static boolean isPalindrome(String s) {
        // 去除非字母数字字符并转为小写
        String cleaned = s.replaceAll("[^a-zA-Z0-9]", "").toLowerCase();
        String reversed = new StringBuilder(cleaned).reverse().toString();
        return cleaned.equals(reversed);
    }
}