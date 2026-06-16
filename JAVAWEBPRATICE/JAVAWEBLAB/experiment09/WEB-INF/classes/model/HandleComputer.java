package model;

import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;
import java.io.IOException;

/** Servlet控制器 - 处理计算机请求 */
@WebServlet(urlPatterns = {"/handleComputer"})
public class HandleComputer extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");

        try {
            // 获取请求参数
            double num1 = Double.parseDouble(request.getParameter("operand1"));
            double num2 = Double.parseDouble(request.getParameter("operand2"));
            String operator = request.getParameter("operator");

            // 创建实体模型
            Computer computer = new Computer();
            computer.setOperand1(num1);
            computer.setOperand2(num2);
            computer.setOperator(operator);

            // 调用业务模型进行计算
            CalculateBean calc = new CalculateBean();
            calc.calculate(computer);

            // 将结果存入request
            request.setAttribute("computer", computer);
            request.setAttribute("operatorSymbol", getOperatorSymbol(operator));

            // 转发到显示页面
            request.getRequestDispatcher("/showResult.jsp").forward(request, response);

        } catch (NumberFormatException e) {
            request.setAttribute("error", "请输入有效的数字！");
            request.getRequestDispatcher("/showResult.jsp").forward(request, response);
        } catch (ArithmeticException e) {
            request.setAttribute("error", e.getMessage());
            request.getRequestDispatcher("/showResult.jsp").forward(request, response);
        } catch (Exception e) {
            request.setAttribute("error", "计算出错：" + e.getMessage());
            request.getRequestDispatcher("/showResult.jsp").forward(request, response);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doPost(request, response);
    }

    /** 格式化数字（整数不显示小数点） */
    private String formatNumber(double num) {
        if (num == (long) num) {
            return String.valueOf((long) num);
        }
        return String.valueOf(num);
    }

    /** 获取运算符符号 */
    private String getOperatorSymbol(String operator) {
        if ("*".equals(operator)) {
            return "×";  // ×
        } else if ("/".equals(operator)) {
            return "÷";  // ÷
        }
        return operator;
    }
}
