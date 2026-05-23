<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>用户登录</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .login-box { width: 300px; padding: 20px; border: 1px solid #ccc; border-radius: 5px; }
        input { margin: 5px; }
    </style>
</head>
<body>
<div class="login-box">
    <h3>登录系统</h3>
    <form action="server.jsp" method="post">
        <label>用户名：</label> <input type="text" name="username" required><br>
        <label>密码：</label> <input type="password" name="password" required><br>
        <input type="submit" value="登录">
    </form>
</div>
</body>
</html>