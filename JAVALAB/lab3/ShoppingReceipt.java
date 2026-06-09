package JAVALAB.lab3;

/**
 * 文件名：ShoppingReceipt.java
 * 功能：打印购物小票，包含时间、商品清单、总价
 */
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class ShoppingReceipt {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入商品种类数：");
        int n = scanner.nextInt();
        scanner.nextLine();
        
        String[] names = new String[n];
        int[] quantities = new int[n];
        double[] prices = new double[n];
        double total = 0;
        
        for (int i = 0; i < n; i++) {
            System.out.println("请输入第" + (i+1) + "个商品名称：");
            names[i] = scanner.nextLine();
            System.out.print("数量：");
            quantities[i] = scanner.nextInt();
            System.out.print("单价：");
            prices[i] = scanner.nextDouble();
            scanner.nextLine();
            total += quantities[i] * prices[i];
        }
        
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        DecimalFormat df = new DecimalFormat("#0.00");
        
        System.out.println("\n========== 购物小票 ==========");
        System.out.println("打印时间：" + sdf.format(new Date()));
        System.out.println("-----------------------------");
        System.out.println("商品\t数量\t单价\t小计");
        for (int i = 0; i < n; i++) {
            double subtotal = quantities[i] * prices[i];
            System.out.println(names[i] + "\t" + quantities[i] + "\t" 
                    + df.format(prices[i]) + "\t" + df.format(subtotal));
        }
        System.out.println("-----------------------------");
        System.out.println("总计：¥" + df.format(total));
        System.out.println("=============================");
        scanner.close();
    }
}