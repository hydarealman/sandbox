package review_pratice;

public class StringDemo {
    public static void main(String[] args) {
        char[] helloArray = {'r','u','n','o','o','b'};
        String helloString = new String(helloArray);
        System.out.println(helloString);
        int len = helloString.length();
        System.out.println("字符串长度" + len);

        String helloArray2 = new String("hello");
        helloString = helloString.concat(helloArray2);
        System.out.println(helloString);

        System.out.printf("%s", helloArray2);
    }
}
