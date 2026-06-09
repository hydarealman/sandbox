package JAVALAB.lab3;

/**
 * 文件名：BirthdayCalculator.java
 * 功能：计算从出生到现在的总天数
 */
import java.util.Calendar;
import java.util.Scanner;

public class BirthdayCalculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入出生年份：");
        int year = scanner.nextInt();
        System.out.print("请输入出生月份（1-12）：");
        int month = scanner.nextInt() - 1; // Calendar中月份从0开始
        System.out.print("请输入出生日期：");
        int day = scanner.nextInt();
        scanner.close();
        
        Calendar birth = Calendar.getInstance();
        birth.set(year, month, day);
        Calendar now = Calendar.getInstance();
        
        // 清除时分秒，只比较日期
        birth.set(Calendar.HOUR_OF_DAY, 0);
        birth.set(Calendar.MINUTE, 0);
        birth.set(Calendar.SECOND, 0);
        birth.set(Calendar.MILLISECOND, 0);
        now.set(Calendar.HOUR_OF_DAY, 0);
        now.set(Calendar.MINUTE, 0);
        now.set(Calendar.SECOND, 0);
        now.set(Calendar.MILLISECOND, 0);
        
        long diffMillis = now.getTimeInMillis() - birth.getTimeInMillis();
        long days = diffMillis / (1000 * 60 * 60 * 24);
        
        System.out.println("从出生到今天，您已经活了 " + days + " 天。");
    }
}