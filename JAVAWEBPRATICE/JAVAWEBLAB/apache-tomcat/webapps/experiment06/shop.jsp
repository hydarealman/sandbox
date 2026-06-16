<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>简单购物车 - Session应用</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px auto; width: 600px; }
        h2 { text-align: center; }
        .product { background: #f5f5f5; padding: 10px; margin: 10px 0; border-radius: 8px; display: flex; justify-content: space-between; align-items: center; }
        .product span { font-size: 16px; }
        .cart { background: #e8f5e9; padding: 15px; border-radius: 8px; margin-top: 20px; }
        .cart h3 { margin-top: 0; color: #006633; }
        .btn {
            padding: 6px 15px; background: #009966; color: white; border: none;
            border-radius: 4px; cursor: pointer; text-decoration: none; font-size: 13px;
        }
        .btn:hover { background: #007a4d; }
        .clear-btn { background: #f44336; }
        .clear-btn:hover { background: #da190b; }
        table { width: 100%; border-collapse: collapse; margin-top: 10px; }
        th, td { border: 1px solid #ddd; padding: 6px; text-align: center; }
        th { background: #009966; color: white; }
    </style>
</head>
<body>
    <h2>简单购物车 (Session对象应用)</h2>

    <%
        // 使用session保存购物车
        java.util.Map<String, Integer> cart = (java.util.Map<String, Integer>) session.getAttribute("cart");
        if (cart == null) {
            cart = new java.util.HashMap<String, Integer>();
            session.setAttribute("cart", cart);
        }

        // 处理添加商品
        String addItem = request.getParameter("add");
        if (addItem != null && !addItem.isEmpty()) {
            cart.put(addItem, cart.getOrDefault(addItem, 0) + 1);
        }
        // 处理清空购物车
        String clear = request.getParameter("clear");
        if (clear != null) {
            cart.clear();
        }
    %>

    <h3>商品列表：</h3>
    <div class="product">
        <span>📕 Java编程思想</span>
        <a href="?add=Java编程思想" class="btn">加入购物车</a>
    </div>
    <div class="product">
        <span>📗 JSP实战指南</span>
        <a href="?add=JSP实战指南" class="btn">加入购物车</a>
    </div>
    <div class="product">
        <span>📘 Servlet核心技术</span>
        <a href="?add=Servlet核心技术" class="btn">加入购物车</a>
    </div>
    <div class="product">
        <span>📙 Web开发大全</span>
        <a href="?add=Web开发大全" class="btn">加入购物车</a>
    </div>

    <div class="cart">
        <h3>购物车内容：</h3>
        <% if (cart.isEmpty()) { %>
            <p>购物车为空</p>
        <% } else { %>
            <table>
                <tr><th>商品名称</th><th>数量</th></tr>
                <%
                    for (java.util.Map.Entry<String, Integer> entry : cart.entrySet()) {
                        out.println("<tr><td>" + entry.getKey() + "</td><td>" + entry.getValue() + "</td></tr>");
                    }
                %>
            </table>
            <p>总计：<strong><%= cart.size() %></strong> 种商品</p>
        <% } %>
        <a href="?clear=true" class="btn clear-btn">清空购物车</a>
        <a href="index.jsp" class="btn">返回首页</a>
    </div>

    <p style="margin-top:15px; font-size:12px; color:#888;">
        Session ID: <%= session.getId() %><br>
        购物车数据存储在HttpSession对象中
    </p>
</body>
</html>
