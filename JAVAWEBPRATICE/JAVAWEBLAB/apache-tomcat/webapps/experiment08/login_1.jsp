<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>基于Servlet的登录验证</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 50px auto; width: 400px; }
        h2 { text-align: center; color: #333; }
        .login-box { background: #f5f5f5; padding: 30px; border-radius: 8px; border: 1px solid #ddd; }
        .form-group { margin-bottom: 15px; }
        label { display: block; margin-bottom: 5px; font-weight: bold; }
        input[type="text"], input[type="password"] {
            width: 95%; padding: 8px; border: 1px solid #ccc; border-radius: 4px;
        }
        input[type="submit"] {
            width: 100%; padding: 10px; background: #009966; color: white;
            border: none; border-radius: 4px; font-size: 16px; cursor: pointer;
        }
        input[type="submit"]:hover { background: #007a4d; }
        .error { color: #f44336; text-align: center; margin-top: 10px; }
        .hint { font-size: 12px; color: #888; text-align: center; margin-top: 15px; }
    </style>
</head>
<body>
    <h2>Servlet登录验证</h2>
    <div class="login-box">
        <form action="loginServlet_1" method="post">
            <div class="form-group">
                <label>用户名：</label>
                <input type="text" name="username" placeholder="请输入用户名">
            </div>
            <div class="form-group">
                <label>密码：</label>
                <input type="password" name="password" placeholder="请输入密码">
            </div>
            <input type="submit" value="登录">
        </form>
        <%
            String error = request.getParameter("error");
            if (error != null) {
        %>
            <p class="error"><%= error %></p>
        <% } %>
    </div>
    <p class="hint">提示：用户名 zhangsan，密码 123<br>
       此登录由Servlet（LoginServlet_1）处理</p>
</body>
</html>
