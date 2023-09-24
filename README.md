# Параллельное программирование
## 7 семестр, Лирисман Карина, Б01-008

<image src="fall.jpg">

# Вводные задачи по OpenMP
* [Условия задач](https://docs.yandex.ru/docs/view?url=ya-disk-public%3A%2F%2FWWP6MJYY23lknWYddiCjurF%2Bel9RP1Tjq4%2FNlfbEvlVSpPZTM6ekRDZrI19xQEcpiyh0ufqrE%2B6HoJ72QHZn3Q%3D%3D%3A%2F%D0%92%D0%B2%D0%BE%D0%B4%D0%BD%D1%8B%D0%B5%20%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B8%20%D0%BF%D0%BE%20OpenMP.pdf&name=%D0%92%D0%B2%D0%BE%D0%B4%D0%BD%D1%8B%D0%B5%20%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B8%20%D0%BF%D0%BE%20OpenMP.pdf&nosw=1)
* [Папка с решениями](/intro_OPENMP/)
* [Скриншоты запуска](/intro_OPENMP/README.md)

# Лабораторная работа №1
* [Условие]()
* [Папка с выполнением]()

# Как запустить сие добро
* Установить mpitch на Ubuntu: 
```
sudo apt install mpich
```

* Переходим к нужному файлу и компилим 
```
cd <путь>/<до>/<папки с файлами,>/<например,>/intro_MPI
mpicc <имя входного файла>.c -o <имя выходного файла>
```
Это было для С. Для С++ ```mpicc -> mpiCC```

* Запуск
```
mpirun -np <количество процессов> ./<имя выходного файла>
```