package review_pratice;

import java.io.*;

public class ByteStream {
    public static void main(String[] args) {
        String src = "source.jpg";
        String dest = "copy_fast.jpg";

        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(src));
             BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(dest))) {
     
            byte[] buffer = new byte[8192];  // 8KB 缓冲区
            int len;  // 实际读取的字节数
            // 每次读取一个字节数组，返回读取的长度，-1 表示文件结束
            while ((len = bis.read(buffer)) != -1) {
                bos.write(buffer, 0, len);   // 写入数组中的有效部分
            }
            // 刷新缓冲区：确保所有数据真正写入磁盘（close 时会自动 flush，但显式写出更安全）
            bos.flush();
            System.out.println("高效复制完成！");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
