#ifndef OPENGL_PLAYGROUND_LIB_AML_SRC_WINDOWMANAGER_HPP
#define OPENGL_PLAYGROUND_LIB_AML_SRC_WINDOWMANAGER_HPP

#include <vector>
#include <memory>

#include "Window.hpp"
#include "Util.hpp"

namespace SBML
{

    class WindowManager
    {
    public:
        WindowManager() = default;

        template <Derived<Window> T>
        std::shared_ptr<Window> createWindow(const char* title, int width, int height, int posX, int posY)
        {
            auto window = std::make_shared<T>(title, width, height, posX, posY);
            windows.push_back(window);
            return window;
        }

        std::shared_ptr<Window>& operator[](const unsigned int& index)
        {
            return windows[index];
        }

    private:
        std::vector<std::shared_ptr<Window>> windows;
    };

}

#endif //OPENGL_PLAYGROUND_LIB_AML_SRC_WINDOWMANAGER_HPP
