#!/usr/bin/python

import sys
from os import path
import os

gen_src_dir = sys.argv[1]
gen_src_files = sys.argv[2].split(";")
if gen_src_files == ['']:
    gen_src_files = []

print("Creating empty \"generated\" sources")

os.makedirs(gen_src_dir, exist_ok=True)

for file in gen_src_files:
    print("File {} ... ".format(file), end="")
    if path.exists(file):
        print("exists")
    else:
        with open(file, 'w') as f:
            f.close()
            print("ok")
