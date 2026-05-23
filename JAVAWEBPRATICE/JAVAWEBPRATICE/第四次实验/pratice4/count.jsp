<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.util.*" %>
<%
    String cardId = (String) session.getAttribute("memberCard");
    if (cardId == null) {
        response.sendRedirect("loginID.jsp");
        return;
    }
    List<String> cart = (List<String>) session.getAttribute("shoppingCart");
    if (cart == null) {
        cart = new ArrayList<>();
    }
%>
<html>
<head>
    <title>结账柜台</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .info { background: #f5f5f5; padding: 15px; border-radius: 5px; }
        ul { list-style-type: none; padding-left: 0; }
        li { margin: 5px 0; }
    </style>
</head>
<body>
<div class="info">
    <h3>这里是结帐柜台，请确认以下信息。</h3>
    <p>您的会员卡号：<strong><%= cardId %></strong></p>
    <p>购物车中的商品清单：</p>
    <ul>
        <% if (cart.isEmpty()) { %>
            <li>（空）</li>
        <% } else {
            for (String item : cart) { %>
                <li> <%= item %> </li>
        <%   }
           } %>
    </ul>
    <p>
        <a href="loginID.jsp">欢迎修改会员卡号！</a> |
        <a href="food.jsp">欢迎来到调料柜台！</a>
    </p>
</div>
</body>
</html>