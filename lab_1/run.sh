#!/bin/bash

# Путь к первому скрипту
example="scripts/example.sh"

# Путь ко второму скрипту
task1="scripts/task1.sh"

# Проверяем, существуют ли файлы
if [ ! -f "$example" ]; then
    echo "File '$example' is not found."
    exit 1
fi

if [ ! -f "$task1" ]; then
    echo "File '$task1' is not found."
    exit 1
fi

# Запускаем первый скрипт
echo "---------- Run example ----------"
echo " "
bash "$example"
echo "---------- Example completed ----------"
echo " "

# Запускаем второй скрипт
echo "---------- Run task1 ----------"
echo " "
bash "$task1"
echo "---------- Task1 completed ----------"
echo " "

echo "---------- All scripts completed ----------"
echo " "
