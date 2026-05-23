package JAVALAB.lab1;

import java.util.Scanner;

public class InputMess {
    public static void main(String args[]) {
        Scanner reader = new Scanner(System.in);
        System.out.println("输入姓名(回车确认)");
        String name = reader.nextLine();
        System.out.println("输入年龄(回车确认)");
        byte age = reader.nextByte();
        System.out.println("输入身高(回车确认):");
        float height = reader.nextFloat(); 
        System.out.println("姓名：" + name + "，年龄：" + age + "，身高：" + height);
    }
}
