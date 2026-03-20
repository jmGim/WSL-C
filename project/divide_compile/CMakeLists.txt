cmake_minimum_required(VERSION 3.10)

# Name of your project
project(avg3)

# Use the C11 standard
set(CMAKE_C_STANDARD 11)

# Find all .c files in the directory and store them in the SOURCES variable
# file(GLOB SOURCES "*.c")

# Create an executable named 'my_program' from the source files
add_executable(my_program 
    ./main.c
    ./input.c
    ./print.c
    ./average.c
    )
