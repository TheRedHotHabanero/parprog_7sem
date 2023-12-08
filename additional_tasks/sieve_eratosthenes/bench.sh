#!/bin/bash

RESULTS_FILE="results.txt"

MATRIX_BIN="a.out"

echo $SEPARATOR >> $RESULTS_FILE

# --compiler-enable-jit=fals


TOTAL_TIME_NULLABLE_NOT_NULLABLE=0
TOTAL_TIME_NULLABLE_NULLABLE=0
NUMBER_OF_TEST=200000

echo $SEPARATOR >> $RESULTS_FILE

for ((i=5000; i<=NUMBER_OF_TEST; i+=5000))
do

    START=$(date +%s%N)

    # Run the program
    ./a.out $i 8 >> $RESULTS_FILE

done
echo "\n\n\n"