<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>登录成功</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .success { color: green; font-size: 20px; }
    </style>
</head>
<body>
<div class="success">
    <h3>登录成功！</h3>
    <p>欢迎用户：<%= request.getParameter("username") != null ? request.getParameter("username") : "tom" %></p>
    <p><a href="login.jsp">返回登录页面</a></p>
</div>
</body>
</html>