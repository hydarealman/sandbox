package review_pratice;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class demo3_zhengze {
    public static void main(String[] args) {
        String text = "订单号：12345，金额：99.8元";
        String regex = "\\d+\\.?\\d*";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(text);
        String result = matcher.replaceAll("[数字]");
        System.out.println(result);
    }
}
