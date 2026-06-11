package review_pratice;

// import java.util.regex.Pattern;
// import java.util.regex.Matcher;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RegexExample {
    public static void main(String[] args) {
        // 1. 基础匹配：检查字符串是否完全符合正则规则
        String text = "Hello123";
        String regex = "\\w+\\d+";  // 字母数字组合（字母开头，数字结尾）
        
        // Pattern 表示编译后的正则表达式
        Pattern pattern = Pattern.compile(regex);
        // Matcher 用于执行匹配操作
        Matcher matcher = pattern.matcher(text);
        
        // matches() 要求整个字符串完全匹配
        boolean isFullMatch = matcher.matches();
        System.out.println("完全匹配: " + isFullMatch);  // true
        
        // 2. 查找子串：在文本中寻找符合正则的部分
        String sentence = "我的邮箱是 test@example.com 和 info@company.cn";
        String emailRegex = "\\w+@\\w+\\.\\w+";  // 简单邮箱正则
        
        Pattern emailPattern = Pattern.compile(emailRegex);
        Matcher emailMatcher = emailPattern.matcher(sentence);
        
        System.out.println("找到的邮箱地址:");
        while (emailMatcher.find()) {  // find() 依次查找下一个匹配的子串
            String email = emailMatcher.group();  // 返回本次匹配到的子串
            System.out.println("  - " + email);
        }
        
        // 3. 捕获组：提取特定部分
        String dateStr = "2025-07-15, 2026-01-20";
        String dateRegex2 = "(\\d{4})-(\\d{2})-(\\d{2})";  // 年、月、日作为分组
        Pattern datePattern = Pattern.compile(dateRegex2);
        Matcher dateMatcher = datePattern.matcher(dateStr);
        
        System.out.println("\n提取日期中的年、月、日:");
        while (dateMatcher.find()) {
            String year = dateMatcher.group(1);   // 第一组括号内的内容
            String month = dateMatcher.group(2);
            String day = dateMatcher.group(3);
            System.out.printf("  年: %s, 月: %s, 日: %s%n", year, month, day);
        }
        
        // 4. 字符串替换：使用 replaceAll 方法
        String original = "我的电话是 138-1234-5678 和 010-87654321";
        String replaced = original.replaceAll("\\d", "X");  // 把所有数字替换成 X
        System.out.println("\n替换数字为 X: " + replaced);
        
        // 使用 Matcher 的 replaceAll（支持正则引用）
        String messy = "用户ID: 1001, 1002, 1003";
        String result = Pattern.compile("\\d+")
                .matcher(messy)
                .replaceAll("USER_$0");  // $0 代表整个匹配到的内容
        System.out.println("带前缀替换: " + result);
        
        // 5. 常用正则语法示例（写在注释中便于学习）
        /*
         * 字符类：
         *   [abc]      → a、b 或 c
         *   [^abc]     → 除 a、b、c 外的任意字符
         *   [a-z]      → a 到 z 的小写字母
         *   [A-Z]      → 大写字母
         *   [0-9]      → 数字，等同于 \d
         *
         * 预定义字符：
         *   \d         → 数字，[0-9]
         *   \D         → 非数字
         *   \w         → 单词字符（字母、数字、下划线），[a-zA-Z0-9_]
         *   \W         → 非单词字符
         *   \s         → 空白字符（空格、制表符、换行等）
         *   \S         → 非空白字符
         *   .          → 任何字符（默认不包含换行符）
         *
         * 数量词：
         *   *          → 0 次或多次
         *   +          → 1 次或多次
         *   ?          → 0 次或 1 次
         *   {n}        → 恰好 n 次
         *   {n,}       → 至少 n 次
         *   {n,m}      → n 到 m 次
         *
         * 边界匹配：
         *   ^          → 行首
         *   $          → 行尾
         *   \b         → 单词边界
         *
         * 分组和引用：
         *   (abc)      → 捕获组，编号从 1 开始
         *   (?:abc)    → 非捕获组
         *   \1         → 反向引用第一个捕获组的内容
         */
        
        // 6. 示例：验证手机号（简单版，11位数字且以1开头）
        // String phone = "13812345678";
        // boolean isValidPhone = phone.matches("1\\d{10}");
        // System.out.println("\n手机号格式正确吗？" + isValidPhone);

        String phone = "13897968288";
        boolean isValidPhone = phone.matches("1\\d{10}");
        System.out.println("\\n手机号格式正确吗？"+ isValidPhone);
        
        // 7. 示例：忽略大小写匹配
        String caseText = "Hello WORLD";
        Pattern caseInsensitive = Pattern.compile("hello", Pattern.CASE_INSENSITIVE);
        Matcher caseMatcher = caseInsensitive.matcher(caseText);
        System.out.println("忽略大小写匹配 \"hello\": " + caseMatcher.find());
    }
}