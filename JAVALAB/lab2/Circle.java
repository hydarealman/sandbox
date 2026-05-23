package JAVALAB.lab2;

public class Circle extends Geometry {
    double r;

    Circle(double r) {
        this.r = r;
    }

    public double getArea() {
        return Math.PI * r * r;
    }
}