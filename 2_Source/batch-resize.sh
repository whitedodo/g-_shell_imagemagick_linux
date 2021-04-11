#!/bin/bash

# Catch user input for file type.

#echo "Enter the file extension for your image files:"
echo "그림 파일과 확장자명을 입력해주세요. 전체: *"

# Store user input in $files.

read files

# Resize images.

for img in *.$files; do
#convert -resize 20% "$img" "resize-$img"
	convert -resize 40% "original/$img" "convert/$img"

done
