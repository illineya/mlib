#Устанавливаем проверку на версию cmake
cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)
set(CMAKE_C_STANDARD 11)

#Устанавливаем имя проекта
project(mlib)
include_directories("include")

aux_source_directory(src SOURCE)
add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCE})
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Werror)

# cmake . && make && ctest --verbose
enable_testing()
add_subdirectory(tests)