package code;

/**
 * 匿名内部类 --- 计算一个方法执行了多少秒
 */
public class blog_1_1 {
    public static void main(String[] args) {

        // 匿名内部类：new 接口名() { 实现方法 }
        // 相当于临时造了一个没有名字的类，实现 Task 接口
        Task t = new Task() {
            @Override
            public void run() {
                long sum = 0;
                for (int i = 1; i <= 50_000_000; i++) {
                    sum += i;
                }
                System.out.println("结果: " + sum);
            }
        };

        long start = System.currentTimeMillis(); // 开始时间（毫秒）
        t.run();
        long end = System.currentTimeMillis();   // 结束时间（毫秒）

        double sec = (end - start) / 1000.0;
        System.out.println("执行了 " + sec + " 秒");
    }
}

interface Task{
    void run();
}

