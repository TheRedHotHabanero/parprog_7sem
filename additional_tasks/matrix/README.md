
## Запуск
```
bash launch.sh
build/additional_matrix <размер матрицы>
```

### Про блоки разделения
Замечено, что бустованная последовательная версия не особенно стабильно работает от количества блоков.
Параллельная бустованная версия ведет себя стабильно при фиксированном размере матрицы.

### Графики
1. Boosted parallel with fixed matrix sizes
<image src="screenshots/boosted_par_fixed.png">

2. Boosted parallel vs boosted sequential
<image src="screenshots/boosted_par_seq.png">

3. Boosted parallel vs trivial parallel
<image src="screenshots/boosted_trivial_par.png">

### Скриншоты работы
<image src="screenshots/1.png">

<image src="screenshots/2.png">

<image src="screenshots/3.png">