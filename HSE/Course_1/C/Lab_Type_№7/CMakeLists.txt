# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(Lab_Type_7 C)

# Установка стандарта C
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Создание исполняемого файла
add_executable(Lab7 main.c)
