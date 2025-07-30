import os
import shutil

Include_Lists = ["Components", "Core"]
base_path = os.path.abspath(".")
output_root = os.path.join(base_path, "Krooz2d")
include_output_dir = os.path.join(output_root, "include")
lib_output_dir = os.path.join(output_root, "lib")
header_output_path = os.path.join(include_output_dir, "krooz2d.h")

os.makedirs(include_output_dir, exist_ok=True)
os.makedirs(lib_output_dir, exist_ok=True)

all_headers = []

for module in Include_Lists:
    include_dir = os.path.join(base_path, module, "include")
    if os.path.exists(include_dir):
        for filename in os.listdir(include_dir):
            src_file = os.path.join(include_dir, filename)
            dst_file = os.path.join(include_output_dir, filename)
            if os.path.isfile(src_file):
                shutil.copy2(src_file, dst_file)
                all_headers.append(filename)
    else:
        print(f"Warning: {include_dir} does not exist.")

with open(header_output_path, "w") as file:
    for header in all_headers:
        file.write(f"#include <{header}>\n")

krooz_lib_source = os.path.join(base_path, "build", "lib", "krooz.lib")
krooz_lib_dest = os.path.join(lib_output_dir, "krooz2d.lib")

if os.path.exists(krooz_lib_source):
    shutil.copy2(krooz_lib_source, krooz_lib_dest)
else:
    print(f"Warning: {krooz_lib_source} does not exist.")
