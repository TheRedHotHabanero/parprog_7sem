#!/bin/bash

# Путь к первому скрипту
example="scripts/example.sh"

# Путь ко второму скрипту
task2="scripts/task2.sh"

# Проверяем, существуют ли файлы
if [ ! -f "$example" ]; then
    echo "File '$example' is not found."
    exit 1
fi

if [ ! -f "$task2" ]; then
    echo "File '$task2' is not found."
    exit 1
fi

# Запускаем первый скрипт
echo "---------- Run example ----------"
echo " "
bash "$example"
echo "---------- Example completed ----------"
echo " "

# Запускаем второй скрипт
echo "---------- Run task2 ----------"
echo " "
bash "$task2"
echo "---------- Task1 completed ----------"
echo " "

echo "---------- All scripts completed ----------"
echo " "
