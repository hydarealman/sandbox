import olefile
import os
import sys
import re

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

        # .doc format: text is in WordDocument stream
        # The OLE compound document has specific streams
        text_content = ""

        # Try reading the WordDocument stream
        for stream_info in ole.listdir():
            stream_name = '/'.join(stream_info)

            try:
                raw = ole.openstream(stream_info).read()

                # Try to extract readable text
                # In .doc files, text is usually UTF-16LE encoded in the WordDocument stream
                # The 1Table stream contains the text table
                if 'WordDocument' in stream_name or stream_name == 'WordDocument':
                    # Extract text from the WordDocument stream
                    # The text starts at offset specified in the FIB
                    pass

                # Try common encodings for each stream
                for enc in ['utf-16-le', 'gbk', 'utf-8']:
                    try:
                        decoded = raw.decode(enc, errors='ignore')
                        # Filter for streams that look like they contain Chinese text
                        if len(decoded) > 10:
                            # Check if contains Chinese characters
                            chinese_chars = sum(1 for c in decoded if '一' <= c <= '鿿' or '　' <= c <= '〿')
                            if chinese_chars > 5:
                                text_content += f"\n\n=== Stream: {stream_name} ({enc}) ===\n"
                                text_content += decoded
                                break
                    except:
                        pass
            except Exception as e:
                pass

        ole.close()

        if text_content.strip():
            with open(out_path, 'w', encoding='utf-8') as f:
                f.write(text_content)
            print(f"  -> Written to {out_path}")
        else:
            # Fallback: try to extract all readable text
            print(f"  No Chinese text found, trying full extraction...")
            ole = olefile.OleFileIO(fpath)
            all_text = ""
            for stream_info in ole.listdir():
                stream_name = '/'.join(stream_info)
                try:
                    raw = ole.openstream(stream_info).read()
                    # Extract ASCII printable strings
                    strings = re.findall(rb'[\x20-\x7e一-鿿]{4,}', raw)
                    if strings:
                        all_text += f"\n--- {stream_name} ---\n"
                        for s in strings:
                            try:
                                decoded = s.decode('utf-16-le', errors='ignore')
                                all_text += decoded + '\n'
                            except:
                                pass
                except:
                    pass
            ole.close()

            with open(out_path, 'w', encoding='utf-8') as f:
                f.write(all_text if all_text.strip() else "No extractable text found")
            print(f"  -> Written to {out_path} ({len(all_text)} chars)")

    except Exception as e:
        print(f"  Error processing {fname}: {e}")

print("\nDone extracting all documents!")
