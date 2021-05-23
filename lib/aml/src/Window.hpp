#ifndef AML_SRC_WINDOW_HPP
#define AML_SRC_WINDOW_HPP

namespace SBML
{

    class Window
    {
    public:
        virtual void setTitle(const char* title) = 0;
        virtual const char* getTitle() = 0;
        virtual void* getRawWindow() = 0;
    };

}

#endif //AML_SRC_WINDOW_HPP
