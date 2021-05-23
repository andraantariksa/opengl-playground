#ifndef GLCPP_SRC_EXCEPTION_COMPILEEXCEPTION_HPP
#define GLCPP_SRC_EXCEPTION_COMPILEEXCEPTION_HPP

#include <stdexcept>

namespace GLCPP
{

    class CompileException : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

}

#endif //GLCPP_SRC_EXCEPTION_COMPILEEXCEPTION_HPP
