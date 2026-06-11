package review_pratice;

import java.io.*;

public class stream_pratice {
    public static void main(String[] args) {
        String filePath = "d:/sandbox/JAVAPRATICE/data.bin";

        // 写入数据
        try (DataOutputStream dos = new DataOutputStream(new FileOutputStream(filePath))) {
            dos.writeInt(25);
            dos.writeDouble(3.14);
            dos.writeBoolean(true);
            dos.writeUTF("你好 DataStream!");
            System.out.println("写入完成!");
        }
        catch (IOException e) {
            e.printStackTrace();
        }

        // 读取数据
        try(DataInputStream dis = new DataInputStream(new FileInputStream(filePath))) {
            int age = dis.readInt();
            double pi = dis.readDouble();
            boolean flag = dis.readBoolean();
            String msg = dis.readUTF();

            System.out.println("读取结果");
            System.out.println("int" + age);
            System.out.println("boolean" + flag);
            System.out.println("String" + msg);
        }
        catch(IOException e) {
            e.printStackTrace();
        }
    }
}
