# Nimble C++

Tasks and helper libraries for C++ course by Antony Polukhin.

[![Build Status](https://travis-ci.org/apolukhin/course-nimble_cpp.svg?branch=master)](https://travis-ci.org/apolukhin/course-nimble_cpp)
[![Build status](https://ci.appveyor.com/api/projects/status/wii3x2jsdxmqyh4i/branch/master?svg=true)](https://ci.appveyor.com/project/apolukhin/course-nimble-cpp/branch/master)
[![codecov](https://codecov.io/gh/apolukhin/course-nimble_cpp/branch/master/graph/badge.svg)](https://codecov.io/gh/apolukhin/course-nimble_cpp)

# Intro (rus):

В любой большой кодовой базе можно встретить куски абсолютно непонятного кода. Как правило такой код пишется чтобы немного выиграть в производительности приложения... и как правило такой код не нужен в принципе, так как оптимизирует не то что нужно, не в том месте где это нужно и не так как надо.

Мы начнём с небольшого примера, на котором встретим все частые ошибки преждевременной оптимизации. После чего мы начнём с основ и рассмотрим

* Алгоритмы стандартной библиотеки и их сложности
* Контейнеры стандартной (и не только) библиотеки, с их особенностями
* Move семантику и её неожиданное поведение
* Многопоточность

Так как курс практический, то все темы мы будем исследовать экспериментально, используя С++ библиотеку для бенчмарков google benchmark. Большая часть задач выглядит как "Вот пример кода на 10-20 строк, давайте его ускорим используя только что изученный материал. А теперь давайте сделаем Х и попробуем объяснить результат". В процессе исследований мы натолкнёмся на особенности аллокаторов, оптимизаторов и имплементаций контейнеров; посмотрим на ассемблерный код; научимся правильно и понятно писать быстрые однопоточные и многопоточные приложения.

Для курса понадобится всего лишь базовые знания C++ и компилятор с поддержкой C++11 (как минимум [Visual Studio 2013](https://www.microsoft.com/ru-ru/SoftMicrosoft/VisualStudio2013.aspx), или Clang-3.3, или [GCC-4.8](https://launchpad.net/~ubuntu-toolchain-r/+archive/ubuntu/test)).
