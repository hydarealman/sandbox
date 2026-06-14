from pathlib import Path
from textwrap import wrap

from PIL import Image, ImageDraw, ImageFont


ROOT = Path(__file__).resolve().parents[1]
SCREEN_DIR = ROOT / "screenshots"


EXPERIMENTS = [
    ("实验1 安装环境、简单编程与OrderDB初始化", "sql/01_orderdb_setup_and_programming.sql", "outputs/01_orderdb_setup_and_programming.txt"),
    ("实验2 SQL查询", "sql/02_orderdb_queries.sql", "outputs/02_orderdb_queries.txt"),
    ("实验3 BookDB定义、索引、视图与更新", "sql/03_bookdb_definition_indexes_views_updates.sql", "outputs/03_bookdb_definition_indexes_views_updates.txt"),
    ("实验4 游标、存储过程与触发器", "sql/04_orderdb_procedures_triggers.sql", "outputs/04_orderdb_procedures_triggers.txt"),
    ("实验5 安全性定义与检查", "sql/05_security_mysql.sql", "outputs/05_security_mysql.txt"),
    ("实验6 完整性定义与检查", "sql/06_bookdb_integrity.sql", "outputs/06_bookdb_integrity.txt"),
    ("实验7 执行计划", "sql/07_execution_plan.sql", "outputs/07_execution_plan.txt"),
    ("实验8 事务处理", "sql/08_transactions.sql", "outputs/08_transactions.txt"),
    ("实验8 并发隔离级别演示", "scripts/run_transaction_isolation_demo.py", "outputs/08_isolation_demo.txt"),
]


def font(size, mono=False):
    candidates = [
        "C:/Windows/Fonts/consola.ttf" if mono else "C:/Windows/Fonts/msyh.ttc",
        "C:/Windows/Fonts/simsun.ttc",
        "C:/Windows/Fonts/arial.ttf",
    ]
    for candidate in candidates:
        if candidate and Path(candidate).exists():
            return ImageFont.truetype(candidate, size)
    return ImageFont.load_default()


TITLE_FONT = font(32)
LABEL_FONT = font(22)
TEXT_FONT = font(18)
SMALL_FONT = font(16)


def read_text_smart(path):
    data = (ROOT / path).read_bytes()
    for encoding in ("utf-8-sig", "utf-16", "gbk"):
        try:
            return data.decode(encoding)
        except UnicodeDecodeError:
            pass
    return data.decode("utf-8", errors="replace")


def read_excerpt(path, head=70, tail=75):
    text = read_text_smart(path).splitlines()
    if len(text) <= head + tail:
        lines = text
    else:
        lines = text[:head] + ["...", f"... 省略中间 {len(text) - head - tail} 行 ...", "..."] + text[-tail:]
    return lines


def draw_wrapped(draw, xy, text, max_width, fill, font_obj, line_height):
    x, y = xy
    current = ""
    for ch in text.replace("\t", "  "):
        candidate = current + ch
        if draw.textlength(candidate, font=font_obj) <= max_width:
            current = candidate
        else:
            if current:
                draw.text((x, y), current, fill=fill, font=font_obj)
                y += line_height
            current = ch
    if current:
        draw.text((x, y), current, fill=fill, font=font_obj)
        y += line_height
    return y


def draw_panel(draw, x, y, w, h, label, lines):
    draw.rectangle((x, y, x + w, y + h), fill=(255, 255, 255), outline=(180, 180, 180), width=1)
    draw.text((x + 20, y + 16), label, fill=(0, 0, 0), font=LABEL_FONT)
    draw.line((x + 20, y + 54, x + w - 20, y + 54), fill=(180, 180, 180), width=1)
    content_y = y + 62
    max_width = w - 40
    line_height = 24
    for line in lines:
        if content_y + line_height > y + h - 18:
            draw.text((x + 20, content_y), "...", fill=(80, 80, 80), font=TEXT_FONT)
            break
        content_y = draw_wrapped(draw, (x + 20, content_y), line, max_width, (0, 0, 0), TEXT_FONT, line_height)


def make_one(index, title, code_path, output_path):
    width, height = 1800, 2200
    img = Image.new("RGB", (width, height), (255, 255, 255))
    draw = ImageDraw.Draw(img)

    draw.text((70, 50), title, fill=(0, 0, 0), font=TITLE_FONT)
    draw.text((70, 94), "源码与真实运行输出截图", fill=(60, 60, 60), font=SMALL_FONT)
    draw.line((70, 120, width - 70, 120), fill=(160, 160, 160), width=1)

    code_lines = read_excerpt(code_path, head=65, tail=45)
    out_lines = read_excerpt(output_path, head=35, tail=80)

    draw_panel(draw, 70, 145, 800, 1975, f"代码：{code_path}", code_lines)
    draw_panel(draw, 930, 145, 800, 1975, f"运行输出：{output_path}", out_lines)

    out_path = SCREEN_DIR / f"experiment_{index:02d}.png"
    img.save(out_path)
    return out_path


def main():
    SCREEN_DIR.mkdir(parents=True, exist_ok=True)
    for idx, item in enumerate(EXPERIMENTS, 1):
        path = make_one(idx, *item)
        print(path)


if __name__ == "__main__":
    main()
