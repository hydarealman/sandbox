package model;

/** 业务模型 - 执行计算逻辑 */
public class CalculateBean {

    /** 对Computer实体进行计算 */
    public void calculate(Computer computer) {
        double num1 = computer.getOperand1();
        double num2 = computer.getOperand2();
        String op = computer.getOperator();
        double result;

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
                if (num2 == 0) {
                    throw new ArithmeticException("除数不能为零！");
                }
                result = num1 / num2;
                break;
            default:
                throw new IllegalArgumentException("不支持的运算符：" + op);
        }
        computer.setResult(result);
    }
}
