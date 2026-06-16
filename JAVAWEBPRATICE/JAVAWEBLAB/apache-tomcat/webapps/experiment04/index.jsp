<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%-- JSP成员变量声明 --%>
<%!
    private int visitorCount = 0;
    private static final String[] FOODS = {"苹果", "香蕉", "橘子", "葡萄", "西瓜"};

    public String getGreeting() {
        int hour = java.time.LocalTime.now().getHour();
        if (hour < 12) return "早上好";
        else if (hour < 18) return "下午好";
        else return "晚上好";
    }
%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>实验四 JSP脚本元素的应用</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px auto; width: 650px; }
        h1 { text-align: center; color: #333; }
        .section { background: #f5f5f5; padding: 15px; margin: 10px 0; border-radius: 8px; }
        .section h3 { color: #006633; margin-top: 0; }
        table { border-collapse: collapse; width: 100%; }
        table, th, td { border: 1px solid #ddd; }
        th, td { padding: 8px; text-align: center; }
        th { background-color: #009966; color: white; }
        .info { color: #0066cc; font-weight: bold; }
    </style>
</head>
<body>
    <h1>JSP脚本元素的应用</h1>

    <%-- JSP表达式示例 --%>
    <div class="section">
        <h3>1. JSP表达式 (&lt;%= %&gt;)</h3>
        <p>当前时间：<%= new java.util.Date() %></p>
        <p class="info">问候语：<%= getGreeting() %>！欢迎访问本页面！</p>
        <p>服务器信息：<%= application.getServerInfo() %></p>
    </div>

    <%-- JSP程序片(scriptlet)示例 --%>
    <div class="section">
        <h3>2. JSP程序片 (&lt;% %&gt;)</h3>
        <p>水果列表（使用scriptlet循环输出）：</p>
        <table>
            <tr><th>序号</th><th>水果名称</th><th>推荐指数</th></tr>
            <%
                for (int i = 0; i < FOODS.length; i++) {
                    int stars = (int)(Math.random() * 5) + 1;
                    out.println("<tr>");
                    out.println("<td>" + (i + 1) + "</td>");
                    out.println("<td>" + FOODS[i] + "</td>");
                    out.println("<td>");
                    for (int j = 0; j < stars; j++) out.print("★");
                    for (int j = stars; j < 5; j++) out.print("☆");
                    out.println("</td>");
                    out.println("</tr>");
                }
            %>
        </table>
    </div>

    <%-- JSP声明示例 --%>
    <div class="section">
        <h3>3. JSP声明 (&lt;%! %&gt;)</h3>
        <%
            visitorCount++;
        %>
        <p class="info">您是第 <%= visitorCount %> 位访问者（应用范围内计数）</p>
        <p>注：此计数基于JSP成员变量，每次刷新页面都会增加</p>
    </div>

    <%-- JSP与HTML混合示例 --%>
    <div class="section">
        <h3>4. JSP与HTML混合使用</h3>
        <%
            String[] colors = {"#FF6B6B", "#4ECDC4", "#45B7D1", "#96CEB4", "#FFEAA7"};
            String[] names = {"红色系", "青色系", "蓝色系", "绿色系", "黄色系"};
        %>
        <table>
            <tr><th>颜色名称</th><th>颜色值</th><th>预览</th></tr>
            <% for (int i = 0; i < colors.length; i++) { %>
            <tr>
                <td><%= names[i] %></td>
                <td><%= colors[i] %></td>
                <td style="background-color: <%= colors[i] %>; width: 100px;">&nbsp;</td>
            </tr>
            <% } %>
        </table>
    </div>

    <p style="text-align:center; color:#888; font-size:12px;">
        JSP脚本元素实验 - 演示声明、表达式、程序片的使用
    </p>
</body>
</html>
