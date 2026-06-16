<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
    String num1Str = request.getParameter("num1");
    String num2Str = request.getParameter("num2");
    int num1 = (num1Str != null) ? Integer.parseInt(num1Str) : 12;
    int num2 = (num2Str != null) ? Integer.parseInt(num2Str) : 8;

    // 计算最大公约数 (欧几里得算法)
    int a = num1, b = num2;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a;
    int lcm = (num1 * num2) / gcd; // 最小公倍数
%>
<div style="padding:15px; background:#e8f5e9; border-radius:8px; margin:10px 0;">
    <p><strong>第一个正整数：</strong><%= num1 %></p>
    <p><strong>第二个正整数：</strong><%= num2 %></p>
    <p style="color:#006633; font-size:16px;">
        <strong>最大公约数（GCD）：</strong><%= gcd %>
    </p>
    <p style="color:#006633;">
        <strong>最小公倍数（LCM）：</strong><%= lcm %>
    </p>
    <p style="font-size:11px; color:#888;">这两个参数值通过input.jsp的param子标记传递</p>
</div>
