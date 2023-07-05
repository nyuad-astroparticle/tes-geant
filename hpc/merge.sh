#!/bin/bash

# Check if the directory path is provided
if [ $# -lt 1 ]; then
  echo "Usage: ./parallel_merge.sh <directory_path>"
  exit 1
fi

directory_path=$1

# Get the list of files in the directory
files=$(find "$directory_path" -type f)

# Merge content starting from the 13th line of each file
merged_content=""
for file in $files; do
  file_content=$(tail -n +14 "$file")
  merged_content+="$file_content"
done

# Print the merged content
echo "$merged_content"