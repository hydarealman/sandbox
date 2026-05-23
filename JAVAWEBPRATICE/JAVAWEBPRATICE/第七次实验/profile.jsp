<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    String loginUser = (String) session.getAttribute("loginUser");
    if (loginUser == null) {
        response.sendRedirect(response.encodeRedirectURL("login.jsp?error=needLogin"));
        return;
    }
%>
<html>
<head>
    <title>个人信息</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .info { border: 1px solid blue; padding: 20px; background: #e8f0fe; width: 400px; }
    </style>
</head>
<body>
<div class="info">
    <h3>用户个人信息</h3>
    <p>当前登录用户：<strong><%= loginUser %></strong></p>
    <p>您的会话 ID：<%= session.getId() %></p>
    <p>（此页面展示了从 HttpSession 中获取的用户信息，证明会话跟踪有效。）</p>
    <p>
        <a href="<%= response.encodeURL("welcome.jsp") %>">返回首页</a>
        <a href="<%= response.encodeURL("LogoutServlet") %>">注销</a>
    </p>
</div>
</body>
</html>