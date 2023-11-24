mkdir -p build
cd build
mkdir -p task_1_build/
cd task_1_build/
g++ -fopenmp ../../src/task_1e.cpp -o task_1e
./task_1e
bash ../../scripts/compare.sh result_task_1_parallel.txt result_task_1_sequential.txt