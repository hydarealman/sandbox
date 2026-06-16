package beans;

public class Triangle {
    private double sideA;
    private double sideB;
    private double sideC;

    public Triangle() {}

    public double getSideA() { return sideA; }
    public void setSideA(double sideA) { this.sideA = sideA; }

    public double getSideB() { return sideB; }
    public void setSideB(double sideB) { this.sideB = sideB; }

    public double getSideC() { return sideC; }
    public void setSideC(double sideC) { this.sideC = sideC; }

    /** 判断是否为合法三角形 */
    public boolean isValid() {
        return (sideA + sideB > sideC) &&
               (sideA + sideC > sideB) &&
               (sideB + sideC > sideA);
    }

    /** 计算周长 */
    public double getPerimeter() {
        if (!isValid()) return 0;
        return sideA + sideB + sideC;
    }

    /** 计算面积（海伦公式） */
    public double getArea() {
        if (!isValid()) return 0;
        double s = (sideA + sideB + sideC) / 2.0;
        return Math.sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
    }
}
