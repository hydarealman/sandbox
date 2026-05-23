package JAVALAB.lab2;

public class MainClass {
    public static void main(String args[]) {
        Geometry[] tuxing = new Geometry[29];
        for (int i = 0; i < tuxing.length; i++) {
            if (i % 2 == 0)
                tuxing[i] = new Rect(16 + i, 68);
            else if (i % 2 == 1)
                tuxing[i] = new Circle(10 + i);
        }
        TotalArea computer = new TotalArea();
        computer.setTuxing(tuxing);
        System.out.printf("各种图形的面积之和：%f", computer.computerTotalArea());
    }
}