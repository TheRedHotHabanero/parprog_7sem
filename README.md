# Параллельное программирование
## 7 семестр, Лирисман Карина, Б01-008

<image src="fall.jpg">

# Вводные задачи по OpenMP
* [Условия задач](https://docs.yandex.ru/docs/view?url=ya-disk-public%3A%2F%2FWWP6MJYY23lknWYddiCjurF%2Bel9RP1Tjq4%2FNlfbEvlVSpPZTM6ekRDZrI19xQEcpiyh0ufqrE%2B6HoJ72QHZn3Q%3D%3D%3A%2F%D0%92%D0%B2%D0%BE%D0%B4%D0%BD%D1%8B%D0%B5%20%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B8%20%D0%BF%D0%BE%20OpenMP.pdf&name=%D0%92%D0%B2%D0%BE%D0%B4%D0%BD%D1%8B%D0%B5%20%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B8%20%D0%BF%D0%BE%20OpenMP.pdf&nosw=1)
* [Папка с решениями](/intro_OPENMP/)
* [Скриншоты запуска](/intro_OPENMP/README.md)

# Дополнительная задача Nested OMP
* [Условие](https://docs.yandex.ru/docs/view?url=ya-disk-public%3A%2F%2FWWP6MJYY23lknWYddiCjurF%2Bel9RP1Tjq4%2FNlfbEvlVSpPZTM6ekRDZrI19xQEcpiyh0ufqrE%2B6HoJ72QHZn3Q%3D%3D%3A%2F%D0%94%D0%BE%D0%BF%D0%BE%D0%BB%D0%BD%D0%B8%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%B0%D1%8F_%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_OpenMP_Nested.pdf&name=%D0%94%D0%BE%D0%BF%D0%BE%D0%BB%D0%BD%D0%B8%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%B0%D1%8F_%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_OpenMP_Nested.pdf&nosw=1)
* [Папка с выполнением](/additional_nested_omp/)

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