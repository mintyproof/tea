cmake_minimum_required(VERSION 3.13.0)

project(tea C CXX)

if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
    message(FATAL_ERROR "prevented in-tree build.")
endif ()

set(CMAKE_MODULE_PATH "${tea_SOURCE_DIR}/misc/cmake" ${CMAKE_MODULE_PATH})

if (WIN32)
    message(WARNING "building on windows is not yet properly supported.")
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TEA_DEBUG TRUE)
else()
    set(TEA_DEBUG FALSE)
endif()

set(TEA_VERSION_MAJOR "0")
set(TEA_VERSION_MINOR "1")
set(TEA_VERSION_PATCH "0")
set(TEA_VERSION "${TEA_VERSION_MAJOR}.${TEA_VERSION_MINOR}.${TEA_VERSION_PATCH}")

if (TEA_DEBUG)
    add_library(glad deps/glad/debug/src/glad.c)
    target_include_directories(glad PUBLIC deps/glad/debug/include)
else()
    add_library(glad deps/glad/release/src/glad.c)
    target_include_directories(glad PUBLIC deps/glad/release/include)
endif()

set(WREN_SOURCES
    deps/wren/src/vm/wren_compiler.c
    deps/wren/src/vm/wren_core.c
    deps/wren/src/vm/wren_debug.c
    deps/wren/src/vm/wren_primitive.c
    deps/wren/src/vm/wren_utils.c
    deps/wren/src/vm/wren_value.c
    deps/wren/src/vm/wren_vm.c

    deps/wren/src/optional/wren_opt_meta.c
    deps/wren/src/optional/wren_opt_random.c)

add_library(wren ${WREN_SOURCES})
target_include_directories(wren PRIVATE deps/wren/src/optional deps/wren/src/vm)
target_include_directories(wren BEFORE PUBLIC deps/wren/src/include)  # BEFORE to override system wren.h if existing
target_compile_definitions(wren PRIVATE _CRT_SECURE_NO_WARNINGS) # to prevent flooding console with errors on msvc

find_package(SDL2 REQUIRED)

include(deps/cmrc/CMakeRC.cmake)
cmrc_add_resource_library(tea-res ALIAS tea::res NAMESPACE tea WHENCE misc/res/
    misc/res/script/prelude.wren
    misc/res/shader/opengl/default_fragment.glsl
    misc/res/shader/opengl/default_vertex.glsl)

set(TEA_INCLUDE_DIRS
    include
    ${SDL2_INCLUDE_DIR})

set(TEA_LINK_LIBRARIES
    tea::res
    wren
    glad
    ${SDL2_LIBRARY})

add_executable(tea src/main.cpp)
add_subdirectory(src)

target_include_directories(tea PUBLIC ${TEA_INCLUDE_DIRS})
target_link_libraries(tea ${TEA_LINK_LIBRARIES})

set_target_properties(tea PROPERTIES C_STANDARD 17 CXX_STANDARD 17)
target_compile_features(tea PUBLIC cxx_std_17)

if (TEA_DEBUG)
    target_compile_definitions(tea PUBLIC TEA_DEBUG)
endif ()

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /wd4100 /fp:fast")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ZI")
    set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -Wall -Wextra -Werror \
        -ffast-math -fno-finite-math-only -fno-associative-math")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
        -g3 \
        -Wno-error=unused-parameter -Wno-error=unused-variable -Wno-error=unused-private-field")
        # ^ to make development easier, where some variables may momentarily be unused prior to implementation
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -pedantic-errors")
    endif ()
endif ()