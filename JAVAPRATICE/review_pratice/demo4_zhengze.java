package review_pratice;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

// 捕获组的使用(提取日期中的年,月,日)

public class demo4_zhengze {
    public static void main(String[] args) {
        String data = "2026-06-11";
        String regex = "(\\d{4})-(\\d{2})-(\\d{2})";
        Pattern p = Pattern.compile(regex);
        Matcher m = p.matcher(data);
        if (m.find()) {
            System.out.println("完整日期: " + m.group());
            System.out.println("完整日期: " + m.group(1));
            System.out.println("完整日期: " + m.group(2));
            System.out.println("完整日期: " + m.group(3));
        } 
    }
}
