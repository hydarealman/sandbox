package JAVALAB.lab5;

import java.io.*;

/**
 * 实验3 - 密码验证与文件读取
 * 用户有3次机会输入密码（正确密码：tiger123），验证通过后读取 score.txt 内容
 * 注意：在 IDE 中运行时，System.console() 可能返回 null，
 * 故提供 Scanner 回退方案
 */
public class PassWord {
    public static void main(String args[]) {
        boolean success = false;
        int count = 0;

        System.out.println("========== 实验3：密码流 ==========");

        // 尝试使用 Console（命令行运行时可用）
        java.io.Console cons = System.console();

        while (true) {
            String password;
            if (cons != null) {
                // 命令行环境：使用 Console 读取密码（不回显）
                System.out.print("输入密码:");
                char[] passwd = cons.readPassword();
                password = new String(passwd);
            } else {
                // IDE 环境回退：使用 Scanner（密码会回显，但保证程序可运行）
                java.util.Scanner scanner = new java.util.Scanner(System.in);
                System.out.print("输入密码(IDE模式，密码可见):");
                password = scanner.nextLine();
            }

            count++;

            if (password.equals("tiger123")) {
                success = true;
                System.out.println("您第" + count + "次输入的密码正确!");
                break;
            } else {
                System.out.println("您第" + count + "次输入的密码" + password + "不正确");
            }

            if (count == 3) {
                System.out.println("您" + count + "次输入的密码都不正确");
                System.exit(0);
            }
        }

        // 密码验证成功，读取文件
        if (success) {
            File file = new File("JAVALAB/lab5/score.txt");
            try {
                FileReader inOne = new FileReader(file);
                BufferedReader inTwo = new BufferedReader(inOne);
                String s = null;
                System.out.println("\n--- score.txt 文件内容 ---");
                while ((s = inTwo.readLine()) != null) {
                    System.out.println(s);
                }
                inOne.close();
                inTwo.close();
            } catch (IOException exp) {
                System.out.println("文件读取失败: " + exp.toString());
            }
        }
    }
}
