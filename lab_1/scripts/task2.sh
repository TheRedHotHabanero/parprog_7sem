mkdir -p build
cd build
mkdir -p task_2_build/
cd task_2_build/
g++ -fopenmp ../../src/task_2e.cpp -o task_2e
./task_2e
bash ../../scripts/compare.sh result_task_2_parallel.txt result_task_2_sequential.txt