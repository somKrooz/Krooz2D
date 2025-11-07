cmake_minimum_required(VERSION 3.15)

project(Krooz2D VERSION 2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directory for the .exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Paths
set(ENGINE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Include")
set(ENGINE_SOURCE_DIR  "${CMAKE_SOURCE_DIR}/Source")

set(RGFW_INCLUDE_DIR   "${CMAKE_SOURCE_DIR}/external/RGFW")
set(STB_INCLUDE_DIR   "${CMAKE_SOURCE_DIR}/external/STB")
set(JSON_INCLUDE_DIR   "${CMAKE_SOURCE_DIR}/external/JSON")
set(GLAD_INCLUDE_DIR   "${CMAKE_SOURCE_DIR}/external/GLAD/include")
set(GLAD_SOURCE        "${CMAKE_SOURCE_DIR}/external/GLAD/src/glad.c")

# Collect all .cpp files from your engine source directory
file(GLOB_RECURSE ENGINE_SOURCES "${ENGINE_SOURCE_DIR}/*.cpp")

# Main file
set(MAIN_FILE "${CMAKE_SOURCE_DIR}/main.cpp")

# Create glad as a separate static library
add_library(glad STATIC ${GLAD_SOURCE})
target_include_directories(glad PRIVATE ${GLAD_INCLUDE_DIR})

# Create your main executable
add_executable(${PROJECT_NAME}
    ${ENGINE_SOURCES}
    ${MAIN_FILE}
)

# Include directories for your engine and dependencies
target_include_directories(${PROJECT_NAME} PRIVATE
    ${ENGINE_INCLUDE_DIR}
	${STB_INCLUDE_DIR}
    ${ENGINE_INCLUDE_DIR}/Core
    ${ENGINE_INCLUDE_DIR}/Core/utility
    ${RGFW_INCLUDE_DIR}
	${JSON_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# On Windows, you usually need OpenGL32.lib
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
endif()
