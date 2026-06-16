<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>用户登录</title>
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
            width: 100%; padding: 10px; background-color: #009966;
            color: white; border: none; border-radius: 4px; font-size: 16px; cursor: pointer;
        }
        input[type="submit"]:hover { background-color: #007a4d; }
        .error { color: red; text-align: center; margin-top: 10px; }
    </style>
</head>
<body>
    <h2>用户登录（Forward动作）</h2>
    <div class="login-box">
        <form action="validate.jsp" method="post">
            <div class="form-group">
                <label>用户名：</label>
                <input type="text" name="username" placeholder="请输入用户名" required>
            </div>
            <div class="form-group">
                <label>密码：</label>
                <input type="password" name="password" placeholder="请输入密码" required>
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
    <p style="text-align:center; color:#888; font-size:12px; margin-top:15px;">提示：用户名tom，密码jenny</p>
</body>
</html>
