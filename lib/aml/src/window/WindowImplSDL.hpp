#ifndef OPENGL_PLAYGROUND_LIB_AML_SRC_WINDOW_WINDOWIMPLSDL_HPP
#define OPENGL_PLAYGROUND_LIB_AML_SRC_WINDOW_WINDOWIMPLSDL_HPP

#include <SDL2/SDL.h>

#include "../Window.hpp"
#include "../exception/WindowException.hpp"

namespace SBML
{

    class WindowImplSDL : public Window
    {
    public:
        WindowImplSDL(const char* title, int width, int height, int posX = SDL_WINDOWPOS_CENTERED, int posY = SDL_WINDOWPOS_CENTERED):
            window{SDL_CreateWindow(title, posX, posY, width, height, SDL_WINDOW_OPENGL)}
        {
            if (!window)
            {
                throw WindowException("Cannot create SDL_Window");
            }
        }

        void setTitle(const char* title) override
        {
            SDL_SetWindowTitle(window, title);
        }

        const char* getTitle() override
        {
            return SDL_GetWindowTitle(window);
        }

        void* getRawWindow() override
        {
            return window;
        }
    private:
        SDL_Window* window;
    };

}

#endif //OPENGL_PLAYGROUND_LIB_AML_SRC_WINDOW_WINDOWIMPLSDL_HPP
