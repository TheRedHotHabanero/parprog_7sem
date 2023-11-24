#!/bin/bash

file1="result_example_sequential.txt"
file2="result_example_parallel.txt"

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
    echo "Parallel and sequential test. Result: NOT OK.. See diff: "
    echo "$diff_output"
fi