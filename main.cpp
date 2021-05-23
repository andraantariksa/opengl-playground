#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <shader/shader_vertex_none.h>
#include <shader/shader_fragment_single_color.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "lib/glcpp/src/Program.hpp"
#include "lib/glcpp/src/Misc.hpp"
#include "lib/aml/src/WindowManager.hpp"
#include "lib/aml/src/window/WindowImplSDL.hpp"

int main(int argc, char *args[])
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "OpenSans-Regular.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_GL_LoadLibrary(nullptr);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    auto windows = SBML::WindowManager();
    auto window = windows.createWindow<SBML::WindowImplSDL>("SDL2 Window SBML", 680, 480, 100, 100);
    SDL_GLContext glContext = SDL_GL_CreateContext(static_cast<SDL_Window*>(window->getRawWindow()));
    if (!glContext)
    {
        std::cerr << "Failed to create OpenGL context\n";
        return -1;
    }
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << '\n';
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';
    std::cout << "Version: " << glGetString(GL_VERSION) << '\n';

    int window_width;
    int window_height;
    SDL_GetWindowSize(static_cast<SDL_Window*>(window->getRawWindow()), &window_width, &window_height);
    glViewport(0, 0, window_width, window_height);

    auto vertexShader = GLCPP::Shader(GLCPP::Shader::Type::VertexShader, SHADER_VERTEX_NONE);
    vertexShader.compile();

    auto fragmentShader = GLCPP::Shader(GLCPP::Shader::Type::FragmentShader, SHADER_FRAGMENT_SINGLE_COLOR);
    fragmentShader.compile();

    auto program = GLCPP::Program();
    program.attachShader(vertexShader);
    program.attachShader(fragmentShader);
    program.linkProgram();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,
        -0.3f, -0.3f, 0.1f,
        0.7f, -0.3f, 0.1f,
        0.2f,  0.7f, 0.1f
    };
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    unsigned short polygonModeTypesCycleIndex = 0;
    GLCPP::PolygonModeType polygonModeTypes[3] = { GLCPP::PolygonModeType::Fill, GLCPP::PolygonModeType::Line, GLCPP::PolygonModeType::Point };

    program.useProgram();

    Uint64 timeLatest = SDL_GetPerformanceCounter();

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHTBRACKET:
                    polygonModeTypesCycleIndex = (polygonModeTypesCycleIndex + 1) % 3;
                    GLCPP::polygonMode(GLCPP::PolygonFaceType::FrontAndBack, polygonModeTypes[polygonModeTypesCycleIndex]);
                    break;
                }
                break;
            }
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(static_cast<SDL_Window*>(window->getRawWindow()));

        Uint64 timeBefore = timeLatest;
        timeLatest = SDL_GetTicks();

        float elapsed = (float)(timeLatest - timeBefore) / timeLatest;
    }

//    glDeleteShader(vertex_shader_id);
//    glDeleteShader(fragment_shader_id);

    SDL_Quit();

    return 0;
}