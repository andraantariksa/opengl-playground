#ifndef OPENGL_PLAYGROUND_LIB_AML_SRC_EXCEPTION_WINDOWEXCEPTION_HPP
#define OPENGL_PLAYGROUND_LIB_AML_SRC_EXCEPTION_WINDOWEXCEPTION_HPP

#include <stdexcept>

namespace SBML
{

    class WindowException : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

}

#endif //OPENGL_PLAYGROUND_LIB_AML_SRC_EXCEPTION_WINDOWEXCEPTION_HPP
