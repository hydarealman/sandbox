package JAVALAB.lab2;

public class MP3Player implements MobileStorage {
    public void read() {
        System.out.println("MP3 读取数据");
    }
    public void write() {
        System.out.println("MP3 写入数据");
    }
    public void playMusic() {
        System.out.println("MP3 播放音乐");
    }
}
