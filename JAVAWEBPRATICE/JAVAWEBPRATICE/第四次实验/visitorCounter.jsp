<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>网站访客计数器</title>
    <style>
        body { font-family: Arial; margin: 40px; text-align: center; }
        .count { font-size: 30px; color: blue; margin: 20px; }
    </style>
</head>
<body>
<%
    Integer count = (Integer) application.getAttribute("visitCount");
    if (count == null) {
        count = 1;
    } else {
        count++;
    }
    application.setAttribute("visitCount", count);
%>
<h3>欢迎访问本网站</h3>
<div class="count">您是第 <%= count %> 位访客</div>
<p>（刷新页面计数器会增加）</p>
</body>
</html>