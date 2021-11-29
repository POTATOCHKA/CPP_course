cmake_minimum_required(VERSION 3.0.0)
project(main_Matrix)

add_subdirectory(Matrix)

message("MATRIX_LIB_INCLUDE_DIRS = ${MATRIX_LIB_INCLUDE_DIRS}")
message("MATRIX_LIB_LIBRARIES = ${MATRIX_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} all_works.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O" )

target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MATRIX_LIB_LIBRARIES})

add_subdirectory(tests)
