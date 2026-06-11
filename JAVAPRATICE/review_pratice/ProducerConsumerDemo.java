package review_pratice;

import java.util.LinkedList;
import java.util.Queue;

/**
 * 生产者-消费者示例
 * 共享缓冲区容量为5，生产者生产0-9的数字，消费者消费数字
 */
public class ProducerConsumerDemo {
    // 共享缓冲区
    private static final Queue<Integer> buffer = new LinkedList<>();
    private static final int CAPACITY = 5;

    // 生产者线程
    static class Producer implements Runnable {
        private final String name;

        Producer(String name) {
            this.name = name;
        }

        @Override
        public void run() {
            int value = 0;
            while (value < 10) {   // 生产0~9
                synchronized (buffer) {
                    // 缓冲区满，等待消费者消费
                    while (buffer.size() == CAPACITY) {
                        try {
                            System.out.println(name + " 缓冲区已满，等待...");
                            buffer.wait();   // 释放锁，进入等待
                        } catch (InterruptedException e) {
                            Thread.currentThread().interrupt();
                        }
                    }
                    // 生产数据
                    buffer.offer(value);
                    System.out.println(name + " 生产了 " + value + "，缓冲区大小：" + buffer.size());
                    value++;
                    // 唤醒所有等待的消费者（或生产者）
                    buffer.notifyAll();
                }
                // 模拟生产耗时
                try { Thread.sleep(100); } catch (InterruptedException e) {}
            }
            System.out.println(name + " 生产结束。");
        }
    }

    // 消费者线程
    static class Consumer implements Runnable {
        private final String name;

        Consumer(String name) {
            this.name = name;
        }

        @Override
        public void run() {
            while (true) {
                synchronized (buffer) {
                    // 缓冲区空，等待生产者
                    while (buffer.isEmpty()) {
                        try {
                            System.out.println(name + " 缓冲区已空，等待...");
                            buffer.wait();
                        } catch (InterruptedException e) {
                            Thread.currentThread().interrupt();
                        }
                    }
                    // 消费数据
                    int value = buffer.poll();
                    System.out.println(name + " 消费了 " + value + "，缓冲区大小：" + buffer.size());
                    buffer.notifyAll();   // 唤醒等待的生产者
                }
                // 模拟消费耗时
                try { Thread.sleep(150); } catch (InterruptedException e) {}
            }
        }
    }

    public static void main(String[] args) {
        // 创建并启动一个生产者线程和两个消费者线程
        Thread producer = new Thread(new Producer("生产者A"));
        Thread consumer1 = new Thread(new Consumer("消费者1"));
        Thread consumer2 = new Thread(new Consumer("消费者2"));

        producer.start();
        consumer1.start();
        consumer2.start();
    }
}
