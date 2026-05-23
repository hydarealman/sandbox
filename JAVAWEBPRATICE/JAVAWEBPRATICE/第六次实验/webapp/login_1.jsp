<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>登录</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .login-box { border: 1px solid #ccc; padding: 20px; width: 300px; background: #f9f9f9; }
        .error { color: red; }
        input { margin: 5px; }
    </style>
</head>
<body>
<div class="login-box">
    <h3>用户登录</h3>
    <%
        String errorMsg = request.getParameter("error");
        if ("incomplete".equals(errorMsg)) {
    %>
        <div class="error">用户名和密码不能为空！</div>
    <%
        } else if ("invalid".equals(errorMsg)) {
    %>
        <div class="error">用户名或密码错误！</div>
    <%
        }
    %>
    <form action="loginServlet_1" method="post">
        <label>用户名：</label> <input type="text" name="username" required><br>
        <label>密码：</label> <input type="password" name="password" required><br>
        <input type="submit" value="登录">
    </form>
</div>
</body>
</html>