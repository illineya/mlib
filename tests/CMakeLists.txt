cmake_minimum_required(VERSION 3.13)
find_package(PkgConfig REQUIRED)

add_executable(mlist mlist.c)
target_link_libraries(mlist ${CMAKE_SOURCE_DIR}/libmlib.so)

enable_testing()
add_test(mlist mlist)