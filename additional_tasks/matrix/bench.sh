#!/bin/bash

RESULTS_FILE="results.txt"
BUILD="../build"

MATRIX_BIN="./build/additional_matrix"
SEPARATOR="-------------------------------------------------------------------------------"

echo $SEPARATOR >> $RESULTS_FILE

# --compiler-enable-jit=fals


TOTAL_TIME_NULLABLE_NOT_NULLABLE=0
TOTAL_TIME_NULLABLE_NULLABLE=0
NUMBER_OF_TEST=4000

echo "Boosted parallel and sequential mode" >> $RESULTS_FILE
echo $SEPARATOR >> $RESULTS_FILE

for ((i=50; i<=NUMBER_OF_TEST; i+=50))
do

    START=$(date +%s%N)

    # Run the program
    ./build/additional_matrix $i >> $RESULTS_FILE

done
echo "\n\n\n"