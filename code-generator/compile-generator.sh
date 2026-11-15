#!/usr/bin/env bash

SOURCE_FILE_NAME="generator.cpp"
OUTPUT_FILE_NAME="generate"

if [[ -f "$OUTPUT_FILE_NAME" ]]; then
    rm $OUTPUT_FILE_NAME
fi

# Compile
g++ -O3 \
    -g \
    -std=c++23 \
    -o $OUTPUT_FILE_NAME \
    $SOURCE_FILE_NAME

if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

mv $OUTPUT_FILE_NAME ../$OUTPUT_FILE_NAME
echo "Generator compiled"
