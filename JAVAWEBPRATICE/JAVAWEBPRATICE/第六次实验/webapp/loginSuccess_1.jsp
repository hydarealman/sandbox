<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>登录成功</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .success { border: 1px solid green; padding: 20px; background: #e0ffe0; width: 400px; }
    </style>
</head>
<body>
<div class="success">
    <h3>登录成功！</h3>
    <p>欢迎用户：<%= request.getAttribute("loginUser") != null ? request.getAttribute("loginUser") : "zhangsan" %></p>
    <p>您输入的用户名：<%= request.getParameter("username") %></p>
    <p><a href="login_1.jsp">返回登录页</a></p>
</div>
</body>
</html>