package JAVALAB.lab4;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import javax.swing.border.TitledBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.text.DecimalFormat;
import java.util.Random;

/**
 * 文件名：ArithmeticPractice.java
 * 功能：小学生算术计算练习软件（Swing图形用户界面）
 * 特点：
 *   1. 可自定义难度（简单/中等/困难）
 *   2. 随机生成加减乘除题目
 *   3. 按键判断答案是否正确
 *   4. 支持整数和小数运算
 *   5. 计分与统计功能
 */
public class ArithmeticPractice extends JFrame {
    private static final long serialVersionUID = 1L;

    // 颜色常量 - 柔和的配色方案
    private static final Color BG_COLOR = new Color(245, 247, 250);
    private static final Color PRIMARY_COLOR = new Color(92, 107, 192);
    private static final Color ACCENT_COLOR = new Color(255, 138, 101);
    private static final Color SUCCESS_COLOR = new Color(102, 187, 106);
    private static final Color ERROR_COLOR = new Color(239, 83, 80);
    private static final Color CARD_BG = Color.WHITE;
    private static final Color TEXT_COLOR = new Color(55, 71, 79);

    private static final Font TITLE_FONT = new Font("微软雅黑", Font.BOLD, 28);
    private static final Font QUESTION_FONT = new Font("Segoe UI", Font.BOLD, 42);
    private static final Font LABEL_FONT = new Font("微软雅黑", Font.PLAIN, 16);
    private static final Font BUTTON_FONT = new Font("微软雅黑", Font.BOLD, 16);
    private static final Font SCORE_FONT = new Font("微软雅黑", Font.BOLD, 18);
    private static final Font RESULT_FONT = new Font("微软雅黑", Font.BOLD, 20);

    // 游戏状态
    private String difficulty = "中等";   // 简单/中等/困难
    private String numberType = "整数";    // 整数/小数
    private String[] operations = {"+", "-", "×", "÷"};
    private boolean[] opEnabled = {true, true, true, true};

    private double currentAnswer;          // 当前题目的正确答案
    private int totalQuestions = 0;        // 总答题数
    private int correctQuestions = 0;      // 答对数
    private int currentOperand1, currentOperand2;
    private String currentOp;

    private Random random = new Random();
    private DecimalFormat df = new DecimalFormat("#.##");

    // UI 组件
    private JLabel titleLabel;
    private JLabel questionLabel;
    private JTextField answerField;
    private JButton submitBtn;
    private JButton nextBtn;
    private JLabel scoreLabel;
    private JLabel resultLabel;
    private JLabel accuracyLabel;
    private JPanel mainPanel;
    private CardLayout cardLayout;
    private JPanel gamePanel;

    // 难度设置组件
    private JComboBox<String> difficultyCombo;
    private JComboBox<String> numberTypeCombo;
    private JCheckBox addCheck, subCheck, mulCheck, divCheck;

    public ArithmeticPractice() {
        initUI();
        setTitle("🧮 小学生算术练习");
        setSize(700, 600);
        setMinimumSize(new Dimension(600, 500));
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);  // 居中显示
        // 不在构造时生成题目，等用户设置完点"开始"再生成
    }

    private void initUI() {
        // ========== 主面板 - 使用 CardLayout 切换欢迎页和游戏页 ==========
        cardLayout = new CardLayout();
        mainPanel = new JPanel(cardLayout);
        mainPanel.setBackground(BG_COLOR);

        // 欢迎设置页
        JPanel welcomePanel = createWelcomePanel();
        mainPanel.add(welcomePanel, "welcome");

        // 游戏页
        gamePanel = createGamePanel();
        mainPanel.add(gamePanel, "game");

        setContentPane(mainPanel);
        cardLayout.show(mainPanel, "welcome");
    }

    // ==================== 欢迎设置页面 ====================
    private JPanel createWelcomePanel() {
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.setBackground(BG_COLOR);
        panel.setBorder(new EmptyBorder(40, 60, 40, 60));

        // 标题区域
        JLabel welcomeTitle = new JLabel("🧮 算术练习小能手", SwingConstants.CENTER);
        welcomeTitle.setFont(new Font("微软雅黑", Font.BOLD, 32));
        welcomeTitle.setForeground(PRIMARY_COLOR);
        welcomeTitle.setAlignmentX(Component.CENTER_ALIGNMENT);

        JLabel subtitle = new JLabel("专为小学生设计的趣味算术练习工具", SwingConstants.CENTER);
        subtitle.setFont(new Font("微软雅黑", Font.PLAIN, 14));
        subtitle.setForeground(new Color(150, 150, 150));
        subtitle.setAlignmentX(Component.CENTER_ALIGNMENT);

        panel.add(welcomeTitle);
        panel.add(Box.createRigidArea(new Dimension(0, 5)));
        panel.add(subtitle);
        panel.add(Box.createRigidArea(new Dimension(0, 30)));

        // 设置卡片
        JPanel settingsCard = createSettingsCard();
        settingsCard.setAlignmentX(Component.CENTER_ALIGNMENT);
        settingsCard.setMaximumSize(new Dimension(500, 320));
        panel.add(settingsCard);
        panel.add(Box.createRigidArea(new Dimension(0, 25)));

        // 开始按钮
        JButton startBtn = createStyledButton("🚀  开始练习", PRIMARY_COLOR);
        startBtn.setFont(new Font("微软雅黑", Font.BOLD, 20));
        startBtn.setAlignmentX(Component.CENTER_ALIGNMENT);
        startBtn.setMaximumSize(new Dimension(280, 55));
        startBtn.addActionListener(e -> startGame());
        panel.add(startBtn);
        panel.add(Box.createRigidArea(new Dimension(0, 15)));

        // 当前得分摘要（如果有的话）
        scoreLabel = new JLabel("", SwingConstants.CENTER);
        scoreLabel.setFont(SCORE_FONT);
        scoreLabel.setForeground(TEXT_COLOR);
        scoreLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        panel.add(scoreLabel);

        return panel;
    }

    private JPanel createSettingsCard() {
        JPanel card = new JPanel();
        card.setLayout(new BoxLayout(card, BoxLayout.Y_AXIS));
        card.setBackground(CARD_BG);
        card.setBorder(BorderFactory.createCompoundBorder(
                new LineBorder(new Color(220, 220, 230), 1, true),
                new EmptyBorder(25, 30, 25, 30)));
        // 设置 preferredSize 以保证 BoxLayout 能展开
        card.setMaximumSize(new Dimension(500, 350));

        // 难度选择
        JPanel diffPanel = createRowPanel("📊 难度选择：");
        difficultyCombo = new JComboBox<>(new String[]{"简单", "中等", "困难"});
        difficultyCombo.setFont(LABEL_FONT);
        difficultyCombo.setPreferredSize(new Dimension(200, 35));
        difficultyCombo.setMaximumSize(new Dimension(200, 35));
        difficultyCombo.addActionListener(e -> difficulty = (String) difficultyCombo.getSelectedItem());
        diffPanel.add(difficultyCombo);
        card.add(diffPanel);
        card.add(Box.createRigidArea(new Dimension(0, 15)));

        // 数字类型选择
        JPanel typePanel = createRowPanel("🔢 数字类型：");
        numberTypeCombo = new JComboBox<>(new String[]{"整数", "小数"});
        numberTypeCombo.setFont(LABEL_FONT);
        numberTypeCombo.setPreferredSize(new Dimension(200, 35));
        numberTypeCombo.setMaximumSize(new Dimension(200, 35));
        numberTypeCombo.addActionListener(e -> numberType = (String) numberTypeCombo.getSelectedItem());
        typePanel.add(numberTypeCombo);
        card.add(typePanel);
        card.add(Box.createRigidArea(new Dimension(0, 15)));

        // 运算类型选择
        JPanel opPanel = createRowPanel("✖️ 运算类型：");
        JPanel checkPanel = new JPanel(new FlowLayout(FlowLayout.LEFT, 15, 0));
        checkPanel.setBackground(CARD_BG);
        addCheck = new JCheckBox("➕ 加法", true);
        subCheck  = new JCheckBox("➖ 减法", true);
        mulCheck  = new JCheckBox("✖️ 乘法", true);
        divCheck  = new JCheckBox("➗ 除法", true);
        for (JCheckBox cb : new JCheckBox[]{addCheck, subCheck, mulCheck, divCheck}) {
            cb.setFont(LABEL_FONT);
            cb.setBackground(CARD_BG);
            checkPanel.add(cb);
        }
        opPanel.add(checkPanel);
        card.add(opPanel);

        return card;
    }

    private JPanel createRowPanel(String labelText) {
        JPanel panel = new JPanel(new FlowLayout(FlowLayout.LEFT, 10, 0));
        panel.setBackground(CARD_BG);
        JLabel label = new JLabel(labelText);
        label.setFont(LABEL_FONT);
        label.setForeground(TEXT_COLOR);
        label.setPreferredSize(new Dimension(110, 35));
        panel.add(label);
        return panel;
    }

    // ==================== 游戏页面 ====================
    private JPanel createGamePanel() {
        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout(0, 0));
        panel.setBackground(BG_COLOR);

        // ---- 顶部栏 ----
        JPanel topBar = new JPanel(new BorderLayout());
        topBar.setBackground(PRIMARY_COLOR);
        topBar.setBorder(new EmptyBorder(12, 25, 12, 25));

        titleLabel = new JLabel("算术练习", SwingConstants.LEFT);
        titleLabel.setFont(new Font("微软雅黑", Font.BOLD, 18));
        titleLabel.setForeground(Color.WHITE);
        topBar.add(titleLabel, BorderLayout.WEST);

        // 返回按钮
        JButton backBtn = new JButton("⚙ 设置");
        backBtn.setFont(new Font("微软雅黑", Font.PLAIN, 13));
        backBtn.setForeground(Color.WHITE);
        backBtn.setBackground(new Color(0, 0, 0, 0));
        backBtn.setBorderPainted(false);
        backBtn.setFocusPainted(false);
        backBtn.setCursor(new Cursor(Cursor.HAND_CURSOR));
        backBtn.addActionListener(e -> cardLayout.show(mainPanel, "welcome"));
        topBar.add(backBtn, BorderLayout.EAST);

        panel.add(topBar, BorderLayout.NORTH);

        // ---- 中央区域 ----
        JPanel centerPanel = new JPanel();
        centerPanel.setLayout(new BoxLayout(centerPanel, BoxLayout.Y_AXIS));
        centerPanel.setBackground(BG_COLOR);
        centerPanel.setBorder(new EmptyBorder(30, 40, 20, 40));

        // 题目显示卡片
        JPanel questionCard = new JPanel();
        questionCard.setLayout(new BoxLayout(questionCard, BoxLayout.Y_AXIS));
        questionCard.setBackground(CARD_BG);
        questionCard.setBorder(BorderFactory.createCompoundBorder(
                new LineBorder(new Color(220, 220, 230), 1, true),
                new EmptyBorder(30, 20, 30, 20)));
        questionCard.setAlignmentX(Component.CENTER_ALIGNMENT);
        questionCard.setMaximumSize(new Dimension(500, 180));

        JLabel questionHint = new JLabel("📝 请计算下面的题目：", SwingConstants.CENTER);
        questionHint.setFont(LABEL_FONT);
        questionHint.setForeground(new Color(150, 150, 150));
        questionHint.setAlignmentX(Component.CENTER_ALIGNMENT);
        questionCard.add(questionHint);
        questionCard.add(Box.createRigidArea(new Dimension(0, 15)));

        questionLabel = new JLabel("", SwingConstants.CENTER);
        questionLabel.setFont(QUESTION_FONT);
        questionLabel.setForeground(TEXT_COLOR);
        questionLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        questionCard.add(questionLabel);

        centerPanel.add(questionCard);
        centerPanel.add(Box.createRigidArea(new Dimension(0, 20)));

        // 结果提示
        resultLabel = new JLabel("", SwingConstants.CENTER);
        resultLabel.setFont(RESULT_FONT);
        resultLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
        centerPanel.add(resultLabel);
        centerPanel.add(Box.createRigidArea(new Dimension(0, 15)));

        // 答案输入
        JPanel inputPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 15, 0));
        inputPanel.setBackground(BG_COLOR);
        inputPanel.setAlignmentX(Component.CENTER_ALIGNMENT);

        answerField = new JTextField(12);
        answerField.setFont(new Font("Segoe UI", Font.BOLD, 24));
        answerField.setHorizontalAlignment(JTextField.CENTER);
        answerField.setPreferredSize(new Dimension(200, 50));
        answerField.setBorder(BorderFactory.createCompoundBorder(
                new LineBorder(new Color(200, 200, 210), 2, true),
                new EmptyBorder(5, 10, 5, 10)));
        answerField.addKeyListener(new KeyAdapter() {
            public void keyPressed(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ENTER) {
                    checkAnswer();
                }
            }
        });
        inputPanel.add(answerField);

        submitBtn = createStyledButton("✅ 提交答案", SUCCESS_COLOR);
        submitBtn.setPreferredSize(new Dimension(150, 50));
        submitBtn.addActionListener(e -> checkAnswer());
        inputPanel.add(submitBtn);

        centerPanel.add(inputPanel);
        centerPanel.add(Box.createRigidArea(new Dimension(0, 20)));

        // 下一题按钮
        nextBtn = createStyledButton("➡️ 下一题", PRIMARY_COLOR);
        nextBtn.setFont(BUTTON_FONT);
        nextBtn.setAlignmentX(Component.CENTER_ALIGNMENT);
        nextBtn.setMaximumSize(new Dimension(200, 48));
        nextBtn.addActionListener(e -> generateQuestion());
        nextBtn.setEnabled(false);
        centerPanel.add(nextBtn);

        panel.add(centerPanel, BorderLayout.CENTER);

        // ---- 底部状态栏 ----
        JPanel bottomBar = new JPanel(new GridLayout(1, 2, 20, 0));
        bottomBar.setBackground(new Color(236, 239, 244));
        bottomBar.setBorder(new EmptyBorder(12, 30, 12, 30));

        scoreLabel = new JLabel("📊 已答：0 题", SwingConstants.CENTER);
        scoreLabel.setFont(SCORE_FONT);
        scoreLabel.setForeground(TEXT_COLOR);
        bottomBar.add(scoreLabel);

        accuracyLabel = new JLabel("🎯 正确率：--%", SwingConstants.CENTER);
        accuracyLabel.setFont(SCORE_FONT);
        accuracyLabel.setForeground(TEXT_COLOR);
        bottomBar.add(accuracyLabel);

        panel.add(bottomBar, BorderLayout.SOUTH);

        return panel;
    }

    // ==================== 游戏逻辑 ====================
    private void startGame() {
        // 读取用户设置
        difficulty = (String) difficultyCombo.getSelectedItem();
        numberType = (String) numberTypeCombo.getSelectedItem();
        opEnabled[0] = addCheck.isSelected();
        opEnabled[1] = subCheck.isSelected();
        opEnabled[2] = mulCheck.isSelected();
        opEnabled[3] = divCheck.isSelected();

        // 检查是否至少选了一种运算
        boolean anyOpSelected = false;
        for (boolean b : opEnabled) {
            if (b) { anyOpSelected = true; break; }
        }
        if (!anyOpSelected) {
            JOptionPane.showMessageDialog(this,
                    "请至少选择一种运算类型！", "提示",
                    JOptionPane.WARNING_MESSAGE);
            return;
        }

        cardLayout.show(mainPanel, "game");
        titleLabel.setText("算术练习 - " + difficulty + "模式");
        resultLabel.setText("");
        nextBtn.setEnabled(false);
        totalQuestions = 0;
        correctQuestions = 0;
        updateScore();
        generateQuestion();
        answerField.requestFocusInWindow();
    }

    private void generateQuestion() {
        // 随机选择运算
        String[] ops = new String[4];
        int opCount = 0;
        for (int i = 0; i < 4; i++) {
            if (opEnabled[i]) ops[opCount++] = operations[i];
        }
        currentOp = ops[random.nextInt(opCount)];

        // 根据难度生成操作数
        int maxNum;
        switch (difficulty) {
            case "简单": maxNum = 20; break;
            case "中等": maxNum = 100; break;
            case "困难": maxNum = 500; break;
            default: maxNum = 100;
        }

        currentOperand1 = random.nextInt(maxNum) + 1;
        currentOperand2 = random.nextInt(maxNum) + 1;

        // 根据运算类型调整
        switch (currentOp) {
            case "-":
                // 确保不出现负数结果（小学生友好）
                if (currentOperand1 < currentOperand2) {
                    int tmp = currentOperand1;
                    currentOperand1 = currentOperand2;
                    currentOperand2 = tmp;
                }
                currentAnswer = currentOperand1 - currentOperand2;
                break;
            case "×":
                // 乘法缩小范围
                if (difficulty.equals("困难")) {
                    currentOperand1 = random.nextInt(50) + 1;
                    currentOperand2 = random.nextInt(30) + 1;
                } else {
                    currentOperand1 = random.nextInt(12) + 1;
                    currentOperand2 = random.nextInt(12) + 1;
                }
                currentAnswer = currentOperand1 * currentOperand2;
                break;
            case "÷":
                // 确保整除
                if (difficulty.equals("困难")) {
                    currentOperand1 = random.nextInt(100) + 1;
                    currentOperand2 = random.nextInt(20) + 1;
                } else {
                    currentOperand1 = random.nextInt(50) + 1;
                    currentOperand2 = random.nextInt(10) + 1;
                }
                int product = currentOperand1 * currentOperand2;
                currentAnswer = currentOperand1;  // product / currentOperand2 = currentOperand1
                currentOperand1 = product;
                break;
            default: // "+"
                currentAnswer = currentOperand1 + currentOperand2;
                break;
        }

        // 小数模式：用小数形式展示
        String leftStr, rightStr;
        if (numberType.equals("小数")) {
            double d1, d2;
            switch (currentOp) {
                case "÷":
                    // 除法保持整除，但显示为小数
                    d1 = (double) currentOperand1;
                    d2 = (double) currentOperand2;
                    currentAnswer = d1 / d2;
                    break;
                default:
                    // 随机生成一位小数的操作数
                    d1 = Math.round((random.nextDouble() * maxNum + 0.1) * 10.0) / 10.0;
                    d2 = Math.round((random.nextDouble() * maxNum + 0.1) * 10.0) / 10.0;
                    if (currentOp.equals("-") && d1 < d2) {
                        double tmp = d1; d1 = d2; d2 = tmp;
                    }
                    currentOp = currentOp.replace("×", "*").replace("÷", "/");
                    switch (currentOp) {
                        case "+": currentAnswer = d1 + d2; break;
                        case "-": currentAnswer = d1 - d2; break;
                        case "*":
                            d1 = Math.round(d1); d2 = Math.round(d2);
                            currentAnswer = d1 * d2;
                            break;
                        case "/":
                            d2 = Math.max(1, Math.round(d2));
                            double prod = d1 * d2;
                            currentAnswer = d1;
                            d1 = prod;
                            break;
                    }
                    currentOp = currentOp.replace("*", "×").replace("/", "÷");
                    break;
            }
            leftStr = df.format(d1);
            rightStr = df.format(d2);
        } else {
            leftStr = String.valueOf(currentOperand1);
            rightStr = String.valueOf(currentOperand2);
        }

        questionLabel.setText(leftStr + "  " + currentOp + "  " + rightStr + "  =  ?");
        answerField.setText("");
        answerField.setBorder(BorderFactory.createCompoundBorder(
                new LineBorder(new Color(200, 200, 210), 2, true),
                new EmptyBorder(5, 10, 5, 10)));
        resultLabel.setText("");
        nextBtn.setEnabled(false);
        submitBtn.setEnabled(true);
        answerField.setEnabled(true);
        answerField.requestFocusInWindow();
    }

    private void checkAnswer() {
        String input = answerField.getText().trim();
        if (input.isEmpty()) {
            resultLabel.setText("⚠️ 请输入你的答案");
            resultLabel.setForeground(ACCENT_COLOR);
            answerField.requestFocusInWindow();
            return;
        }

        double userAnswer;
        try {
            // 支持输入小数和整数
            userAnswer = Double.parseDouble(input);
        } catch (NumberFormatException e) {
            resultLabel.setText("⚠️ 请输入有效的数字");
            resultLabel.setForeground(ACCENT_COLOR);
            return;
        }

        totalQuestions++;

        // 比较答案（允许小数精度误差）
        boolean correct = Math.abs(userAnswer - currentAnswer) < 0.001;

        if (correct) {
            correctQuestions++;
            resultLabel.setText("🎉 正确！答案就是 " + formatAnswer(currentAnswer));
            resultLabel.setForeground(SUCCESS_COLOR);
            answerField.setBorder(BorderFactory.createCompoundBorder(
                    new LineBorder(SUCCESS_COLOR, 3, true),
                    new EmptyBorder(5, 10, 5, 10)));
        } else {
            resultLabel.setText("❌ 不对哦，正确答案是 " + formatAnswer(currentAnswer));
            resultLabel.setForeground(ERROR_COLOR);
            answerField.setBorder(BorderFactory.createCompoundBorder(
                    new LineBorder(ERROR_COLOR, 3, true),
                    new EmptyBorder(5, 10, 5, 10)));
        }

        updateScore();
        submitBtn.setEnabled(false);
        answerField.setEnabled(false);
        nextBtn.setEnabled(true);
        nextBtn.requestFocusInWindow();
    }

    private String formatAnswer(double answer) {
        // 如果是整数则不带小数
        if (Math.abs(answer - Math.round(answer)) < 0.0001) {
            return String.valueOf(Math.round(answer));
        }
        return df.format(answer);
    }

    private void updateScore() {
        scoreLabel.setText("📊 已答：" + totalQuestions + " 题  正确：" + correctQuestions + " 题");
        if (totalQuestions > 0) {
            double rate = 100.0 * correctQuestions / totalQuestions;
            accuracyLabel.setText("🎯 正确率：" + df.format(rate) + "%");
            if (rate >= 90) {
                accuracyLabel.setForeground(SUCCESS_COLOR);
            } else if (rate >= 60) {
                accuracyLabel.setForeground(ACCENT_COLOR);
            } else {
                accuracyLabel.setForeground(ERROR_COLOR);
            }
        } else {
            accuracyLabel.setText("🎯 正确率：--%");
            accuracyLabel.setForeground(TEXT_COLOR);
        }
    }

    // ==================== 辅助方法 ====================
    private JButton createStyledButton(String text, Color bgColor) {
        JButton button = new JButton(text);
        button.setFont(BUTTON_FONT);
        button.setForeground(Color.WHITE);
        button.setBackground(bgColor);
        button.setBorder(BorderFactory.createCompoundBorder(
                new LineBorder(bgColor.darker(), 1, true),
                new EmptyBorder(10, 25, 10, 25)));
        button.setFocusPainted(false);
        button.setCursor(new Cursor(Cursor.HAND_CURSOR));
        button.setOpaque(true);

        // 悬停效果
        button.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                button.setBackground(bgColor.brighter());
            }
            public void mouseExited(java.awt.event.MouseEvent evt) {
                button.setBackground(bgColor);
            }
        });

        return button;
    }

    public static void main(String[] args) {
        // 设置系统外观
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
            // 全局字体设置
            UIManager.put("OptionPane.messageFont", new Font("微软雅黑", Font.PLAIN, 14));
            UIManager.put("OptionPane.buttonFont", new Font("微软雅黑", Font.PLAIN, 14));
        } catch (Exception e) {
            e.printStackTrace();
        }

        SwingUtilities.invokeLater(() -> {
            ArithmeticPractice app = new ArithmeticPractice();
            app.setVisible(true);
        });
    }
}
