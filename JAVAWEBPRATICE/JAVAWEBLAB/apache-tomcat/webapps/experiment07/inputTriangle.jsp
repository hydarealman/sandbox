<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>三角形边长输入</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 50px auto; width: 450px; }
        h2 { text-align: center; color: #333; }
        .input-box { background: #f5f5f5; padding: 25px; border-radius: 8px; border: 1px solid #ddd; }
        .form-group { margin-bottom: 15px; }
        label { display: block; margin-bottom: 5px; font-weight: bold; }
        input[type="text"] { width: 95%; padding: 8px; border: 1px solid #ccc; border-radius: 4px; }
        input[type="submit"] {
            width: 100%; padding: 10px; background: #009966; color: white;
            border: none; border-radius: 4px; font-size: 16px; cursor: pointer;
        }
        input[type="submit"]:hover { background: #007a4d; }
    </style>
</head>
<body>
    <h2>三角形边长输入</h2>
    <div class="input-box">
        <form action="showTriangle.jsp" method="post">
            <div class="form-group">
                <label>边长A：</label>
                <input type="text" name="sideA" placeholder="请输入边长A" required>
            </div>
            <div class="form-group">
                <label>边长B：</label>
                <input type="text" name="sideB" placeholder="请输入边长B" required>
            </div>
            <div class="form-group">
                <label>边长C：</label>
                <input type="text" name="sideC" placeholder="请输入边长C" required>
            </div>
            <input type="submit" value="计算">
        </form>
    </div>
</body>
</html>
