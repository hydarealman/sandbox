package JAVALAB.lab1;

import java.util.Scanner;

public class MenuPrinter {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请选择功能：");
        System.out.println("A - 打印直线");
        System.out.println("B - 打印杨辉三角形");
        System.out.print("输入选项：");
        String choice = scanner.nextLine();

        if (choice.equalsIgnoreCase("A")) {
            System.out.print("请输入直线长度（字符个数）：");
            int len = scanner.nextInt();
            for (int i = 0; i < len; i++) {
                System.out.print("*");
            }
            System.out.println();
        } else if (choice.equalsIgnoreCase("B")) {
            System.out.print("请输入杨辉三角的行数：");
            int rows = scanner.nextInt();
            int[][] triangle = new int[rows][rows];
            for (int i = 0; i < rows; i++) {
                triangle[i][0] = 1;
                triangle[i][i] = 1;
                for (int j = 1; j < i; j++) {
                    triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
                }
            }
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j <= i; j++) {
                    System.out.print(triangle[i][j] + " ");
                }
                System.out.println();
            }
        } else {
            System.out.println("无效选项");
        }
    }
}
