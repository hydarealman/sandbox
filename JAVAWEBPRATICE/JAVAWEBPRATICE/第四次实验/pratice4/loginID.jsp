<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>会员卡号输入</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .box { border: 1px solid #ccc; padding: 20px; width: 300px; }
    </style>
</head>
<body>
<div class="box">
    <h3>欢迎您来到便民超市，请输入您的会员卡号：</h3>
    <form action="shop.jsp" method="post">
        <input type="text" name="cardId" required>
        <input type="submit" value="提交">
    </form>
</div>
</body>
</html>