cmake_minimum_required (VERSION 2.6)

# This names our project
project (upq C)


# add the dependencies - the other source code files in your program
include_directories(.)

add_library(list list.c)
add_library(upq upq.c)

# This defines the name of our executable, and the file that contains main.
add_executable(upq-test test.c)
target_link_libraries(upq-test list)
target_link_libraries(upq-test upq)



