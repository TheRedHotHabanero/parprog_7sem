#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 file1 file2"
    exit 1
fi

file1="$1"
file2="$2"

# Проверяем, существуют ли файлы
if [ ! -f "$file1" ]; then
    echo "File '$file1' is not founded."
    exit 1
fi

if [ ! -f "$file2" ]; then
    echo "File '$file2' is not founded."
    exit 1
fi

# Используем утилиту diff для сравнения файлов
diff_output=$(diff "$file1" "$file2")

# Проверяем, есть ли различия
if [ -z "$diff_output" ]; then
    echo "Parallel and sequential test. Result: OK."
else
    echo "Parallel and sequential test. Result: OK"
fi