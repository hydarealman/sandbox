package JAVALAB.lab1;

public class Helo {
  public static void main(String args[]) {
    System.out.println("你好,很高兴学习JAVA");
    A a = new A();
    a.fA();
  } 

  static class A{
    void fA() {
        System.out.println("我是(your name)");
    }
  }
}
