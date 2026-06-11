package review_pratice;

import java.util.regex.Pattern;

// 判断是否有数字包含
public class demo1_zhengze {
    public static void main(String[] args) {
        String text = "我的成绩是85分";
        String regex = "\\d+";
        boolean hasDigit = Pattern.matches(".*" + regex + ".*",text); // 检车是否整个字符串完成匹配
        System.out.println(hasDigit);
    }
}
