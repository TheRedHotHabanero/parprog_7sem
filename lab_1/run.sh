mkdir -p build
cd build
g++ -fopenmp ../example.cpp -o example
./example
bash ../compare.sh