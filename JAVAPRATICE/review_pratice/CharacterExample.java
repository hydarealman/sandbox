package review_pratice;

public class CharacterExample {
    public static void main(String[] args) {
        // 1. 装箱与拆箱
        Character ch1 = 'A';               // 自动装箱 (char -> Character)
        char ch2 = ch1;                    // 自动拆箱 (Character -> char)
        System.out.println("拆箱后的字符: " + ch2);

        // 2. 判断字符类型
        char test = '9';
        System.out.println("'" + test + "' 是数字? " + Character.isDigit(test));
        System.out.println("'" + test + "' 是字母? " + Character.isLetter(test));

        test = 'z';
        System.out.println("'" + test + "' 是小写? " + Character.isLowerCase(test));
        System.out.println("'" + test + "' 转大写: " + Character.toUpperCase(test));

        // 3. 空白字符判断
        char space = ' ';
        System.out.println("空格是空白字符? " + Character.isWhitespace(space));

        // 4. 进制转换
        char hexChar = 'F';
        int value = Character.digit(hexChar, 16);   // 十六进制字符 'F' -> 15
        System.out.println("字符 'F' 的十六进制数值: " + value);

        char fromValue = Character.forDigit(15, 16); // 15 -> 字符 'F'
        System.out.println("数值15的十六进制字符: " + fromValue);

        // 5. 实际应用：统计字符串中的数字和字母个数
        String str = "Hello 2025! 你好 😊";
        int digitCount = 0, letterCount = 0, spaceCount = 0;
        for (char c : str.toCharArray()) {
            if (Character.isDigit(c)) digitCount++;
            else if (Character.isLetter(c)) letterCount++;
            else if (Character.isWhitespace(c)) spaceCount++;
        }
        System.out.println("\n字符串: \"" + str + "\"");
        System.out.println("数字个数: " + digitCount);
        System.out.println("字母个数: " + letterCount);
        System.out.println("空白字符个数: " + spaceCount);
    }
}
