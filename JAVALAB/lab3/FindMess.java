package JAVALAB.lab3;

/**
 * 文件名：FindMess.java
 * 功能：从字符串中提取图书信息并判断
 */
public class FindMess {
    public static void main(String args[]) {
        String mess = "书名:Java程序设计,出版时间:2011.10.01," +
                "出版社:清华大学出版社,价格:29.8元,页数:389页";
        
        // 判断是否包含"程序"
        if (mess.contains("程序")) {
            System.out.println("图书信息包含有\"程序\"");
        }
        
        // 获取第2个冒号的位置（出版时间前的冒号）
        int index = mess.indexOf(":", mess.indexOf(":") + 1);
        String date = mess.substring(index + 1, index + 11);
        System.out.println("出版时间：" + date);
        
        // 获取价格
        int pricePosition = mess.indexOf("价格");
        int endPosition = mess.indexOf("元");
        String priceMess = mess.substring(pricePosition + 3, endPosition);
        System.out.println("图书价格:" + priceMess);
        double price = Double.parseDouble(priceMess);
        if (price >= 29) {
            System.out.println("图书价格" + price + "大于或等于29元");
        } else {
            System.out.println("图书价格" + price + "小于29元");
        }
        
        // 获取页数（最后一个冒号后的内容）
        index = mess.lastIndexOf(":");
        endPosition = mess.lastIndexOf("页");
        String pageMess = mess.substring(index + 1, endPosition);
        int p = Integer.parseInt(pageMess);
        if (p >= 360) {
            System.out.println("图书的页数" + p + "大于或等于360");
        } else {
            System.out.println("图书的页数" + p + "小于360");
        }
    }
}
