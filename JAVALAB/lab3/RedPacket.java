package JAVALAB.lab3;

/**
 * 文件名：RedPacket.java
 * 功能：模拟微信抢红包，随机分配金额
 */
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

public class RedPacket {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入红包总金额（元）：");
        double total = scanner.nextDouble();
        System.out.print("请输入人数：");
        int people = scanner.nextInt();
        scanner.close();
        
        if (total < people * 0.01) {
            System.out.println("金额不足，每人至少0.01元");
            return;
        }
        
        List<BigDecimal> result = divideRedPacket(BigDecimal.valueOf(total), people);
        System.out.println("分配结果：");
        BigDecimal sum = BigDecimal.ZERO;
        for (int i = 0; i < result.size(); i++) {
            System.out.printf("第%d人：%.2f元\n", i+1, result.get(i));
            sum = sum.add(result.get(i));
        }
        System.out.printf("总金额：%.2f元\n", sum);
    }
    
    /**
     * 红包分配算法（二倍均值法）
     */
    public static List<BigDecimal> divideRedPacket(BigDecimal total, int count) {
        List<BigDecimal> list = new ArrayList<>();
        Random random = new Random();
        BigDecimal remain = total;
        int remainCount = count;
        
        for (int i = 0; i < count - 1; i++) {
            // 最大金额 = 剩余金额 - (剩余人数-1)*0.01
            BigDecimal max = remain.subtract(BigDecimal.valueOf(remainCount - 1).multiply(BigDecimal.valueOf(0.01)));
            // 随机金额范围 [0.01, max]
            double rand = random.nextDouble();
            BigDecimal money = BigDecimal.valueOf(rand).multiply(max).add(BigDecimal.valueOf(0.01));
            // 保留两位小数，四舍五入
            money = money.setScale(2, RoundingMode.HALF_UP);
            list.add(money);
            remain = remain.subtract(money);
            remainCount--;
        }
        // 最后一个人
        list.add(remain.setScale(2, RoundingMode.HALF_UP));
        return list;
    }
}
