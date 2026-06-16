<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<jsp:useBean id="triangle" class="beans.Triangle" scope="request" />
<jsp:setProperty name="triangle" property="*" />
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>三角形计算结果</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 50px auto; width: 500px; }
        h2 { text-align: center; color: #333; }
        .result-box { background: #e8f5e9; padding: 25px; border-radius: 8px; border: 2px solid #4CAF50; }
        .result-box.error { background: #ffebee; border-color: #f44336; }
        .info { font-size: 16px; margin: 10px 0; }
        .back-link { display: block; text-align: center; margin-top: 20px; color: #009966; text-decoration: none; }
        table { width: 100%; border-collapse: collapse; margin-top: 15px; }
        th, td { padding: 10px; border: 1px solid #ddd; text-align: center; }
        th { background: #009966; color: white; }
        .value { font-size: 20px; color: #006633; font-weight: bold; }
    </style>
</head>
<body>
    <h2>三角形计算结果</h2>

    <jsp:getProperty name="triangle" property="isValid" />
    <% if (triangle.isValid()) { %>
        <div class="result-box">
            <p class="info" style="font-size:18px;">✅ 这是一个合法的三角形！</p>
            <table>
                <tr><th>属性</th><th>值</th></tr>
                <tr>
                    <td>边长A (getProperty)</td>
                    <td class="value"><jsp:getProperty name="triangle" property="sideA" /></td>
                </tr>
                <tr>
                    <td>边长B (getProperty)</td>
                    <td class="value"><jsp:getProperty name="triangle" property="sideB" /></td>
                </tr>
                <tr>
                    <td>边长C (getProperty)</td>
                    <td class="value"><jsp:getProperty name="triangle" property="sideC" /></td>
                </tr>
                <tr>
                    <td>周长 (getProperty)</td>
                    <td class="value"><jsp:getProperty name="triangle" property="perimeter" /></td>
                </tr>
                <tr>
                    <td>面积 (表达式)</td>
                    <td class="value"><%= String.format("%.4f", triangle.getArea()) %></td>
                </tr>
            </table>
        </div>
    <% } else { %>
        <div class="result-box error">
            <p class="info" style="font-size:18px; color:#f44336;">❌ 这三条边不能构成三角形！</p>
            <p>请确保任意两边之和大于第三边。</p>
            <p>您输入的边长：A=<jsp:getProperty name="triangle" property="sideA" />,
               B=<jsp:getProperty name="triangle" property="sideB" />,
               C=<jsp:getProperty name="triangle" property="sideC" /></p>
        </div>
    <% } %>

    <a href="inputTriangle.jsp" class="back-link">← 返回重新输入</a>
</body>
</html>
