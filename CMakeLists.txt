cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)
set(CMAKE_C_STANDARD 11)
set(MLIB_HEADERS include/mlib.h include/mlist.h include/mlog.h include/mmap.h include/mpool.h include/mqueue.h include/mset.h include/mstack.h include/mtypes.h)

project(mlib)
include_directories("include")

aux_source_directory(src SOURCE)
add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCE})
configure_file(mlib.pc.sample mlib.pc @ONLY)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${MLIB_HEADERS}")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RESOURCE mlib.pc)

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${CMAKE_PROJECT_NAME}
        RESOURCE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Werror -O3 -Wl,-undefined -Wl,dynamic_lookup)

# cmake . && make && ctest --verbose
enable_testing()
add_subdirectory(tests)