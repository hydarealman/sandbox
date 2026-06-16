<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>JSP动作标记 - include和param</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px auto; width: 650px; }
        h1 { text-align: center; color: #333; }
        .section { background: #f9f9f9; padding: 15px; margin: 15px 0; border-radius: 8px; border: 1px solid #ddd; }
        .section h3 { color: #006633; margin-top: 0; }
    </style>
</head>
<body>
    <h1>实验五 JSP动作标记的应用</h1>
    <p style="text-align:center;">本页面使用 &lt;jsp:include&gt; 动作标记加载子页面</p>

    <div class="section">
        <h3>1. first.jsp - 表格绘制（include+param）</h3>
        <jsp:include page="first.jsp">
            <jsp:param name="rows" value="5" />
            <jsp:param name="cols" value="3" />
        </jsp:include>
    </div>

    <div class="section">
        <h3>2. second.jsp - 最大公约数计算（include+param）</h3>
        <jsp:include page="second.jsp">
            <jsp:param name="num1" value="48" />
            <jsp:param name="num2" value="18" />
        </jsp:include>
    </div>
</body>
</html>
