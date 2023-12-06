mkdir -p build
cd build
mkdir -p task_3_build/
cd task_3_build/
g++ -fopenmp ../../src/task_3e.cpp -o task_3e
./task_3e
bash ../../scripts/compare.sh result_task_3_parallel.txt result_task_3_sequential.txt