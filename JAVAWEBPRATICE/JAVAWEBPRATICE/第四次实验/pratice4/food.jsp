<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="java.util.*" %>
<%
    // 检查是否已登录（session中有会员卡号）
    String cardId = (String) session.getAttribute("memberCard");
    if (cardId == null) {
        response.sendRedirect("loginID.jsp");
        return;
    }

    // 处理添加商品到购物车
    String[] selectedItems = request.getParameterValues("item");
    if (selectedItems != null && selectedItems.length > 0) {
        List<String> cart = (List<String>) session.getAttribute("shoppingCart");
        if (cart == null) {
            cart = new ArrayList<>();
            session.setAttribute("shoppingCart", cart);
        }
        for (String item : selectedItems) {
            cart.add(item);
        }
        // 添加完成后，重定向回本页面刷新商品列表，避免重复提交
        response.sendRedirect("food.jsp");
        return;
    }
%>
<html>
<head>
    <title>购物页面</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .item-list { margin: 20px 0; }
        .item-list label { margin-right: 15px; }
        input[type="checkbox"] { margin-right: 5px; }
    </style>
</head>
<body>
<h3>这里是调料柜台，请选择您要购买的调料：</h3>
<form method="post" action="food.jsp">
    <div class="item-list">
        <label><input type="checkbox" name="item" value="调和油"> 调和油</label>
        <label><input type="checkbox" name="item" value="强化盐"> 强化盐</label>
        <label><input type="checkbox" name="item" value="多维醋"> 多维醋</label>
        <label><input type="checkbox" name="item" value="绿色调料"> 绿色调料</label>
    </div>
    <input type="submit" value="购物">
</form>
<p>
    <a href="shop.jsp">欢迎修改会员卡号！</a> |
    <a href="count.jsp">欢迎查看购物车！</a>
</p>
</body>
</html>