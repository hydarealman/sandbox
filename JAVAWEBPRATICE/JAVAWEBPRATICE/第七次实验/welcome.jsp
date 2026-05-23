<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    // 检查是否已登录
    String loginUser = (String) session.getAttribute("loginUser");
    if (loginUser == null) {
        response.sendRedirect(response.encodeRedirectURL("login.jsp?error=needLogin"));
        return;
    }
%>
<html>
<head>
    <title>欢迎页</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .welcome { border: 1px solid green; padding: 20px; background: #e8f8e8; width: 400px; }
        a { margin-right: 15px; }
    </style>
</head>
<body>
<div class="welcome">
    <h3>登录成功！</h3>
    <p>欢迎您，<strong><%= loginUser %></strong>！</p>
    <p>您的会话 ID：<%= session.getId() %></p>
    <p>
        <a href="<%= response.encodeURL("profile.jsp") %>">查看个人信息</a>
        <a href="<%= response.encodeURL("LogoutServlet") %>">注销</a>
    </p>
</div>
</body>
</html>