cmake_minimum_required(VERSION 3.28)
project(foh LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory(foh)
add_subdirectory(extern)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -DDEBUG>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glm::glm
    glad
    stb_image
)
