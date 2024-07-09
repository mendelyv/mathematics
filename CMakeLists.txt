project(cpp_math)
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/src/include)

file(GLOB MAIN_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB MAIN_HEAD ${PROJECT_SOURCE_DIR}/src/include/*.h)

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${MAIN_HEAD})
