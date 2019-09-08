cmake_minimum_required(VERSION 3.0)

project(tea C CXX)

# GLFW
if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_INSTALL OFF)

    add_subdirectory(deps/glfw)
endif()

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

# stb
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE deps/stb)

# stb_vorbis
add_library(stb_vorbis deps/stb/stb_vorbis.c)
target_compile_definitions(stb_vorbis PUBLIC STB_VORBIS_NO_STDIO)
target_compile_definitions(stb_vorbis INTERFACE STB_VORBIS_HEADER_ONLY)

# PortAudio
add_subdirectory(deps/portaudio)

# {fmt}
add_library(fmt deps/fmt/src/format.cc)
target_include_directories(fmt PUBLIC deps/fmt/include)

# Resources
include(deps/cmrc/CMakeRC.cmake)
cmrc_add_resource_library(tea-res NAMESPACE tea WHENCE res/
        res/tea/input.wren
        res/tea/graphics.wren
        res/tea/prelude.wren)

# Engine
set(ENGINE_SOURCES
        src/assets/asset.cpp
        src/assets/asset.h
        src/assets/image.cpp
        src/assets/image.h
        src/assets/image_loader.cpp
        src/assets/image_loader.h
        src/assets/ogg_sound.cpp
        src/assets/ogg_sound.h
        src/assets/ogg_sound_player.cpp
        src/assets/ogg_sound_player.h
        src/assets/sound.h
        src/assets/sound_loader.cpp
        src/assets/sound_loader.h
        src/assets/sound_player.h
        src/modules/audio.cpp
        src/modules/audio.h
        src/modules/input.cpp
        src/modules/input.h
        src/modules/renderer.cpp
        src/modules/renderer.h
        src/platforms/platform_glfw.cpp
        src/platforms/platform_glfw.h
        src/assets.cpp
        src/assets.h
        src/bindings.cpp
        src/bindings.h
        src/color.cpp
        src/color.h
        src/engine.cpp
        src/engine.h
        src/main.cpp
        src/module.h
        src/platform.h
        src/scripting.h
        src/scripting.cpp
        src/utils.cpp
        src/utils.h
        src/vec.h)

add_executable(tea ${ENGINE_SOURCES})
set_target_properties(tea PROPERTIES C_STANDARD 11 CXX_STANDARD 11)
target_compile_features(tea PUBLIC cxx_std_11)
target_link_libraries(tea tea-res wren stb stb_vorbis glfw glad portaudio_static fmt)
if (MSVC)
    target_compile_options(tea PRIVATE /W4 /wd4100 /D _CRT_SECURE_NO_WARNINGS)
else ()
    target_compile_options(tea PRIVATE -Wall -Wextra -pedantic -Wno-error=unused-parameter)
endif ()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    target_link_libraries(tea "-s WASM=1 -s USE_GLFW=3 -s USE_WEBGL2=1")

    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        target_link_libraries(tea "-Oz")
    endif ()
endif ()