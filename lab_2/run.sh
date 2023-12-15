mkdir -p build
cd build
g++ -fopenmp ../main.cpp -o main
./main
python3 ../plot.py solution_a_100.000000.txt