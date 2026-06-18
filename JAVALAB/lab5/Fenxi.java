package JAVALAB.lab5;

import java.util.*;

/**
 * 实验1 - 分数分析工具类
 * 使用正则表达式和StringTokenizer解析成绩字符串，计算总成绩
 */
public class Fenxi {
    /**
     * 从成绩字符串中提取所有数字并求和
     * @param s 包含姓名和各项成绩的字符串，如 "张三 78.5 90 85.5"
     * @return 总成绩
     */
    public static double getTotalScore(String s) {
        // 匹配非数字字符的正则表达式（保留数字和小数点）
        String regex = "[^0123456789.]";
        // 将非数字字符替换为 * 作为分隔符
        String digitMess = s.replaceAll(regex, "*");
        // 使用 StringTokenizer 以 * 为分隔符提取数字
        StringTokenizer fenxi = new StringTokenizer(digitMess, "*");
        double totalScore = 0;
        while (fenxi.hasMoreTokens()) {
            double score = Double.parseDouble(fenxi.nextToken());
            totalScore = totalScore + score;
        }
        return totalScore;
    }
}
