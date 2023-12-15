# Параллельное программирование
## 7 семестр, Лирисман Карина, Б01-008

<image src="fall.jpg">

# Вводные задачи по OpenMP
* [Папка с решениями](/intro_OPENMP/)
* [Скриншоты запуска](/intro_OPENMP/README.md)

# Лабраторная работа №1. вариант 1е2е3е
* [Папка с решениями](/lab_1/)
* [Скриншоты запуска](/lab_1/README.md)

# Дополнительная задача Nested OpenMP
* [Папка с выполнением](additional_tasks/nested_omp/)
* [Скриншоты запуска](additional_tasks/nested_omp/README.md)

# Дополнительная задача Untied OpenMP
* [Папка с выполнением](additional_tasks/untied_tasks/)
* [Скриншоты запуска](additional_tasks/untied_tasks/README.md)

# Дополнительная задача Перемножение Матриц
* [Папка с выполнением](additional_tasks/matrix/)
* [Скриншоты запуска](additional_tasks/matrix/README.md)

# Дополнительная задача Сортировка
* [Папка с выполнением](additional_tasks/sort/)
* [Скриншоты запуска](additional_tasks/sort/README.md)

# Дополнительная задача OpenCL intro
* [Папка с выполнением](additional_tasks/opencl_intro/)

# Дополнительная задача Решето эратосфена
* [Папка с выполнением](additional_tasks/opencl_intro/)
* [Скриншоты запуска](additional_tasks/opencl_intro/README.md)

# Как запустить сие добро

* Переходим в каталог с нашим файлом. Используем g++ для с++ 
```
g++ -fopenmp <имя входного файла с расширением .cpp> -o <имя выходного файла>
```

* Запуск
```
./<имя выходного файла>
```

* Пример с первой вводной таской:
```
cd intro_OPENMP
g++ -fopenmp 1_hello.cpp -o hello
./hello
```