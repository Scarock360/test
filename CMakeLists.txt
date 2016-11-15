project(ConanTest)
cmake_minimum_required(VERSION 2.8.12)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB A_Sources "*.cpp" "*.h")

add_executable(conanTest ${A_Sources})

target_link_libraries(conanTest ${CONAN_LIBS})

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "conanTest")