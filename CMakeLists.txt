cmake_minimum_required(VERSION 3.17)
project(opengl_playground)

include("cmake/shader.cmake")

BIN2H(SOURCE_FILE "shader/none.vert" HEADER_FILE "shader_vertex_none.h" VARIABLE_NAME "shader_vertex_none")
BIN2H(SOURCE_FILE "shader/single_color.frag" HEADER_FILE "shader_fragment_single_color.h" VARIABLE_NAME "shader_fragment_single_color")

set(CMAKE_CXX_STANDARD 20)

set(GLCPP
        "lib/glcpp/src/shader/Shader.cpp"
        "lib/glcpp/src/Program.cpp" lib/glcpp/src/Misc.hpp)

set(EXTERNAL_SOURCES
        "external/glad/src/glad.c"
        ${GLCPP} lib/aml/src/Window.hpp lib/aml/src/window/WindowImplSDL.cpp lib/aml/src/window/WindowImplSDL.hpp lib/aml/src/exception/WindowException.hpp lib/aml/src/WindowManager.cpp lib/aml/src/WindowManager.hpp lib/aml/src/Util.hpp)

add_executable(opengl_playground
        "main.cpp"
        "${EXTERNAL_SOURCES}")
target_link_libraries(opengl_playground
#        SDL2
        ${CMAKE_DL_LIBS})
target_include_directories(opengl_playground PUBLIC
        "external/glad/include"
        "${CMAKE_CURRENT_BINARY_DIR}/include")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(arch_ptr_size "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(arch_ptr_size "x32")
else()
    message(FATAL_ERROR "Can't determine ptr size, please check CMakeLists.txt")
endif()

if(WIN32)
    target_link_libraries(opengl_playground
            "${CMAKE_SOURCE_DIR}/external/SDL2/lib/${arch_ptr_size}/SDL2.lib"
            "${CMAKE_SOURCE_DIR}/external/SDL2/lib/${arch_ptr_size}/SDL2main.lib"
            "${CMAKE_SOURCE_DIR}/external/freetype/lib/${arch_ptr_size}/freetype.lib")

    target_include_directories(opengl_playground PUBLIC
            "external/SDL2/include"
            "external/freetype/include")

    if(NOT(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll"))
        file(COPY "${CMAKE_SOURCE_DIR}/external/SDL2/lib/${arch_ptr_size}/SDL2.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
endif()