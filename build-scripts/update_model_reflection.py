#!/usr/bin/python

import sys

source_files = sys.argv[1].split(" ")
output_header_path = sys.argv[2]
tmp_dir = sys.argv[3] or "CMakeFiles/"
timestamps_path = tmp_dir + "model_refl_timestamps"

print("Updating reflection model")
print("Source files", source_files)
print("Output header", output_header_path)
print("Timestamps", timestamps_path)

