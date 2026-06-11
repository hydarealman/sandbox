package review_pratice;

// 文件名: RunnableDemo.java
public class RunnableDemo {
  public static void main(String[] args) {
    Runner runner1 = new Runner("线程A");
    Runner runner2 = new Runner("线程B");

    Thread thread1 = new Thread(runner1);
    Thread thread2 = new Thread(runner2);

    thread1.start();
    thread2.start();
  }
}

class Runner implements Runnable {
    String name;
    Runner(String name) {
        this.name = name;
    }

    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println(name + "第" + i + "步");
        }
    }
}