package JAVAWEBPRATICE.JAVAWEBPRATICE.第六次实验.java2;

public class CalculateBean {
    public void calculate(Computer computer) {
        double num1 = computer.getNum1();
        double num2 = computer.getNum2();
        String op = computer.getOperator();
        double result = 0;

        if (op == null) return;

        switch (op) {
            case "+":
                result = num1 + num2;
                break;
            case "-":
                result = num1 - num2;
                break;
            case "*":
                result = num1 * num2;
                break;
            case "/":
                if (num2 != 0) {
                    result = num1 / num2;
                } else {
                    throw new ArithmeticException("除数不能为零");
                }
                break;
            default:
                throw new UnsupportedOperationException("不支持的运算符");
        }
        computer.setResult(result);
    }
}
