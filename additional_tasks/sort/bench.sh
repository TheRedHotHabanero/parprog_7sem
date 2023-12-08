#!/bin/bash

RESULTS_FILE="resultss.txt"

MATRIX_BIN="./additional_sort"
SEPARATOR="-------------------------------------------------------------------------------"

echo $SEPARATOR >> $RESULTS_FILE

# --compiler-enable-jit=fals


TOTAL_TIME_NULLABLE_NOT_NULLABLE=0
TOTAL_TIME_NULLABLE_NULLABLE=0
NUMBER_OF_TEST=10000000

echo "2 Variant. treshold = 300" >> $RESULTS_FILE
echo $SEPARATOR >> $RESULTS_FILE

for ((i=1000000; i<=NUMBER_OF_TEST; i+=100000))
do

    START=$(date +%s%N)
    # Run the program
    ./additional_sort $i >> $RESULTS_FILE

done
echo "\n\n\n"