cmake_minimum_required(VERSION 3.13)
find_package(PkgConfig REQUIRED)

add_executable(mlist mlist.c)
target_link_libraries(mlist ${CMAKE_SOURCE_DIR}/libmlib.so)
target_compile_options(mlist PUBLIC -g -O0)

add_executable(mqueue mqueue.c)
target_link_libraries(mqueue ${CMAKE_SOURCE_DIR}/libmlib.so)
target_compile_options(mqueue PUBLIC -g -O0)

add_executable(mstack mstack.c)
target_link_libraries(mstack ${CMAKE_SOURCE_DIR}/libmlib.so)
target_compile_options(mstack PUBLIC -g -O0)

add_executable(mmap mmap.c)
target_link_libraries(mmap ${CMAKE_SOURCE_DIR}/libmlib.so)
target_compile_options(mmap PUBLIC -g -O0)

add_executable(mset mset.c)
target_link_libraries(mset ${CMAKE_SOURCE_DIR}/libmlib.so)
target_compile_options(mset PUBLIC -g -O0)

add_executable(mpool mpool.c)
target_link_libraries(mpool ${CMAKE_SOURCE_DIR}/libmlib.so)
target_compile_options(mpool PUBLIC -g -O0)

enable_testing()
add_test(mlist mlist)
add_test(mqueue mqueue)
add_test(mstack mstack)
add_test(mmap mmap)
add_test(mset mset)
add_test(mpool mpool)