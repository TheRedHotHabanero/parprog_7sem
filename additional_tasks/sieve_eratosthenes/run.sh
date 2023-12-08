mkdir -p build
cd build
g++ -fopenmp ../eratosthenes.cpp
rm -rf results.txt
bash ../bench.sh
python3 ../plot.py