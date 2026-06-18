package JAVALAB.lab5;

import java.io.*;

/**
 * 实验1 - 举重成绩单分析
 * 读取 score.txt 中的运动员成绩，计算总成绩并输出到 scoreAnalysis.txt
 */
public class AnalysisResult {
    public static void main(String args[]) {
        File fRead = new File("JAVALAB/lab5/score.txt");
        File fWrite = new File("JAVALAB/lab5/scoreAnalysis.txt");
        try {
            // 以追加方式创建指向文件 fWrite 的 FileWriter 流
            Writer out = new FileWriter(fWrite, true);
            // 创建指向 out 的 BufferedWriter 流（缓冲写入）
            BufferedWriter bufferWrite = new BufferedWriter(out);
            // 创建指向文件 fRead 的 FileReader 流
            Reader in = new FileReader(fRead);
            // 创建指向 in 的 BufferedReader 流（缓冲读取）
            BufferedReader bufferRead = new BufferedReader(in);

            System.out.println("========== 实验1：举重成绩单分析 ==========");
            String str = null;
            while ((str = bufferRead.readLine()) != null) {
                double totalScore = Fenxi.getTotalScore(str);
                str = str + " 总成绩:" + totalScore;
                System.out.println(str);
                bufferWrite.write(str);
                bufferWrite.newLine();
            }
            System.out.println("结果已写入 scoreAnalysis.txt");
            System.out.println();

            bufferRead.close();
            bufferWrite.close();
        } catch (IOException e) {
            System.out.println("文件读写异常: " + e.toString());
        }
    }
}
