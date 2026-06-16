<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>计算结果</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 50px auto; width: 500px; text-align: center; }
        .result-box { background: #e8f5e9; padding: 30px; border-radius: 8px; border: 2px solid #4CAF50; }
        .error-box { background: #ffebee; padding: 30px; border-radius: 8px; border: 2px solid #f44336; }
        h2 { color: #006633; }
        .equation { font-size: 28px; font-weight: bold; color: #006633; margin: 20px 0; }
        .error-msg { color: #f44336; font-size: 16px; }
        .back-link { display: inline-block; margin-top: 20px; padding: 10px 25px;
            background: #009966; color: white; text-decoration: none; border-radius: 4px; }
        .back-link:hover { background: #007a4d; }
        .info { font-size: 12px; color: #888; margin-top: 15px; }
    </style>
</head>
<body>
    <%
        String error = (String) request.getAttribute("error");
        if (error != null) {
    %>
        <div class="error-box">
            <h2 style="color:#f44336;">计算出错</h2>
            <p class="error-msg"><%= error %></p>
        </div>
    <% } else { %>
        <div class="result-box">
            <h2>计算结果</h2>
            <p class="equation">
                <%= request.getAttribute("operand1") %>
                <%= request.getAttribute("operator") %>
                <%= request.getAttribute("operand2") %>
                =
                <span style="color:#ff6600;"><%= request.getAttribute("result") %></span>
            </p>
            <p style="color:#666; font-size:14px;">
                计算时间：<%= new java.util.Date() %>
            </p>
        </div>
    <% } %>
    <a href="inputNumber.jsp" class="back-link">← 返回继续计算</a>
    <p class="info">基于Servlet的MVC模式实现 - Model-View-Controller</p>
</body>
</html>
