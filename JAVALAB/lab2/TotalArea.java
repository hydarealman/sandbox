package JAVALAB.lab2;

public class TotalArea {
    Geometry[] tuxing;
    double totalArea = 0;

    public void setTuxing(Geometry[] t) {
        tuxing = t;
    }

    public double computerTotalArea() {
        for (int i = 0; i < tuxing.length; i++) {
            totalArea += tuxing[i].getArea();
        }
        return totalArea;
    }
}