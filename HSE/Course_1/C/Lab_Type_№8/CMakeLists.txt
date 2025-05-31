cmake_minimum_required(VERSION 3.10)
project(Lab_Type_8 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Указываем и .c, и .h файлы (хотя .h можно не указывать — они подтянутся автоматически)
add_executable(Lab8 main.c Setlib.h)
