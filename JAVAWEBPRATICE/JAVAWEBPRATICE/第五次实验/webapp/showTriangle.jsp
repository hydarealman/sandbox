<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>三角形信息</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .result { border: 1px solid #ccc; padding: 20px; width: 400px; background: #f0f8ff; }
    </style>
</head>
<body>
<div class="result">
    <h3>三角形的三边是：</h3>
    <jsp:useBean id="tri" class="Triangle" scope="request" />
    <jsp:setProperty name="tri" property="*" />

    <p>边A: <jsp:getProperty name="tri" property="a" />
       边B: <jsp:getProperty name="tri" property="b" />
       边C: <jsp:getProperty name="tri" property="c" /></p>

    <p>这三个边能构成一个三角形吗？ <strong><%= tri.isTriangle() %></strong></p>

    <% if (tri.isTriangle()) { %>
        <p>周长是：<%= tri.getPerimeter() %></p>
        <p>面积是：<%= tri.getArea() %></p>
    <% } else { %>
        <p style="color:red">无法构成三角形，请返回重新输入边长。</p>
    <% } %>

    <p><a href="inputTriangle.jsp">返回重新输入</a></p>
</div>
</body>
</html>