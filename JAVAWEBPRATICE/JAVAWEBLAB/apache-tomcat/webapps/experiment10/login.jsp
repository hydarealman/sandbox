<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>会话跟踪 - 登录注销系统</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 50px auto; width: 420px; }
        h2 { text-align: center; color: #333; }
        .login-box { background: #f5f5f5; padding: 30px; border-radius: 8px; border: 1px solid #ddd; }
        .form-group { margin-bottom: 15px; }
        label { display: block; margin-bottom: 5px; font-weight: bold; }
        input[type="text"], input[type="password"] {
            width: 94%; padding: 8px; border: 1px solid #ccc; border-radius: 4px;
        }
        input[type="submit"] {
            width: 100%; padding: 10px; background: #009966; color: white;
            border: none; border-radius: 4px; font-size: 16px; cursor: pointer;
        }
        input[type="submit"]:hover { background: #007a4d; }
        .error { color: #f44336; text-align: center; margin-top: 10px; }
        .info { color: #2196F3; text-align: center; margin-top: 10px; }
        .hint { font-size: 12px; color: #888; margin-top: 20px; text-align: center; }
    </style>
</head>
<body>
    <h2>用户登录</h2>
    <div class="login-box">
        <form action="login" method="post">
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
            String info = request.getParameter("info");
            if (error != null) {
        %>
            <p class="error"><%= error %></p>
        <% } else if (info != null) { %>
            <p class="info"><%= info %></p>
        <% } %>
    </div>
    <p class="hint">
        提示：输入相同的用户名和密码即可登录（如：admin/admin）<br>
        此系统演示HttpSession会话跟踪技术<br>
        支持URL重写（应对浏览器禁用Cookie的情况）
    </p>
</body>
</html>
