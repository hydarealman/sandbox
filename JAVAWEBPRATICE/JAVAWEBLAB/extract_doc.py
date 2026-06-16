import olefile
import sys
import os

# Set output encoding
sys.stdout.reconfigure(encoding='utf-8')

doc_dir = r'C:\Users\dong\Desktop\javaweb实验报告\javaweb实验指导书'
output_dir = r'd:\sandbox\JAVAWEBPRATICE\JAVAWEBLAB\experiment_texts'

os.makedirs(output_dir, exist_ok=True)

files = sorted([f for f in os.listdir(doc_dir) if f.endswith('.doc')])

for fname in files:
    fpath = os.path.join(doc_dir, fname)
    out_path = os.path.join(output_dir, fname.replace('.doc', '.txt'))
    print(f"Processing: {fname}")

    try:
        ole = olefile.OleFileIO(fpath)
        # Try to read the WordDocument stream
        if ole.exists('WordDocument'):
            data = ole.openstream('WordDocument').read()
        else:
            print(f"  No WordDocument stream in {fname}")
            ole.close()
            continue

        ole.close()

        # .doc format stores text in the WordDocument stream
        # The text is usually in the '1Table' or '0Table' stream
        ole = olefile.OleFileIO(fpath)

        # Try to get text from streams
        text_parts = []
        for stream_name in ole.listdir():
            stream_path = '/'.join(stream_name)
            try:
                data = ole.openstream(stream_path).read()
                # Try to decode as various encodings
                for enc in ['utf-16-le', 'utf-8', 'gbk', 'cp1252']:
                    try:
                        decoded = data.decode(enc, errors='ignore')
                        if any('一' <= c <= '鿿' for c in decoded[:500]):
                            text_parts.append(f"--- {stream_path} ({enc}) ---\n{decoded[:5000]}")
                            break
                    except:
                        pass
            except:
                pass

        ole.close()

        with open(out_path, 'w', encoding='utf-8') as f:
            if text_parts:
                f.write('\n\n'.join(text_parts))
            else:
                f.write(f"Could not extract text from {fname}\n")
                f.write(f"Streams found: {ole.listdir()}\n")

        print(f"  -> {out_path}")
    except Exception as e:
        print(f"  Error: {e}")

print("Done!")
