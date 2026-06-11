package review_pratice;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

// 提取字符串所有的数字并求和

public class demo2_zhengze {
    public static void main(String[] args) {
        String text = "数学85分数,英语100分数,语文97.5";
        Pattern pattern = Pattern.compile("\\d+\\.?\\d*");
        Matcher matcher = pattern.matcher(text); // 返回一个Matcher对象,提供更丰富的操作
        double sum = 0;
        while(matcher.find()) {
            double score = Double.parseDouble(matcher.group());
            sum += score;
            System.out.println("找到分数" + score);
        }
        System.out.println("总分" + sum);
    }
}
