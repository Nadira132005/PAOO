cmake_minimum_required(VERSION 3.16)

project(app LANGUAGES CXX)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE Calculator::calculator)
set_target_properties(app PROPERTIES CXX_EXTENSIONS OFF)
