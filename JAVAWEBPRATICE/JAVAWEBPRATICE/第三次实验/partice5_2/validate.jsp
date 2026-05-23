<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    String username = request.getParameter("username");
    String password = request.getParameter("password");
    if ("tom".equals(username) && "jenny".equals(password)) {
        request.setAttribute("loginUser", username);
%>
        <jsp:forward page="success.jsp" />
<%
    } else {
%>
        <jsp:forward page="login.jsp">
            <jsp:param name="error" value="1" />
        </jsp:forward>
<%
    }
%>