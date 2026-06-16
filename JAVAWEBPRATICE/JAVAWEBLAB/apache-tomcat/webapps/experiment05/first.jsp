<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%
    String rowsStr = request.getParameter("rows");
    String colsStr = request.getParameter("cols");
    int rows = (rowsStr != null) ? Integer.parseInt(rowsStr) : 3;
    int cols = (colsStr != null) ? Integer.parseInt(colsStr) : 2;
%>
<table border="1" style="border-collapse:collapse; width:100%; margin:10px 0;">
    <tr style="background-color:#009966; color:white;">
        <% for (int j = 1; j <= cols; j++) { %>
            <th>列 <%= j %></th>
        <% } %>
    </tr>
    <% for (int i = 1; i <= rows; i++) { %>
        <tr>
            <% for (int j = 1; j <= cols; j++) { %>
                <td style="padding:8px; text-align:center;">行<%= i %>列<%= j %></td>
            <% } %>
        </tr>
    <% } %>
</table>
<p style="font-size:12px; color:#888; text-align:center;">表格尺寸：<%= rows %> 行 × <%= cols %> 列（通过param传递参数）</p>
