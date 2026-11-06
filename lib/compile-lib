#!/usr/bin/env bash

SOURCE_FILE_NAME="lip.cpp"
LIBRARY_NAME="liblip.a"
OBJECT_FILE_NAME="lip.o"

if [[ -f "$LIBRARY_NAME" ]]; then
    rm $LIBRARY_NAME
fi

# Compile into object file
g++ -O3 \
    -g \
    -c \
    -flto \
    -std=c++23 \
    -fsanitize=address \
    -fsanitize=undefined \
    -o $OBJECT_FILE_NAME \
    $SOURCE_FILE_NAME

if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Make library
ar rcs $LIBRARY_NAME $OBJECT_FILE_NAME

if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

rm $OBJECT_FILE_NAME

echo "Library compiled"
