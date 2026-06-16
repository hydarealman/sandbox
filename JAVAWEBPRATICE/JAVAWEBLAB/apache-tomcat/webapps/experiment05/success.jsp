<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>登录成功</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 50px auto; width: 500px; text-align: center; }
        .success-box { background: #e8f5e9; padding: 30px; border-radius: 8px; border: 2px solid #4CAF50; }
        h2 { color: #006633; }
        .info { font-size: 16px; color: #333; }
        .back-link { margin-top: 20px; display: block; color: #009966; text-decoration: none; }
    </style>
</head>
<body>
    <div class="success-box">
        <h2>登录成功！</h2>
        <p class="info">
            欢迎您，<strong><%= request.getParameter("username") %></strong>！
        </p>
        <p>您已成功通过JSP forward动作跳转到此页面。</p>
        <p style="font-size:12px; color:#888;">
            当前时间：<%= new java.util.Date() %>
        </p>
    </div>
    <a href="login.jsp" class="back-link">返回登录页面</a>
</body>
</html>
