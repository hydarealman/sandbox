<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    // 获取或创建 session
    String cardId = request.getParameter("cardId");
    if (cardId != null && !cardId.trim().isEmpty()) {
        session.setAttribute("memberCard", cardId);
    } else {
        cardId = (String) session.getAttribute("memberCard");
        if (cardId == null) {
            // 未登录，重定向到登录页
            response.sendRedirect("loginID.jsp");
            return;
        }
    }
%>
<html>
<head>
    <title>导购页面</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        a { margin-right: 15px; }
    </style>
</head>
<body>
<h3>这里是调料柜台，欢迎选购您喜欢的调料。</h3>
<p>欢迎修改会员卡号！</p>
<p>
    <a href="food.jsp">去购物</a>
    <a href="count.jsp">查看购物车</a>
    <a href="loginID.jsp">修改会员卡号</a>
</p>
</body>
</html>