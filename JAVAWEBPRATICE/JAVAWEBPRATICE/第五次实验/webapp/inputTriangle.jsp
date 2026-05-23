<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>输入三角形三边</title>
    <style>
        body { font-family: Arial; margin: 40px; }
        .form-box { border: 1px solid #ccc; padding: 20px; width: 300px; background: #f9f9f9; }
        input { margin: 5px; width: 60px; }
    </style>
</head>
<body>
<div class="form-box">
    <h3>输入三角形三边：</h3>
    <form action="showTriangle.jsp" method="post">
        <label>边A：</label> <input type="text" name="a" required><br>
        <label>边B：</label> <input type="text" name="b" required><br>
        <label>边C：</label> <input type="text" name="c" required><br>
        <input type="submit" value="提交">
    </form>
</div>
</body>
</html>