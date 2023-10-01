
## Запуск
[См главную ридмишку](../README.md)

### Схема работы вложенности
<image src="nesting.png">

В стандарте OpenMP для выяснения своих координат в дереве потоков есть:

1. **omp_get_thread_num()**: Номер текущего потока в рамках текущего уровня параллелизма.

```
int my_thread_num = omp_get_thread_num();
```

2. **omp_get_num_threads()**: С помощью этой функции можно получить общее количество потоков, работающих на текущем уровне параллелизма.

```
int num_threads = omp_get_num_threads();
```

3. **omp_get_level()**: Текущий уровень вложенности параллелизма.

```
int current_level = omp_get_level();
```

4. **omp_get_ancestor_thread_num()**: Номер потока на более высоком уровне вложенности.

```
int ancestor_thread_num = omp_get_ancestor_thread_num(level);
```

5. **omp_get_team_size()**: Количество потоков в текущей команде выполнения, которая может быть меньше общего количества потоков на уровне.

```
int team_size = omp_get_team_size(level);
```

### Скриншоты работы
<image src="screenshots/1.png">

<image src="screenshots/2.png">

<image src="screenshots/3.png">