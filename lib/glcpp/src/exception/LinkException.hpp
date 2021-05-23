#ifndef GLCPP_SRC_EXCEPTION_LINKEXCEPTION_HPP
#define GLCPP_SRC_EXCEPTION_LINKEXCEPTION_HPP

#include <stdexcept>

namespace GLCPP
{

    class LinkException : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

}

#endif //GLCPP_SRC_EXCEPTION_LINKEXCEPTION_HPP
