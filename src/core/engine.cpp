#include "core/engine.h"

#include <glad/glad.h>
#include <SDL.h>
#include "gfx/colour.h"
#include "impl/platformsdl2.h"
#include "impl/renderergl33.h"
#include "gfx/commandbuffer.h"

namespace tea {

Engine::Engine(std::vector<std::string> args) {
    this->args = std::move(args);
    this->scripting = std::make_unique<Scripting>();
}

int Engine::run() {
    scripting->test();

    PlatformSDL2 platform = PlatformSDL2();
    SDL_Window* window = platform.get_raw_window();

#ifdef TEA_DEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    gladLoadGLLoader(SDL_GL_GetProcAddress);
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));

    RendererGL33 renderer = RendererGL33();

    SDL_GL_SetSwapInterval(1);

    bool running = true;
    SDL_Event sdl_event;
    while (running) {
        while (SDL_PollEvent(&sdl_event) != 0) {
            if (sdl_event.type == SDL_QUIT) {
                running = false;
            }
        }

        int w, h;
        SDL_GL_GetDrawableSize(window, &w, &h);

        CommandBuffer buffer;
        buffer.cmd_set_viewport(0, 0, w, h, 0.0, 1.0);
        buffer.cmd_clear_to_colour(ColourRGB::CORNFLOWERBLUE);
        renderer.execute_command_buffer(buffer);

        SDL_GL_SwapWindow(window);
    }


    return 0;
}

}