package JAVALAB.lab3;

/**
 * 文件名：PhoneNumberValidator.java
 * 功能：验证手机号（137/138/139开头，共11位）
 */
import java.util.Scanner;
import java.util.regex.Pattern;

public class PhoneNumberValidator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入一串连续的数字：");
        String input = scanner.nextLine();
        scanner.close();
        
        if (isValidPhoneNumber(input)) {
            System.out.println(input + " 是一个有效的手机号码（137/138/139开头）。");
        } else {
            System.out.println(input + " 不是有效的手机号码。");
        }
    }
    
    public static boolean isValidPhoneNumber(String number) {
        // 正则：以137、138或139开头，后面跟8位数字
        String regex = "^(137|138|139)\\d{8}$";
        return Pattern.matches(regex, number);
    }
}
