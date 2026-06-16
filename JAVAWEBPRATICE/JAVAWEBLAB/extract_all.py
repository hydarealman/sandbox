"""Extract text from all .doc experiment guide files."""
import os
import re
import sys

doc_dir = r'C:\Users\dong\Desktop\javaweb实验报告\javaweb实验指导书'
output_dir = r'd:\sandbox\JAVAWEBPRATICE\JAVAWEBLAB\experiment_texts'

os.makedirs(output_dir, exist_ok=True)

files = sorted([f for f in os.listdir(doc_dir) if f.endswith('.doc') and f != '实验报告模板.docx'])

for fname in files:
    fpath = os.path.join(doc_dir, fname)
    out_path = os.path.join(output_dir, fname.replace('.doc', '.txt'))

    with open(fpath, 'rb') as f:
        data = f.read()

    # Decode as UTF-16LE
    decoded = data.decode('utf-16-le', errors='ignore')

    # Clean up - keep lines that look like meaningful text
    lines = decoded.split('\r')
    clean_lines = []
    for line in lines:
        stripped = line.strip()
        if not stripped or len(stripped) < 2:
            continue

        # Check if line has Chinese characters or meaningful ASCII text
        has_chinese = any('一' <= c <= '鿿' or '　' <= c <= '〿' or '＀' <= c <= '￯' for c in stripped)
        has_ascii_text = sum(1 for c in stripped if c.isascii() and c.isalpha()) > 5
        has_digits = any(c.isdigit() for c in stripped)
        is_meaningful = has_chinese or has_ascii_text or (has_digits and len(stripped) > 5)

        if is_meaningful:
            clean_lines.append(stripped)

    # Remove consecutive duplicates (binary noise often creates duplicates)
    deduped = []
    prev = None
    for line in clean_lines:
        if line != prev:
            deduped.append(line)
        prev = line

    with open(out_path, 'w', encoding='utf-8') as f:
        f.write('\n'.join(deduped))

    print(f'Extracted {len(deduped)} lines from: {fname}')

print('\nDone! All files extracted.')
