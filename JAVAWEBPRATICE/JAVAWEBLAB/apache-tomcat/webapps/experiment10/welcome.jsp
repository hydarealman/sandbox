<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
    // 检查是否已登录
    String username = (String) session.getAttribute("username");
    if (username == null) {
        // 未登录，使用URL重写进行重定向
        response.sendRedirect(response.encodeRedirectURL("login.jsp?error=请先登录！"));
        return;
    }
%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>欢迎 - 会话跟踪系统</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 30px auto; width: 600px; }
        h1 { text-align: center; color: #006633; }
        .welcome-box { background: #e8f5e9; padding: 25px; border-radius: 8px; border: 2px solid #4CAF50; margin: 15px 0; }
        .info-table { width: 100%; border-collapse: collapse; margin: 15px 0; }
        .info-table th, .info-table td { padding: 8px; border: 1px solid #ddd; text-align: left; }
        .info-table th { background: #009966; color: white; width: 35%; }
        .nav-links { display: flex; justify-content: center; gap: 15px; margin-top: 20px; }
        .nav-links a { padding: 10px 20px; text-decoration: none; border-radius: 4px; font-size: 14px; }
        .profile-btn { background: #2196F3; color: white; }
        .logout-btn { background: #f44336; color: white; }
        .nav-links a:hover { opacity: 0.8; }
    </style>
</head>
<body>
    <h1>欢迎使用会话跟踪系统</h1>

    <div class="welcome-box">
        <p style="font-size:18px; text-align:center;">
            您好，<strong><%= username %></strong>！欢迎回来！
        </p>
        <table class="info-table">
            <tr><th>会话信息</th><th>值</th></tr>
            <tr><td>用户名</td><td><strong><%= username %></strong></td></tr>
            <tr><td>Session ID</td><td style="font-size:11px; word-break:break-all;"><%= session.getAttribute("sessionId") %></td></tr>
            <tr><td>登录时间</td><td><%= session.getAttribute("loginTime") %></td></tr>
            <tr><td>Session创建时间</td><td><%= new java.util.Date(session.getCreationTime()) %></td></tr>
            <tr><td>最后访问时间</td><td><%= new java.util.Date(session.getLastAccessedTime()) %></td></tr>
            <tr><td>最大不活动间隔</td><td><%= session.getMaxInactiveInterval() %> 秒</td></tr>
            <tr><td>当前时间</td><td><%= new java.util.Date() %></td></tr>
        </table>

        <p style="font-size:12px; color:#666; text-align:center;">
            您的登录状态保存在HttpSession中<br>
            关闭浏览器或注销后，Session将失效
        </p>
    </div>

    <div class="nav-links">
        <a href="<%= response.encodeURL("profile.jsp") %>" class="profile-btn">查看个人信息</a>
        <a href="<%= response.encodeURL("logout") %>" class="logout-btn">注销登录</a>
    </div>

    <p style="text-align:center; color:#888; font-size:12px; margin-top:20px;">
        所有链接使用 response.encodeURL() 进行URL重写<br>
        确保在浏览器禁用Cookie时仍能正常使用Session
    </p>
</body>
</html>
