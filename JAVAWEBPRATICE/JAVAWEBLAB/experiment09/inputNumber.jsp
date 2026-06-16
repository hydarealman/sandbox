<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>MVC模式 - 四则运算</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 50px auto; width: 450px; }
        h2 { text-align: center; color: #333; }
        .calc-box { background: #f5f5f5; padding: 25px; border-radius: 8px; border: 1px solid #ddd; }
        .form-group { margin-bottom: 15px; }
        label { display: block; margin-bottom: 5px; font-weight: bold; }
        input[type="text"], select {
            width: 95%; padding: 8px; border: 1px solid #ccc; border-radius: 4px;
        }
        select { width: 100%; }
        input[type="submit"] {
            width: 100%; padding: 10px; background: #009966; color: white;
            border: none; border-radius: 4px; font-size: 16px; cursor: pointer; margin-top: 10px;
        }
        input[type="submit"]:hover { background: #007a4d; }
        .model-info { font-size: 12px; color: #888; margin-top: 20px; text-align: center; }
    </style>
</head>
<body>
    <h2>MVC模式 - 四则运算计算器</h2>
    <div class="calc-box">
        <form action="handleComputer" method="post">
            <div class="form-group">
                <label>第一个操作数：</label>
                <input type="text" name="operand1" placeholder="请输入第一个数字" required>
            </div>
            <div class="form-group">
                <label>运算符：</label>
                <select name="operator">
                    <option value="+">加法 (+)</option>
                    <option value="-">减法 (-)</option>
                    <option value="*">乘法 (×)</option>
                    <option value="/">除法 (÷)</option>
                </select>
            </div>
            <div class="form-group">
                <label>第二个操作数：</label>
                <input type="text" name="operand2" placeholder="请输入第二个数字" required>
            </div>
            <input type="submit" value="计算">
        </form>
    </div>
    <div class="model-info">
        <p><strong>MVC模式说明：</strong></p>
        <p>M(Model): Computer.java (实体模型) + CalculateBean.java (业务模型)</p>
        <p>V(View): inputNumber.jsp + showResult.jsp (视图)</p>
        <p>C(Controller): HandleComputer.java (Servlet控制器)</p>
    </div>
</body>
</html>
