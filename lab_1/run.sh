#!/bin/bash

# Путь к первому скрипту
example="scripts/example.sh"

# Путь ко второму скрипту
task1="scripts/task1.sh"

# Путь ко второму скрипту
task2="scripts/task2.sh"

# Путь ко второму скрипту
task3="scripts/task3.sh"

# Проверяем, существуют ли файлы
if [ ! -f "$example" ]; then
    echo "File '$example' is not found."
    exit 1
fi

if [ ! -f "$task1" ]; then
    echo "File '$task1' is not found."
    exit 1
fi

if [ ! -f "$task2" ]; then
    echo "File '$task2' is not found."
    exit 1
fi

if [ ! -f "$task3" ]; then
    echo "File '$task3' is not found."
    exit 1
fi

# Запускаем примерный скрипт
echo "---------- Run example ----------"
echo " "
bash "$example"
echo "---------- Example completed ----------"
echo " "

# Запускаем первый скрипт
# echo "---------- Run task1 ----------"
# echo " "
# bash "$task1"
# echo "---------- Task1 completed ----------"
# echo " "
# 
# # Запускаем второй скрипт
# echo "---------- Run task2 ----------"
# echo " "
# bash "$task2"
# echo "---------- Task2 completed ----------"
# echo " "
# 
# # Запускаем третий скрипт
# echo "---------- Run task3 ----------"
# echo " "
# bash "$task3"
# echo "---------- Task3 completed ----------"
# echo " "
# 
# echo "---------- All scripts completed ----------"
# echo " "
