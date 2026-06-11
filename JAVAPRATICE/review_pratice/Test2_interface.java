package review_pratice;

interface Calculator {
    public int add(int a, int b);
}

class Myclc implements Calculator{
    public int add(int a,int b) {
        return a + b;
    }
}

public class Test2_interface {
    public static void main(String[] args) {
        Calculator p = new Myclc();
        int result = p.add(10,20);
        System.out.println(result);
    }
}
