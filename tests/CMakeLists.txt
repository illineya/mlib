cmake_minimum_required(VERSION 3.13)
find_package(PkgConfig REQUIRED)

set(LIB "libmlib.so")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(LIB "libmlib.dylib")
endif()

add_executable(mlist mlist.c)
target_link_libraries(mlist -pthread ${CMAKE_SOURCE_DIR}/${LIB})
target_compile_options(mlist PUBLIC -g -O0)

add_executable(mqueue mqueue.c)
target_link_libraries(mqueue -pthread ${CMAKE_SOURCE_DIR}/${LIB})
target_compile_options(mqueue PUBLIC -g -O0)

add_executable(mstack mstack.c)
target_link_libraries(mstack -pthread ${CMAKE_SOURCE_DIR}/${LIB})
target_compile_options(mstack PUBLIC -g -O0)

add_executable(mmap mmap.c)
target_link_libraries(mmap -pthread ${CMAKE_SOURCE_DIR}/${LIB})
target_compile_options(mmap PUBLIC -g -O0)

add_executable(mset mset.c)
target_link_libraries(mset -pthread ${CMAKE_SOURCE_DIR}/${LIB})
target_compile_options(mset PUBLIC -g -O0)

add_executable(mpool mpool.c)
target_link_libraries(mpool -pthread ${CMAKE_SOURCE_DIR}/${LIB})
target_compile_options(mpool PUBLIC -g -O0)

add_executable(mthread mthread.c)
target_link_libraries(mthread -pthread ${CMAKE_SOURCE_DIR}/${LIB})
target_compile_options(mthread PUBLIC -g -O0)

add_executable(mroutine mroutine.c)
target_link_libraries(mroutine -pthread ${CMAKE_SOURCE_DIR}/${LIB})
target_compile_options(mroutine PUBLIC -g -O0)

enable_testing()
add_test(mlist mlist)
add_test(mqueue mqueue)
add_test(mstack mstack)
add_test(mmap mmap)
add_test(mset mset)
add_test(mpool mpool)
add_test(mthread mthread)
add_test(mroutine mroutine)