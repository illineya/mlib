cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)
set(CMAKE_C_STANDARD 11)

project(mlib)
include_directories("include")
aux_source_directory(src SOURCE)

add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCE})
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Werror -pedantic -O3 -Wl,-undefined -Wl,dynamic_lookup)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RESOURCE mlib.pc)
configure_file(mlib.pc.sample mlib.pc @ONLY)
install(DIRECTORY include/ DESTINATION include/mlib FILES_MATCHING PATTERN "*.h")
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RESOURCE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)

# cmake . && make && ctest --verbose
enable_testing()
add_subdirectory(tests)