<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    String rowsStr = request.getParameter("rows");
    String colsStr = request.getParameter("cols");
    int rows = 3;
    int cols = 4;
    try {
        if (rowsStr != null && !rowsStr.isEmpty()) rows = Integer.parseInt(rowsStr);
        if (colsStr != null && !colsStr.isEmpty()) cols = Integer.parseInt(colsStr);
        if (rows <= 0) rows = 1;
        if (cols <= 0) cols = 1;
    } catch (NumberFormatException e) {
        rows = 3;
        cols = 4;
    }
%>
<table border="1" cellpadding="8" cellspacing="0" style="border-collapse: collapse;">
    <caption> <%= rows %> 行 × <%= cols %> 列表格</caption>
    <% for (int i = 1; i <= rows; i++) { %>
        <tr>
            <% for (int j = 1; j <= cols; j++) { %>
                <td>行<%=i%>列<%=j%></td>
            <% } %>
        </tr>
    <% } %>
</table>