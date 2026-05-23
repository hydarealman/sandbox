<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>计算结果</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .result { border: 1px solid green; padding: 20px; background: #e8f8e8; width: 400px; }
    </style>
</head>
<body>
<div class="result">
    <h3>计算结果</h3>
    <jsp:useBean id="computer" class="Computer" scope="request" />
    <%
        // 从 request 中获取 computer 对象（Servlet 已经存入）
        Computer comp = (Computer) request.getAttribute("computer");
        if (comp != null) {
    %>
        <p><%= comp.getNum1() %> <%= comp.getOperator() %> <%= comp.getNum2() %> = <strong><%= comp.getResult() %></strong></p>
    <% } else { %>
        <p style="color:red">没有计算结果，请返回重新输入。</p>
    <% } %>
    <p><a href="inputNumber.jsp">返回重新计算</a></p>
</div>
</body>
</html>