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
        String error = request.getParameter("error");
        if ("invalid".equals(error)) {
    %>
        <div class="error">用户名或密码错误！</div>
    <%
        } else if ("logout".equals(error)) {
    %>
        <div class="error">您已成功注销，请重新登录。</div>
    <%
        } else if ("needLogin".equals(error)) {
    %>
        <div class="error">请先登录后再访问！</div>
    <%
        }
    %>
    <form action="<%= response.encodeURL("LoginServlet") %>" method="post">
        <label>用户名：</label> <input type="text" name="username" required><br>
        <label>密码：</label> <input type="password" name="password" required><br>
        <input type="submit" value="登录">
    </form>
</div>
</body>
</html>