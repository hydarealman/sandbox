package review_pratice;

public class ThreadDemo {
    public static void main() {
        MyThread t1 = new MyThread("工作线程-1");
        MyThread t2 = new MyThread("工作线程-2");

        t1.setPriority(Thread.MIN_PRIORITY);  // 1
        t2.setPriority(Thread.MAX_PRIORITY);  // 10

        t1.start();
        t2.start();

        // 主线程也做一些事情
        for (int i = 1; i <= 3; i++) {
            System.out.println("主线程 计数：" + i);
            try {
                Thread.sleep(150);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class MyThread extends Thread{
    public MyThread(String name) {
        super(name); // 给线程设置名字
    }

    @Override
    public void run() {
        for (int i = 1; i <= 5; i++) {
            System.out.println(getName() + " 计数：" + i);
            try {
                sleep(100);
            } catch (InterruptedException e) {
                System.out.println(getName() + " 被中断");
            }
        }
        System.out.println(getName() + " 结束");
    }
}