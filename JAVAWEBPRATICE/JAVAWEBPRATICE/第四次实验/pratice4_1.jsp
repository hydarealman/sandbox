<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>客户端基本信息</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .info { border: 1px solid #ccc; padding: 20px; width: 400px; background: #f9f9f9; }
        .info p { margin: 8px 0; }
    </style>
</head>
<body>
<div class="info">
    <h3>客户端基本信息</h3>
    <p>客户端的 IP 地址：<%= request.getRemoteAddr() %></p>
    <p>客户机名称：<%= request.getRemoteHost() %></p>
    <p>服务器名称：<%= request.getServerName() %></p>
    <p>服务器端口号：<%= request.getServerPort() %></p>
</div>
</body>
</html>