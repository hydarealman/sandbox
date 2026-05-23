<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>四则运算计算器</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .form-box { border: 1px solid #ccc; padding: 20px; width: 400px; background: #f9f9f9; }
        input, select { margin: 5px; }
        .error { color: red; }
    </style>
</head>
<body>
<div class="form-box">
    <h3>简易计算器</h3>
    <%
        String error = (String) request.getAttribute("error");
        if (error != null) {
    %>
        <div class="error"><%= error %></div>
    <%
        }
    %>
    <form action="HandleComputer" method="post">
        <label>数字1：</label> <input type="text" name="num1" required><br>
        <label>运算符：</label>
        <select name="operator">
            <option value="+">+</option>
            <option value="-">-</option>
            <option value="*">*</option>
            <option value="/">/</option>
        </select><br>
        <label>数字2：</label> <input type="text" name="num2" required><br>
        <input type="submit" value="计算">
    </form>
</div>
</body>
</html>