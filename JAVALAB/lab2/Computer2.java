package JAVALAB.lab2;

public class Computer2 {
    public void exchangeData(MobileStorage device) {
        device.read();
        device.write();
        if (device instanceof MP3Player) {
            ((MP3Player) device).playMusic();
        }
    }
}
