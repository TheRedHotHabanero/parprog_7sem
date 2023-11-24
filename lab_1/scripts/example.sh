mkdir -p build
cd build
mkdir -p example_build/
cd example_build/
g++ -fopenmp ../../src/example.cpp -o example
./example
bash ../../scripts/compare.sh result_example_parallel.txt result_example_sequential.txt