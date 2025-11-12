cmake_minimum_required(VERSION 3.15)
project(Krooz2D VERSION 0.2 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(ENGINE_SRC "${CMAKE_SOURCE_DIR}/Source")
set(ENGINE_INCLUDE "${CMAKE_SOURCE_DIR}/Include")

set(RGFW "${CMAKE_SOURCE_DIR}/external/RGFW")
set(STB "${CMAKE_SOURCE_DIR}/external/STB")
set(JSON "${CMAKE_SOURCE_DIR}/external/JSON")

set(GLAD_INCLUDE "${CMAKE_SOURCE_DIR}/external/GLAD/include")
set(GLAD_SRC "${CMAKE_SOURCE_DIR}/external/GLAD/src/glad.c")

file(GLOB_RECURSE ENGINE_SOURCES "${ENGINE_SRC}/*.cpp")

add_library(Krooz2D STATIC
	${ENGINE_SOURCES}
	${GLAD_SRC}
)

target_include_directories(Krooz2D PUBLIC
	${ENGINE_INCLUDE}
    ${ENGINE_INCLUDE}/Core
    ${STB}
    ${RGFW}
    ${JSON}
    ${GLAD_INCLUDE}
)

target_link_libraries(Krooz2D PUBLIC -lopengl32)

add_custom_command(TARGET Krooz2D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/include"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ENGINE_INCLUDE}"
        "${CMAKE_BINARY_DIR}/include"
    COMMENT "Copying engine headers to build/include"
)
