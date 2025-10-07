cmake_minimum_required(VERSION 3.15)
project(Krooz2D VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB Comp "Components/*.cpp")
file(GLOB Sys "Systems/*.cpp")
file(GLOB Cor "Core/*.cpp")

add_executable(Krooz2D 
    main.cpp
    ${Comp}
    ${Sys}
    ${Cor}
)

target_include_directories(Krooz2D PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Components/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Systems/include
)

