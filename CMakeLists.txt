cmake_minimum_required(VERSION 3.0)

project(tea C CXX)

set(TEA_VERSION_MAJOR "0")
set(TEA_VERSION_MINOR "1")
set(TEA_VERSION_PATCH "0")
set(TEA_VERSION "${TEA_VERSION_MAJOR}.${TEA_VERSION_MINOR}.${TEA_VERSION_PATCH}")

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
target_compile_definitions(wren PRIVATE _CRT_SECURE_NO_WARNINGS) # To prevent spewing errors on MSVC

set(ENGINE_SOURCES
    src/engine.cpp
    src/main.cpp
    src/scripting/scripting.cpp)

add_executable(tea ${ENGINE_SOURCES})
target_include_directories(tea PUBLIC include)
set_target_properties(tea PROPERTIES C_STANDARD 17 CXX_STANDARD 17)
target_compile_features(tea PUBLIC cxx_std_17)
target_link_libraries(tea wren)
if (MSVC)
    target_compile_options(tea PRIVATE /W4 /wd4100 /D _CRT_SECURE_NO_WARNINGS)
else ()
    target_compile_options(tea PRIVATE -Wall -Wextra -pedantic -Wno-error=unused-parameter)
endif ()