#!/bin/bash
# Путь ко второму скрипту
task1="scripts/task1.sh"

if [ ! -f "$task1" ]; then
    echo "File '$task1' is not found."
    exit 1
fi

# Запускаем первый скрипт
echo "---------- Run task1 ----------"
echo " "
bash "$task1"
echo "---------- Task1 completed ----------"
echo " "