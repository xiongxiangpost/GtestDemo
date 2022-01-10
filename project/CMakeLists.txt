cmake_minimum_required(VERSION 3.10)
project(GtestDemo VERSION 1.0.1)

SET(BIN_DESTINATION ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DESTINATION})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DESTINATION})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DESTINATION})

include_directories(source)
include_directories(gtest/include)

link_directories(gtest/lib)

aux_source_directory(${PROJECT_SOURCE_DIR}/source SRCS)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} gtest gtest_main gmock pthread)