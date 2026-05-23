package JAVALAB.lab2;

public class Estimator {
    public static void main(String args[]) {
        double a[] = {9.89, 9.88, 9.99, 9.12, 9.69, 9.76, 8.97};
        double b[] = {56, 55, 5, 65, 50, 51, 5, 53, 6, 70, 49, 66, 62, 46};
        ComprerAverage computer;
        computer = new SongGame();
        double result = computer.average(a);
        System.out.println("********************************");
        System.out.printf("歌手最后得分：%5.3f\n", result);
        computer = new School();
        result = computer.average(b);
        System.out.printf("学生平均体重：%5.2fkg", result);
    }
}