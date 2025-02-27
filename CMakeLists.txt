cmake_minimum_required(VERSION 3.30)
project(C_for_everybody C)

set(CMAKE_C_STANDARD 11)

add_executable(ReadFile exploring_c/read_file.c)
add_executable(MinMax exploring_c/min_max.c)
add_executable(GuessingGame exploring_c/guessing_game.c)
add_executable(FahrCelsTable exploring_c/fahr_cels_table.c)
add_executable(CopyOut exploring_c/copy_out.c)
add_executable(CountChars exploring_c/count_chars.c)
add_executable(SimpleWC exploring_c/simple_wc.c)
