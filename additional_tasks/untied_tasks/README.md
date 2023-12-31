## Запуск
[См главную ридмишку](../README.md)

### Документация + что-то типа теории
* [Документация Untied Clause OpenMP](https://www.openmp.org/spec-html/5.2/openmpse69.html)

## Untied tasks простыми словами

* Задачи типа untied - это способ выполнять определенные действия в программе параллельно, без строгой связи между ними. Это означает, что эти действия могут выполняться в любом порядке и в разное время, независимо друг от друга.

* Например, если у есть большой список задач, которые могут выполняться параллельно, и нам не важен их порядок выполнения или зависимость друг от друга, то можно использовать задачи типа untied, чтобы ускорить выполнение программы.

* Если задачи типа untied используются неправильно, это может привести к ошибкам в программе из-за непредсказуемого порядка выполнения или гонкам данных.

* В OpenMP по умолчанию предполагается, что операции в программе выполняются последовательно и имеют зависимость друг от друга - учитывается порядок действий.

## Некоторые директивы OpenMP для задач типа Untied

1. **#pragma omp task** : Позволяет создавать независимые задачи, которые могут выполняться асинхронно и в произвольном порядке. Задачи, созданные с помощью этой директивы, считаются "untied", потому что они не обязаны ждать друг друга и могут выполняться независимо.

2. **#pragma omp taskloop**: Используется для создания набора независимых задач, выполняющихся в цикле. Опять же, задачи, созданные внутри этого цикла, считаются "untied" и могут выполняться параллельно.

3. Директива **#pragma omp parallel** с явным созданием задач: также можно использовать #pragma omp parallel для создания явных задач внутри параллельной области.

## Мой пример

Приведены две функции - одну считаем safe mode, вторую unsafe mode. Демонстрация опасного поведения состоит в том, что не учитывается порядок выполнения задач, и поэтому результат работы не может быть гарантированно одинаковым. В то время как в случае safe mode результат гарантированно сохраняется - в этом состоит безопасность поведения. См скриншот работы программа в случае разного запуска. Чем больше потоков участвует, тем больше вероятность расхождения результатов. Особенно видно при сравнении второго и третьего примеров. Аналогично unsafe mode можно подобрать пример такой, чтобы результат работы все же был одинаков, например, арифметические операции одного приоритета (сложение и вычитание, умножение и деление и тд). См закомменченный пример

### Скриншоты работы
<image src="screenshots/1.png">

<image src="screenshots/2.png">

<image src="screenshots/3.png">