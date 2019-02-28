cmake_minimum_required(VERSION 2.6)

project(DatabaseStorageManager)

set(include_directory ${PROJECT_SOURCE_DIR}/inc)

#Initializing input directories
set(output_executable_directory ${CMAKE_BINARY_DIR}/bin)

include_directories(${include_directory}) 

aux_source_directory(${PROJECT_SOURCE_DIR}/src srcs)

add_executable(main ${srcs})









