package JAVALAB.lab4;

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;

/**
 * 文件名：Minesweeper.java
 * 功能：终端扫雷游戏
 * 特点：
 *   1. 良好的终端界面（Unicode字符 + ANSI颜色）
 *   2. 三级难度可调（初级9×9/10雷、中级16×16/40雷、高级30×16/99雷）
 *   3. 计时与计步功能
 *   4. 保存/读取游戏进度（序列化到文件）
 *   5. WASD 移动光标，空格翻开，F 插旗/取消旗，Q 退出
 */
public class Minesweeper {
    // ============ 难度预设 ============
    private static final int[][] DIFFICULTY_PRESETS = {
        // {行数, 列数, 雷数}
        {9,  9,  10},   // 初级
        {16, 16, 40},   // 中级
        {16, 30, 99},   // 高级
    };
    private static final String[] DIFFICULTY_NAMES = {"初级", "中级", "高级"};

    // ============ 颜色常量 (ANSI) ============
    private static final String RESET  = "[0m";
    private static final String RED    = "[31m";
    private static final String GREEN  = "[32m";
    private static final String YELLOW = "[33m";
    private static final String BLUE   = "[34m";
    private static final String CYAN   = "[36m";
    private static final String WHITE  = "[37m";
    private static final String BOLD   = "[1m";
    private static final String BG_GRAY = "[47m[30m";

    // 数字颜色 (1-8)
    private static final String[] NUM_COLORS = {
        "", BLUE, GREEN, RED, BLUE + BOLD, RED + BOLD, CYAN, YELLOW, "[35m"
    };

    // ============ 单元格状态 ============
    private static final int COVERED  = 0;   // 未翻开
    private static final int FLAGGED  = -1;  // 插旗
    private static final int REVEALED = 1;   // 已翻开

    // ============ 游戏数据 ============
    private int rows, cols, totalMines;
    private boolean[][] mine;         // 是否有雷
    private int[][]    state;         // 单元格状态: COVERED/FLAGGED/REVEALED
    private int[][]    adjacentMines; // 周围雷数 (仅已翻开的有效)

    private int cursorRow, cursorCol; // 光标位置
    private int steps;                // 计步
    private long startTime;           // 开始时间戳
    private long elapsedSeconds;      // 已用秒数
    private boolean gameOver;
    private boolean gameWon;
    private boolean firstMove;        // 是否是第一步 (用于保证第一步不踩雷)

    private Scanner scanner;
    private String saveDir;

    public Minesweeper() {
        scanner = new Scanner(System.in);
        saveDir = System.getProperty("user.dir") + File.separator + "JAVALAB" + File.separator + "lab4" + File.separator + "saves";
    }

    public static void main(String[] args) {
        Minesweeper game = new Minesweeper();
        game.run();
    }

    // ==================== 主菜单 ====================
    public void run() {
        while (true) {
            clearScreen();
            printBanner();
            System.out.println();
            System.out.println("  " + BOLD + "🎮  主 菜 单" + RESET);
            System.out.println("  ┌─────────────────────────┐");
            System.out.println("  │  1. 🟢 初级  (9×9,  10雷) │");
            System.out.println("  │  2. 🟡 中级 (16×16, 40雷) │");
            System.out.println("  │  3. 🔴 高级 (30×16, 99雷) │");
            System.out.println("  │  4. 💾 读取存档          │");
            System.out.println("  │  5. 🚪 退出游戏          │");
            System.out.println("  └─────────────────────────┘");
            System.out.print("\n  👉 请选择 (1-5): ");

            String choice = scanner.nextLine().trim();
            switch (choice) {
                case "1": startGame(0); break;
                case "2": startGame(1); break;
                case "3": startGame(2); break;
                case "4": loadGame();   break;
                case "5":
                    System.out.println("\n  👋 再见！");
                    return;
                default:
                    System.out.println("  ⚠️  无效选择，按回车继续...");
                    scanner.nextLine();
            }
        }
    }

    // ==================== 游戏初始化 ====================
    private void startGame(int difficulty) {
        int[] preset = DIFFICULTY_PRESETS[difficulty];
        rows = preset[0];
        cols = preset[1];
        totalMines = preset[2];

        mine = new boolean[rows][cols];
        state = new int[rows][cols];
        adjacentMines = new int[rows][cols];

        for (int i = 0; i < rows; i++) {
            Arrays.fill(state[i], COVERED);
        }

        cursorRow = rows / 2;
        cursorCol = cols / 2;
        steps = 0;
        elapsedSeconds = 0;
        gameOver = false;
        gameWon = false;
        firstMove = true;

        // 雷还未布置，等第一次操作后再布置（保证第一步安全）
        startTime = System.currentTimeMillis();
        gameLoop();
    }

    // ==================== 布雷（首次操作后调用） ====================
    private void placeMines(int safeRow, int safeCol) {
        Random rand = new Random();
        int placed = 0;
        while (placed < totalMines) {
            int r = rand.nextInt(rows);
            int c = rand.nextInt(cols);
            // 不要在安全位置（第一步点击处及其周围）放雷
            if (!mine[r][c] && !(Math.abs(r - safeRow) <= 1 && Math.abs(c - safeCol) <= 1)) {
                mine[r][c] = true;
                placed++;
            }
        }
        // 计算周围雷数
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                adjacentMines[i][j] = countAdjacentMines(i, j);
            }
        }
    }

    private int countAdjacentMines(int r, int c) {
        int count = 0;
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && mine[nr][nc]) {
                    count++;
                }
            }
        }
        return count;
    }

    // ==================== 翻开单元格 ====================
    private void reveal(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return;
        if (state[r][c] != COVERED) return;
        if (mine[r][c]) return;

        state[r][c] = REVEALED;
        // 如果周围没有雷，自动翻开相邻格
        if (adjacentMines[r][c] == 0) {
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    reveal(r + dr, c + dc);
                }
            }
        }
    }

    // ==================== 检查胜利 ====================
    private boolean checkWin() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // 所有非雷格都已翻开
                if (!mine[i][j] && state[i][j] != REVEALED) {
                    return false;
                }
            }
        }
        return true;
    }

    // ==================== 游戏主循环 ====================
    private void gameLoop() {
        while (!gameOver && !gameWon) {
            renderBoard();
            System.out.print("\n  🎯 操作 (WASD移动 空格翻开 F插旗 P保存 Q退出): ");
            String input = scanner.nextLine().trim().toUpperCase();

            if (input.isEmpty()) continue;

            char cmd = input.charAt(0);

            // 更新时间
            elapsedSeconds = (System.currentTimeMillis() - startTime) / 1000;

            switch (cmd) {
                case 'W': if (cursorRow > 0) cursorRow--; break;
                case 'S': if (cursorRow < rows - 1) cursorRow++; break;
                case 'A': if (cursorCol > 0) cursorCol--; break;
                case 'D': if (cursorCol < cols - 1) cursorCol++; break;

                case ' ': // 翻开
                    if (state[cursorRow][cursorCol] == FLAGGED) break;
                    if (firstMove) {
                        placeMines(cursorRow, cursorCol);
                        firstMove = false;
                        steps++;
                    }
                    if (mine[cursorRow][cursorCol]) {
                        // 踩雷
                        state[cursorRow][cursorCol] = REVEALED;
                        gameOver = true;
                    } else {
                        reveal(cursorRow, cursorCol);
                        if (!firstMove) steps++;
                    }
                    break;

                case 'F': // 插旗/取消插旗
                    if (state[cursorRow][cursorCol] == COVERED) {
                        state[cursorRow][cursorCol] = FLAGGED;
                        steps++;
                    } else if (state[cursorRow][cursorCol] == FLAGGED) {
                        state[cursorRow][cursorCol] = COVERED;
                        steps++;
                    }
                    break;

                case 'P': // 保存
                    saveGame();
                    System.out.print("  📌 按回车继续...");
                    scanner.nextLine();
                    break;

                case 'Q': // 退出
                    System.out.print("\n  ❓ 确定要退出吗？(y/n): ");
                    if (scanner.nextLine().trim().equalsIgnoreCase("y")) {
                        return;
                    }
                    break;

                default:
                    break;
            }

            // 检查胜利
            if (!firstMove && checkWin()) {
                gameWon = true;
            }
        }

        // 游戏结束画面
        elapsedSeconds = (System.currentTimeMillis() - startTime) / 1000;
        renderBoard();
        if (gameWon) {
            System.out.println("\n  🎉🎊 恭喜你赢了！ 🎊🎉");
            System.out.println("  ⏱ 用时: " + formatTime(elapsedSeconds) + "  |  🐾 步数: " + steps);
        } else {
            System.out.println("\n  💥 踩到地雷了！游戏结束！ 💥");
            revealAllMines();
        }
        System.out.print("\n  📌 按回车返回主菜单...");
        scanner.nextLine();
    }

    // ==================== 画面渲染 ====================
    private void renderBoard() {
        clearScreen();
        printBanner();
        System.out.println("  ⏱ " + formatTime(elapsedSeconds) + "  |  🐾 步数: " + steps
                + "  |  🚩 旗: " + countFlags() + "/" + totalMines);
        System.out.println();

        // 列号
        System.out.print("  " + BG_GRAY + "   " + RESET);
        for (int j = 0; j < cols; j++) {
            if (j == cursorCol) {
                System.out.print(BG_GRAY + BLUE + BOLD + padCenter(colLabel(j), 2) + RESET);
            } else {
                System.out.print(BG_GRAY + padCenter(colLabel(j), 2) + RESET);
            }
        }
        System.out.println();

        // 棋盘
        for (int i = 0; i < rows; i++) {
            // 行号
            if (i == cursorRow) {
                System.out.print("  " + BG_GRAY + BLUE + BOLD + padCenter(rowLabel(i), 2) + RESET + " ");
            } else {
                System.out.print("  " + BG_GRAY + padCenter(rowLabel(i), 2) + RESET + " ");
            }

            for (int j = 0; j < cols; j++) {
                boolean isCursor = (i == cursorRow && j == cursorCol);
                String cell = renderCell(i, j, isCursor);
                System.out.print(cell);
            }
            System.out.println();
        }
    }

    private String rowLabel(int i) {
        // 使用字母作为行标签
        if (i < 26) return String.valueOf((char)('A' + i));
        return String.valueOf(i + 1);
    }

    private String colLabel(int j) {
        // 使用数字作为列标签
        return String.valueOf(j + 1);
    }

    private String padCenter(String s, int width) {
        if (s.length() >= width) return s;
        int leftPad = (width - s.length()) / 2;
        int rightPad = width - s.length() - leftPad;
        return " ".repeat(leftPad) + s + " ".repeat(rightPad);
    }

    private String renderCell(int r, int c, boolean isCursor) {
        String cursorPrefix = isCursor ? "[7m" : "";  // 反色高亮光标
        String suffix = isCursor ? RESET : "";

        if (gameOver && mine[r][c] && state[r][c] != FLAGGED) {
            // 游戏结束时显示所有雷
            String cell = (r == cursorRow && c == cursorCol && state[r][c] != FLAGGED) ? "💥" : "💣";
            return cursorPrefix + " " + cell + " " + suffix;
        }

        switch (state[r][c]) {
            case COVERED:
                return cursorPrefix + " █ " + suffix;
            case FLAGGED:
                return cursorPrefix + RED + " ⚑ " + RESET + suffix;
            case REVEALED:
                if (mine[r][c]) {
                    return cursorPrefix + RED + BOLD + " 💥" + RESET + suffix;
                }
                int adj = adjacentMines[r][c];
                if (adj == 0) {
                    return cursorPrefix + " · " + suffix;
                }
                return cursorPrefix + " " + NUM_COLORS[adj] + adj + " " + RESET + suffix;
            default:
                return " ? ";
        }
    }

    private int countFlags() {
        int count = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (state[i][j] == FLAGGED) count++;
            }
        }
        return count;
    }

    private void revealAllMines() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (mine[i][j] && state[i][j] != FLAGGED) {
                    state[i][j] = REVEALED;
                }
            }
        }
        clearScreen();
        printBanner();
        System.out.println();
        // 简单打印最终状态
        System.out.print("  " + BG_GRAY + "   " + RESET);
        for (int j = 0; j < cols; j++) {
            System.out.print(BG_GRAY + padCenter(colLabel(j), 2) + RESET);
        }
        System.out.println();
        for (int i = 0; i < rows; i++) {
            System.out.print("  " + BG_GRAY + padCenter(rowLabel(i), 2) + RESET + " ");
            for (int j = 0; j < cols; j++) {
                if (mine[i][j]) {
                    if (state[i][j] == FLAGGED) {
                        System.out.print(GREEN + " ⚑ " + RESET);
                    } else {
                        System.out.print(RED + " 💣" + RESET);
                    }
                } else if (state[i][j] == FLAGGED) {
                    System.out.print(RED + " ✖ " + RESET);  // 错误插旗
                } else {
                    int adj = adjacentMines[i][j];
                    if (adj == 0) {
                        System.out.print(" · ");
                    } else {
                        System.out.print(" " + NUM_COLORS[adj] + adj + " " + RESET);
                    }
                }
            }
            System.out.println();
        }
    }

    // ==================== 存档操作 ====================
    private void saveGame() {
        if (firstMove) {
            System.out.println("  ⚠️  游戏尚未开始，无法保存");
            return;
        }
        try {
            File dir = new File(saveDir);
            if (!dir.exists()) dir.mkdirs();

            String timestamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
            String filename = saveDir + File.separator + "minesweeper_" + timestamp + ".sav";
            String descFile = saveDir + File.separator + "minesweeper_latest.sav";

            GameSave save = new GameSave();
            save.rows = rows;
            save.cols = cols;
            save.totalMines = totalMines;
            save.mine = mine;
            save.state = state;
            save.adjacentMines = adjacentMines;
            save.cursorRow = cursorRow;
            save.cursorCol = cursorCol;
            save.steps = steps;
            save.elapsedSeconds = (System.currentTimeMillis() - startTime) / 1000;
            save.gameOver = gameOver;
            save.gameWon = gameWon;
            save.firstMove = firstMove;

            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
                oos.writeObject(save);
            }
            // 也存为 latest
            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(descFile))) {
                oos.writeObject(save);
            }

            System.out.println("  💾 游戏已保存到: " + filename);
        } catch (IOException e) {
            System.out.println("  ❌ 保存失败: " + e.getMessage());
        }
    }

    private void loadGame() {
        clearScreen();
        printBanner();
        System.out.println();

        // 优先加载 latest
        String latestFile = saveDir + File.separator + "minesweeper_latest.sav";
        File f = new File(latestFile);
        if (!f.exists()) {
            // 列出所有存档
            File dir = new File(saveDir);
            if (!dir.exists() || dir.listFiles() == null || dir.listFiles().length == 0) {
                System.out.println("  📭 没有找到存档文件");
                System.out.print("\n  📌 按回车返回...");
                scanner.nextLine();
                return;
            }
            File[] saves = dir.listFiles((d, name) -> name.endsWith(".sav"));
            if (saves == null || saves.length == 0) {
                System.out.println("  📭 没有找到存档文件");
                System.out.print("\n  📌 按回车返回...");
                scanner.nextLine();
                return;
            }
            System.out.println("  📂 可用存档：");
            for (int i = 0; i < saves.length; i++) {
                System.out.println("    " + (i + 1) + ". " + saves[i].getName());
            }
            System.out.print("\n  👉 选择存档编号 (0取消): ");
            int idx;
            try {
                idx = Integer.parseInt(scanner.nextLine().trim());
                if (idx == 0) return;
                if (idx < 1 || idx > saves.length) {
                    System.out.println("  ⚠️  无效编号");
                    System.out.print("  📌 按回车返回...");
                    scanner.nextLine();
                    return;
                }
                latestFile = saves[idx - 1].getAbsolutePath();
            } catch (NumberFormatException e) {
                System.out.println("  ⚠️  无效输入");
                System.out.print("  📌 按回车返回...");
                scanner.nextLine();
                return;
            }
        }

        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(latestFile))) {
            GameSave save = (GameSave) ois.readObject();
            rows = save.rows;
            cols = save.cols;
            totalMines = save.totalMines;
            mine = save.mine;
            state = save.state;
            adjacentMines = save.adjacentMines;
            cursorRow = save.cursorRow;
            cursorCol = save.cursorCol;
            steps = save.steps;
            elapsedSeconds = save.elapsedSeconds;
            gameOver = save.gameOver;
            gameWon = save.gameWon;
            firstMove = save.firstMove;
            startTime = System.currentTimeMillis() - save.elapsedSeconds * 1000;

            System.out.println("  📥 存档加载成功！");
            System.out.print("  📌 按回车开始游戏...");
            scanner.nextLine();

            if (!gameOver && !gameWon) {
                gameLoop();
            } else {
                renderBoard();
                System.out.println("  ⚠️  该存档的游戏已结束");
                System.out.print("  📌 按回车返回...");
                scanner.nextLine();
            }
        } catch (IOException | ClassNotFoundException e) {
            System.out.println("  ❌ 加载失败: " + e.getMessage());
            System.out.print("  📌 按回车返回...");
            scanner.nextLine();
        }
    }

    // ==================== 辅助方法 ====================
    private void clearScreen() {
        // ANSI清屏
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    private void printBanner() {
        System.out.println();
        System.out.println("  " + BOLD + CYAN + "╔══════════════════════════════════════╗" + RESET);
        System.out.println("  " + BOLD + CYAN + "║" + RESET + "       💣  " + BOLD + "扫 雷 游 戏" + RESET + "  💣       " + BOLD + CYAN + "║" + RESET);
        System.out.println("  " + BOLD + CYAN + "╚══════════════════════════════════════╝" + RESET);
    }

    private String formatTime(long seconds) {
        long min = seconds / 60;
        long sec = seconds % 60;
        return String.format("%02d:%02d", min, sec);
    }

    // ==================== 存档数据类 ====================
    public static class GameSave implements Serializable {
        private static final long serialVersionUID = 1L;
        int rows, cols, totalMines;
        boolean[][] mine;
        int[][] state;
        int[][] adjacentMines;
        int cursorRow, cursorCol;
        int steps;
        long elapsedSeconds;
        boolean gameOver, gameWon, firstMove;
    }
}
