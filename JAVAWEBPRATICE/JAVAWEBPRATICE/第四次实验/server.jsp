<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    String username = request.getParameter("username");
    String password = request.getParameter("password");

    if ("zhangsan".equals(username) && "123".equals(password)) {
        // 验证成功，显示提示，3秒后跳转到 loginSuccess.jsp
        response.setHeader("refresh", "3;url=loginSuccess.jsp");
%>
        <!DOCTYPE html>
        <html>
        <head><title>登录成功</title></head>
        <body>
            <h3>成功登录，3秒钟后进入 loginSuccess.jsp 页面...</h3>
            <p>如果没有跳转，请点击 <a href="loginSuccess.jsp">这里</a></p>
        </body>
        </html>
<%
    } else {
        // 验证失败，重定向到 login_1.jsp
        response.sendRedirect("login_1.jsp");
    }
%>