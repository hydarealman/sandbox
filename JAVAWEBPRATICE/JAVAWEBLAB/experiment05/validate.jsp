<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
    String username = request.getParameter("username");
    String password = request.getParameter("password");

    // 验证用户名和密码
    if ("tom".equals(username) && "jenny".equals(password)) {
        // 登录成功，使用forward动作标记转到success.jsp
%>
        <jsp:forward page="success.jsp">
            <jsp:param name="username" value="<%= username %>" />
        </jsp:forward>
<%
    } else {
        // 登录失败，转到login.jsp并显示错误信息
%>
        <jsp:forward page="login.jsp">
            <jsp:param name="error" value="用户名或密码错误，请重新登录！" />
        </jsp:forward>
<%
    }
%>
