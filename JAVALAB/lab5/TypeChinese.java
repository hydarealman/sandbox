package JAVALAB.lab5;

/**
 * 实验4 - 汉字输入练习主程序
 * 双线程协作：GiveChineseThread 显示汉字，InputChineseThread 读取用户输入
 */
public class TypeChinese {
    public static void main(String args[]) {
        System.out.println("========== 实验4：汉字输入练习 ==========");
        System.out.println("输入汉字练习(输入#结束程序)");
        System.out.printf("输入显示的汉字(回车)\n");

        Chinese hanzi;
        hanzi = new Chinese();

        GiveChineseThread giveHanzi;
        InputChineseThread typeHanzi;

        // 创建出汉字线程 giveHanzi
        giveHanzi = new GiveChineseThread();
        giveHanzi.setChinese(hanzi);
        giveHanzi.setSleepLength(6000);

        // 创建输入汉字线程 typeHanzi
        typeHanzi = new InputChineseThread();
        typeHanzi.setChinese(hanzi);

        giveHanzi.start();
        try {
            Thread.sleep(200);
        } catch (Exception exp) {
        }
        typeHanzi.start();
    }
}
