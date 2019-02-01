cmake_minimum_required(VERSION 3.0)

project(tea C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# GLFW
add_subdirectory(deps/glfw)

# Glad
add_library(glad deps/glad/src/glad.c)
target_include_directories(glad PUBLIC deps/glad/include)

# Wren
set(WREN_SOURCES
        deps/wren/src/vm/wren_compiler.c
        deps/wren/src/vm/wren_core.c
        deps/wren/src/vm/wren_debug.c
        deps/wren/src/vm/wren_primitive.c
        deps/wren/src/vm/wren_utils.c
        deps/wren/src/vm/wren_value.c
        deps/wren/src/vm/wren_vm.c

        deps/wren/src/optional/wren_opt_meta.c
        deps/wren/src/optional/wren_opt_random.c
        )

add_library(wren ${WREN_SOURCES})
target_include_directories(wren PRIVATE deps/wren/src/optional deps/wren/src/vm)
target_include_directories(wren BEFORE PUBLIC deps/wren/src/include)  # BEFORE to override system wren.h if existing
target_compile_definitions(wren PRIVATE _CRT_SECURE_NO_WARNINGS) # To prevent spewing errors on MSVC

# STB
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE deps/stb)

# Resources
include(deps/cmrc/CMakeRC.cmake)
cmrc_add_resource_library(tea-res NAMESPACE tea WHENCE res/
        res/tea/graphics.wren
        res/tea/prelude.wren)

# Engine
set(ENGINE_SOURCES
        src/modules/input.cpp
        src/modules/input.h
        src/modules/renderer.cpp
        src/modules/renderer.h
        src/platforms/platform_glfw.cpp
        src/platforms/platform_glfw.h
        src/assets.cpp
        src/assets.h
        src/engine.cpp
        src/engine.h
        src/main.cpp
        src/module.h
        src/platform.h
        src/utils.cpp
        src/utils.h)

add_executable(tea ${ENGINE_SOURCES})
target_link_libraries(tea tea-res wren stb glfw glad)
if (MSVC)
    target_compile_options(tea PRIVATE /W4 /wd4100 /D _CRT_SECURE_NO_WARNINGS)
else ()
    target_compile_options(tea PRIVATE -Wall -Wextra -pedantic -Wno-error=unused-parameter)
endif ()