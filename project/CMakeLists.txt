cmake_minimum_required(VERSION 3.0.0)
project(all_func)

add_subdirectory(func)

message("FUNC_LIB_INCLUDE_DIRS = ${FUNC_LIB_INCLUDE_DIRS}")
message("FUNC_LIB_LIBRARIES = ${FUNC_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} all_works.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${FUNC_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FUNC_LIB_LIBRARIES})

add_subdirectory(tests)
