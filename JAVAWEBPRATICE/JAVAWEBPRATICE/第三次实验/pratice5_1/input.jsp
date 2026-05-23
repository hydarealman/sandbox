<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>动态包含演示</title>
    <style>
        body { font-family: Arial; margin: 20px; }
        .param-form { margin-bottom: 30px; padding: 10px; background: #f0f0f0; border-radius: 5px; }
        .param-form label { display: inline-block; width: 80px; }
        .param-form input { margin: 5px; }
        .section { margin: 20px 0; border: 1px solid #ccc; padding: 10px; border-radius: 5px; }
    </style>
</head>
<body>
<h2>JSP动作标记应用 - include与param</h2>

<div class="param-form">
    <h3>设置参数</h3>
    <form method="get" action="input.jsp">
        <label>表格行数:</label> <input type="number" name="rows" value="<%= request.getParameter("rows") == null ? "4" : request.getParameter("rows") %>" min="1"><br>
        <label>表格列数:</label> <input type="number" name="cols" value="<%= request.getParameter("cols") == null ? "5" : request.getParameter("cols") %>" min="1"><br>
        <label>正整数A:</label> <input type="number" name="num1" value="<%= request.getParameter("num1") == null ? "12" : request.getParameter("num1") %>" min="1"><br>
        <label>正整数B:</label> <input type="number" name="num2" value="<%= request.getParameter("num2") == null ? "18" : request.getParameter("num2") %>" min="1"><br>
        <input type="submit" value="更新参数并重新加载">
    </form>
</div>

<div class="section">
    <h3>动态表格（first.jsp）</h3>
    <jsp:include page="first.jsp">
        <jsp:param name="rows" value="<%= request.getParameter("rows") == null ? "4" : request.getParameter("rows") %>"/>
        <jsp:param name="cols" value="<%= request.getParameter("cols") == null ? "5" : request.getParameter("cols") %>"/>
    </jsp:include>
</div>

<div class="section">
    <h3>最大公约数计算（second.jsp）</h3>
    <jsp:include page="second.jsp">
        <jsp:param name="num1" value="<%= request.getParameter("num1") == null ? "12" : request.getParameter("num1") %>"/>
        <jsp:param name="num2" value="<%= request.getParameter("num2") == null ? "18" : request.getParameter("num2") %>"/>
    </jsp:include>
</div>

</body>
</html>