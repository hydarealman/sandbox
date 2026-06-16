<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>实验六 JSP内置对象的应用</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px auto; width: 700px; }
        h1 { text-align: center; color: #333; }
        .section { background: #f5f5f5; padding: 15px; margin: 10px 0; border-radius: 8px; border-left: 4px solid #009966; }
        .section h3 { color: #006633; margin-top: 0; }
        table { border-collapse: collapse; width: 100%; }
        table, th, td { border: 1px solid #ddd; }
        th, td { padding: 8px; text-align: left; }
        th { background-color: #009966; color: white; width: 30%; }
        pre { background: #e8e8e8; padding: 10px; border-radius: 4px; font-size: 12px; overflow-x: auto; }
    </style>
</head>
<body>
    <h1>JSP内置对象的应用</h1>

    <!-- 1. request 对象 -->
    <div class="section">
        <h3>1. request 对象 (HttpServletRequest)</h3>
        <table>
            <tr><th>属性</th><th>值</th></tr>
            <tr><td>客户端IP地址</td><td><%= request.getRemoteAddr() %></td></tr>
            <tr><td>客户端主机名</td><td><%= request.getRemoteHost() %></td></tr>
            <tr><td>请求方法</td><td><%= request.getMethod() %></td></tr>
            <tr><td>请求URL</td><td><%= request.getRequestURL() %></td></tr>
            <tr><td>请求URI</td><td><%= request.getRequestURI() %></td></tr>
            <tr><td>协议</td><td><%= request.getProtocol() %></td></tr>
            <tr><td>服务器名</td><td><%= request.getServerName() %></td></tr>
            <tr><td>服务器端口</td><td><%= request.getServerPort() %></td></tr>
            <tr><td>字符编码</td><td><%= request.getCharacterEncoding() %></td></tr>
        </table>
    </div>

    <!-- 2. response 对象 -->
    <div class="section">
        <h3>2. response 对象 (HttpServletResponse)</h3>
        <table>
            <tr><th>属性</th><th>值</th></tr>
            <tr><td>内容类型</td><td><%= response.getContentType() %></td></tr>
            <tr><td>缓冲区大小</td><td><%= response.getBufferSize() %> bytes</td></tr>
            <tr><td>字符编码</td><td><%= response.getCharacterEncoding() %></td></tr>
        </table>
    </div>

    <!-- 3. session 对象 -->
    <div class="section">
        <h3>3. session 对象 (HttpSession)</h3>
        <%
            String visitTime = (String) session.getAttribute("firstVisit");
            if (visitTime == null) {
                visitTime = new java.util.Date().toString();
                session.setAttribute("firstVisit", visitTime);
            }
            Integer sessionCount = (Integer) session.getAttribute("count");
            if (sessionCount == null) {
                sessionCount = 1;
            } else {
                sessionCount++;
            }
            session.setAttribute("count", sessionCount);
        %>
        <table>
            <tr><th>属性</th><th>值</th></tr>
            <tr><td>Session ID</td><td><%= session.getId() %></td></tr>
            <tr><td>创建时间</td><td><%= new java.util.Date(session.getCreationTime()) %></td></tr>
            <tr><td>首次访问时间</td><td><%= visitTime %></td></tr>
            <tr><td>本次会话访问次数</td><td><%= sessionCount %></td></tr>
            <tr><td>最大不活动间隔</td><td><%= session.getMaxInactiveInterval() %> 秒</td></tr>
        </table>
    </div>

    <!-- 4. application 对象 -->
    <div class="section">
        <h3>4. application 对象 (ServletContext)</h3>
        <%
            Integer appCount = (Integer) application.getAttribute("appCount");
            if (appCount == null) {
                appCount = 1;
            } else {
                appCount++;
            }
            application.setAttribute("appCount", appCount);
        %>
        <table>
            <tr><th>属性</th><th>值</th></tr>
            <tr><td>服务器信息</td><td><%= application.getServerInfo() %></td></tr>
            <tr><td>Servlet API版本</td><td><%= application.getMajorVersion() %>.<%= application.getMinorVersion() %></td></tr>
            <tr><td>应用全局访问次数</td><td><%= appCount %></td></tr>
            <tr><td>真实路径(/)</td><td><%= application.getRealPath("/") %></td></tr>
        </table>
    </div>

    <!-- 5. request、session、application 区别 -->
    <div class="section">
        <h3>5. request vs session vs application 的区别</h3>
        <table>
            <tr><th>作用域</th><th>范围</th><th>生命周期</th></tr>
            <tr>
                <td>request</td>
                <td>单次请求</td>
                <td>请求处理完成后消失</td>
            </tr>
            <tr>
                <td>session</td>
                <td>单次会话</td>
                <td>用户关闭浏览器或session超时时消失</td>
            </tr>
            <tr>
                <td>application</td>
                <td>整个Web应用</td>
                <td>服务器重启或应用重新加载时消失</td>
            </tr>
        </table>
    </div>

    <p style="text-align:center; color:#888; font-size:12px; margin-top:20px;">
        实验六：JSP内置对象 (request, response, session, application) 的应用
    </p>
</body>
</html>
