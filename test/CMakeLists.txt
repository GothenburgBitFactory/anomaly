cmake_minimum_required (VERSION 2.8)
include_directories (${CMAKE_SOURCE_DIR}
                     ${CMAKE_SOURCE_DIR}/src
                     ${CMAKE_SOURCE_DIR}/test)

add_custom_target (test ./run_all WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test)

