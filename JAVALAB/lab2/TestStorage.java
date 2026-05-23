package JAVALAB.lab2;

public class TestStorage {
    public static void main(String[] args) {
        Computer pc = new Computer();
        pc.exchangeData(new UDisk());
        pc.exchangeData(new MobileHardDisk());
        pc.exchangeData(new MP3Player());
    }
}
