package review_pratice;

interface Greeting{
    public void sayHello();
}

class Chinese implements Greeting {
    public void sayHello() {
        System.out.println("你好");
    }
}

public class Test1_interface {
   public static void main(String[] args) {
        Greeting p = new Chinese();
        p.sayHello();
   }
}
// 输出你好
