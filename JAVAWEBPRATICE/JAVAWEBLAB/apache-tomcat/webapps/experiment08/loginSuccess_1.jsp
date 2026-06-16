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
        .info strong { color: #006633; }
        .back-link { display: inline-block; margin-top: 20px; padding: 8px 20px;
            background: #009966; color: white; text-decoration: none; border-radius: 4px; }
        .back-link:hover { background: #007a4d; }
    </style>
</head>
<body>
    <div class="success-box">
        <h2>登录成功！</h2>
        <p class="info">
            欢迎您，<strong><%= request.getParameter("username") %></strong>！
        </p>
        <p class="info">
            您的密码是：<strong><%= request.getParameter("password") %></strong>
        </p>
        <p style="font-size:14px; color:#666;">
            此页面通过Servlet的RequestDispatcher.forward()方法转发而来
        </p>
        <p style="font-size:12px; color:#888;">当前时间：<%= new java.util.Date() %></p>
    </div>
    <a href="login_1.jsp" class="back-link">返回登录页</a>

    <div style="margin-top:20px; font-size:12px; color:#888;">
        <p><strong>重定向 vs 转发：</strong></p>
        <p>重定向(sendRedirect)：浏览器重新发请求，URL会变化，request数据会丢失</p>
        <p>转发(forward)：服务器内部跳转，URL不变，request数据可以保留</p>
    </div>
</body>
</html>
