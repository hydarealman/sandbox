package code;

import java.io.*;

/**
 * Java IO 流 四大基础操作（由浅入深）
 *
 * 1. 文本文件复制    → FileReader / FileWriter          （字符流，只能处理纯文本）
 * 2. 字符串缓冲流    → BufferedReader / BufferedWriter   （字符缓冲流，带 readLine 逐行读）
 * 3. 任意文件复制    → FileInputStream / FileOutputStream（字节流，万物皆可读，但慢）
 * 4. 字节缓冲流万能复制 → BufferedInputStream / BufferedOutputStream（字节缓冲流，效率最高）
 */
public class blog_4 {

    public static void main(String[] args) {

        // ==================== 1. 文本文件复制 ====================
        // 核心：FileReader 按"字符"读文本，FileWriter 按"字符"写文本
        // 原理：底层自动把字节 → 字符（解码），所以只能处理 .txt .java 等文本文件
        //       遇到图片/视频/zip 会乱码甚至报错

        try (
            // FileReader(路径) → 打开文件准备读字符
            FileReader fr = new FileReader("d:/sandbox/source.txt");
            // FileWriter(路径) → 打开文件准备写字符
            FileWriter fw = new FileWriter("d:/sandbox/target.txt");
        ) {
            int ch;  // 存一个字符（int 是因为 read() 返回 ASCII/Unicode 码，结束返回 -1）
            while ((ch = fr.read()) != -1) {
                fw.write(ch);   // 读一个字符 → 写一个字符
            }
            System.out.println("1. 文本文件复制 完成");
        } catch (IOException e) {
            e.printStackTrace();
        }


        // ==================== 2. 字符串缓冲流 ====================
        // 核心：BufferedReader 内置一个 char[] 缓冲区，一次读一大块到内存
        //       readLine() 一次读一整行（读不到换行符 \n），比逐字符 read() 快几十倍
        // 类比：超市购物 → 逐字符是"一次买一粒米"，缓冲是"一次买一购物车"

        try (
            // 构造：new BufferedReader( new FileReader(路径) )   ← 装饰器模式套娃
            BufferedReader br = new BufferedReader(new FileReader("d:/sandbox/source.txt"));
            BufferedWriter bw = new BufferedWriter(new FileWriter("d:/sandbox/target2.txt"));
        ) {
            String line;  // 存一行文本
            while ((line = br.readLine()) != null) {   // readLine() 读一行，读完返回 null
                bw.write(line);   // 写一行
                bw.newLine();     // 补一个换行符（readLine 不读 \n，所以要手动补）
            }
            System.out.println("2. 字符串缓冲流复制 完成");
        } catch (IOException e) {
            e.printStackTrace();
        }


        // ==================== 3. 任意文件复制 ====================
        // 核心：FileInputStream 按"字节"读，不管内容是什么（文本/图片/视频/zip 通吃）
        // 缺点：每次 read() 只读 1 字节 → 读写 1MB 文件要调 100 万次系统调用，蜗牛速度

        try (
            FileInputStream fis = new FileInputStream("d:/sandbox/source.png");
            FileOutputStream fos = new FileOutputStream("d:/sandbox/target.png");
        ) {
            int b;  // 存一个字节（0~255，结束返回 -1）
            while ((b = fis.read()) != -1) {
                fos.write(b);
            }
            System.out.println("3. 任意文件复制 完成");
        } catch (IOException e) {
            e.printStackTrace();
        }


        // ==================== 4. 字节缓冲流 — 万能复制 ====================
        // 核心：BufferedInputStream 内置 byte[] 缓冲区（默认 8192 字节 = 8KB）
        //       一次 read 读满一车（8192 字节），而不是 1 字节，速度提升几百倍
        // 这是日常开发里最实用的"万能文件复制"写法

        try (
            BufferedInputStream bis = new BufferedInputStream(new FileInputStream("d:/sandbox/source.png"));
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream("d:/sandbox/target2.png"));
        ) {
            byte[] buf = new byte[1024];  // 搬运小车，一次搬 1024 字节（1KB）
            int len;  // 实际读到的字节数
            while ((len = bis.read(buf)) != -1) {  // 读满一车
                bos.write(buf, 0, len);            // 倒出实际读到的（最后一车可能不满）
            }
            System.out.println("4. 字节缓冲流万能复制 完成");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
