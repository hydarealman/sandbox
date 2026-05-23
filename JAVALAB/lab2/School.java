package JAVALAB.lab2;

public class School implements ComprerAverage {
    public double average(double x[]) {
        double sum = 0;
        for (int i = 0; i < x.length; i++) {
            sum += x[i];
        }
        return sum / x.length;
    }
}