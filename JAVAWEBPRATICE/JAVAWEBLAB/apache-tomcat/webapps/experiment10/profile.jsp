<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
    String username = (String) session.getAttribute("username");
    if (username == null) {
        response.sendRedirect(response.encodeRedirectURL("login.jsp?error=请先登录！"));
        return;
    }
%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>个人信息 - 会话跟踪系统</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 30px auto; width: 550px; }
        h1 { text-align: center; color: #2196F3; }
        .profile-box { background: #e3f2fd; padding: 25px; border-radius: 8px; border: 2px solid #2196F3; }
        .info-table { width: 100%; border-collapse: collapse; margin: 15px 0; }
        .info-table th, .info-table td { padding: 8px; border: 1px solid #ddd; text-align: left; }
        .info-table th { background: #2196F3; color: white; width: 35%; }
        .nav-links { display: flex; justify-content: center; gap: 15px; margin-top: 20px; }
        .nav-links a { padding: 10px 20px; text-decoration: none; border-radius: 4px; font-size: 14px; }
        .home-btn { background: #009966; color: white; }
        .logout-btn { background: #f44336; color: white; }
        .nav-links a:hover { opacity: 0.8; }
    </style>
</head>
<body>
    <h1>个人信息中心</h1>

    <div class="profile-box">
        <h3 style="text-align:center;">用户资料</h3>
        <table class="info-table">
            <tr><th>属性</th><th>值</th></tr>
            <tr><td>用户名</td><td><strong><%= username %></strong></td></tr>
            <tr><td>登录时间</td><td><%= session.getAttribute("loginTime") %></td></tr>
            <tr><td>当前Session ID</td><td style="font-size:10px; word-break:break-all;"><%= session.getId() %></td></tr>
            <tr><td>会话是否新建</td><td><%= session.isNew() ? "是" : "否" %></td></tr>
            <tr><td>请求编码URL</td><td style="font-size:10px; word-break:break-all;"><%= response.encodeURL("profile.jsp") %></td></tr>
        </table>
    </div>

    <div class="nav-links">
        <a href="<%= response.encodeURL("welcome.jsp") %>" class="home-btn">返回首页</a>
        <a href="<%= response.encodeURL("logout") %>" class="logout-btn">注销登录</a>
    </div>

    <div style="margin-top:20px; font-size:12px; color:#888; padding:10px; background:#f9f9f9; border-radius:8px;">
        <strong>会话跟踪技术说明：</strong><br>
        1. 本系统使用HttpSession进行会话跟踪<br>
        2. 用户信息保存在session对象中<br>
        3. 使用 response.encodeURL() 实现URL重写<br>
        4. 注销时调用 session.invalidate() 清除所有会话数据<br>
        5. 支持浏览器禁用Cookie的场景
    </div>
</body>
</html>
