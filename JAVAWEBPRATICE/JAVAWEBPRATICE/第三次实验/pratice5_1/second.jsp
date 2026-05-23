<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%!
    private int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
%>
<%
    String num1Str = request.getParameter("num1");
    String num2Str = request.getParameter("num2");
    int num1 = 12;
    int num2 = 18;
    boolean valid = true;
    try {
        if (num1Str != null && !num1Str.isEmpty()) num1 = Integer.parseInt(num1Str);
        if (num2Str != null && !num2Str.isEmpty()) num2 = Integer.parseInt(num2Str);
        if (num1 <= 0 || num2 <= 0) valid = false;
    } catch (NumberFormatException e) {
        valid = false;
    }
    if (valid) {
        int result = gcd(num1, num2);
%>
        <p>您输入的两个正整数为：<%=num1%> 和 <%=num2%></p>
        <p>它们的最大公约数是：<strong><%=result%></strong></p>
<%
    } else {
%>
        <p style="color:red">参数错误：请确保两个参数均为正整数！当前 num1=<%=num1Str%>, num2=<%=num2Str%></p>
<%
    }
%>