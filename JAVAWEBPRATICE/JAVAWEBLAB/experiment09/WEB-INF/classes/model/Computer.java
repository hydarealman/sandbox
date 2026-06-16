package model;

/** 实体模型 - 存储计算数据 */
public class Computer {
    private double operand1;
    private double operand2;
    private String operator;
    private double result;

    public Computer() {}

    public double getOperand1() { return operand1; }
    public void setOperand1(double operand1) { this.operand1 = operand1; }

    public double getOperand2() { return operand2; }
    public void setOperand2(double operand2) { this.operand2 = operand2; }

    public String getOperator() { return operator; }
    public void setOperator(String operator) { this.operator = operator; }

    public double getResult() { return result; }
    public void setResult(double result) { this.result = result; }
}
