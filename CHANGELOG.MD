# Changelog

Изменения в версии библиотеки

## [v1.0.0] - 2023-01-28
* Добавлен алгоритм pool
* Добавлен алгоритм list

## [v1.0.1] - 2023-01-28
* Добавлены методы mlist_last, mlist_prepend, mlist_insert_sorted, mlist_length
* Добавлен алгоритм queue
* Добавлен алгоритм stack
* Добавлен проект tests

## [v1.0.2] - 2023-01-30
* Добавлен алгоритм map
* Добавлен метод получения хеш-суммы строки
* Добавлен метод сравления строк
* Исправлен метод mlist_foreach добавлены пользовательские данные
* Исправлен алгоритм mmap_find
* Добалены логи
* Исправлены алгоритмы map, set, queue

## [v1.1.0-release] - 2023-01-30
* Подготовка к релизу
* Тестирование имеющегося функционала

## [v1.1.1] - 23-02-16
* Добавлена совместимость с С++
* Добавлены threads
* Добавлены routine
* Исправлен Mmap_t - добавлена возможность указать вместимость
* Исправлены утечки памяти
* Исправлен MRoutine_t

## [v1.1.2] - 29-03-2023
* Подготовка к релизу
* Добавлены функции перебора по MMap_t с условием
* Исправлены функции mlist_last и mlist_get
* Исправлена функция mmap_foreach_nth

## [v1.1.3] - В разработке
* Добавлена поддержка macos
* Добавлена статическая библиотека
* Добавлена функция получения ключей из MMap_t
* Добавлена функция удаления MList_t при помощи собственной функции очистки памяти
* Исправлены croutine - добавлены потоки по количеству ядер процессора