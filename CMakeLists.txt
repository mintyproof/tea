project(testengine C)

add_subdirectory(deps/sdl)

set(ENGINE_SOURCES
	src/assets.c
	src/main.c
)

add_executable(testengine ${ENGINE_SOURCES})
target_link_libraries(testengine SDL2-static)
