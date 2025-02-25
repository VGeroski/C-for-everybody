cmake_minimum_required(VERSION 3.30)
project(C_for_everybody C)

set(CMAKE_C_STANDARD 11)

add_executable(ReadFile exploring_c/read_file.c)
add_executable(MinMax exploring_c/min_max.c)
add_executable(GuessingGame exploring_c/guessing_game.c)
