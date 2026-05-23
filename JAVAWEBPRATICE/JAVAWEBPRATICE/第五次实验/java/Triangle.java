public class Triangle {
    private double a;
    private double b;
    private double c;

    public Triangle() {
        // 无参构造方法
    }

    public double getA() {
        return a;
    }

    public void setA(double a) {
        this.a = a;
    }

    public double getB() {
        return b;
    }

    public void setB(double b) {
        this.b = b;
    }

    public double getC() {
        return c;
    }

    public void setC(double c) {
        this.c = c;
    }

    /**
     * 判断是否构成三角形
     */
    public boolean isTriangle() {
        if (a <= 0 || b <= 0 || c <= 0) {
            return false;
        }
        return (a + b > c) && (a + c > b) && (b + c > a);
    }

    /**
     * 计算周长
     */
    public double getPerimeter() {
        if (!isTriangle()) {
            return 0;
        }
        return a + b + c;
    }

    /**
     * 计算面积（海伦公式）
     */
    public double getArea() {
        if (!isTriangle()) {
            return 0;
        }
        double p = (a + b + c) / 2;  // 半周长
        return Math.sqrt(p * (p - a) * (p - b) * (p - c));
    }
}