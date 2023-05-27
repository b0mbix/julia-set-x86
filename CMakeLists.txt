cmake_minimum_required(VERSION 3.24)
project(julia_set)

# assembler
enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f elf64 -o <OBJECT> <SOURCE>")

# executables
add_executable(julia_set julia.asm main.c)

# allegro
TARGET_LINK_LIBRARIES(julia_set allegro)

# math
TARGET_LINK_LIBRARIES(julia_set m)
