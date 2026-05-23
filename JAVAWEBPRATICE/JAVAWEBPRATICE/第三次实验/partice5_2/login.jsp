<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>用户登录</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .login-box { width: 300px; padding: 20px; border: 1px solid #ccc; border-radius: 5px; }
        .error { color: red; margin-bottom: 10px; }
        input { margin: 5px; }
    </style>
</head>
<body>
<div class="login-box">
    <h3>用户登录</h3>
    <%
        String error = request.getParameter("error");
        if (error != null && error.equals("1")) {
    %>
        <div class="error">用户名或密码错误，请重新登录！</div>
    <% } %>
    <form action="validate.jsp" method="post">
        <label>用户名：</label> <input type="text" name="username"><br>
        <label>密码：</label> <input type="password" name="password"><br>
        <input type="submit" value="登录">
    </form>
</div>
</body>
</html>