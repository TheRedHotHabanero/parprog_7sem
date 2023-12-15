mkdir -p build
cd build
mkdir -p task_1_build/
cd task_1_build/
mpic++ ../../src/task_1e.cpp -g -o task_1e
mpirun -np 4 ./task_1e
bash ../../scripts/compare.sh result_task_1_parallel.txt result_task_1_sequential.txt