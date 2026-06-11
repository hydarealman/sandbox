package code;

/**
 * 创建线程的两种方式（对比学习）
 *
 * 方式1: extends Thread       — 继承 Thread 类，重写 run()
 * 方式2: implements Runnable  — 实现 Runnable 接口，传入 Thread 构造器
 *
 * 核心区别：Java 只能单继承 → 方式1 会"占用"继承名额，方式2 更灵活（推荐）
 */
public class blog_7 {

    public static void main(String[] args) {

        // ==================== 方式1：继承 Thread 类 ====================
        // 语法：class 子类 extends Thread { 重写 run() }
        // 启动：子类对象.start()    ← 注意是 start()，不是 run()！

        MyThread t1 = new MyThread();   // 创建线程对象
        t1.start();                     // start() → JVM 帮你调用 run() 并启动新线程

        // ==================== 方式2：实现 Runnable 接口 ====================
        // 语法：class 子类 implements Runnable { 实现 run() }
        //       然后 new Thread(子类对象).start()
        // 优点：不占用继承名额，可以把"任务"和"线程"解耦

        Runnable task = new MyRunnable();     // 只定义"任务"
        Thread t2 = new Thread(task);          // 把任务装进 Thread
        t2.start();                            // start() 启动新线程

        // 主线程继续执行
        System.out.println("主线程结束（但不代表子线程结束）");
    }
}


// ========== 方式1：继承 Thread 类 ==========
// 语法：extends Thread — 当前类直接变成一个"线程类"
// 缺点：如果 MyThread 还需要继承别的类，就行不通了（Java 单继承）
class MyThread extends Thread {

    // 重写 run() — 新线程要执行的代码写在这里
    // @Override 是注解：告诉编译器"我是在重写父类方法"，拼错会报错
    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            // Thread.currentThread().getName() → 获取当前线程名字
            System.out.println("方式1-继承Thread: " + i
                    + " [" + Thread.currentThread().getName() + "]");
        }
    }
}


// ========== 方式2：实现 Runnable 接口 ==========
// 语法：implements Runnable — 只是实现接口，不占用继承名额
// 优点：MyRunnable 还可以 extends 其他类（比如 extends Animal）
class MyRunnable implements Runnable {

    // 实现 run() — 新线程要执行的代码写在这里
    // 注意：实现接口必须写 public（接口方法默认 public，不能降低可见性）
    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println("方式2-实现Runnable: " + i
                    + " [" + Thread.currentThread().getName() + "]");
        }
    }
}
