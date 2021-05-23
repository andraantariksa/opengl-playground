#ifndef GLCPP_SRC_PROGRAM_HPP
#define GLCPP_SRC_PROGRAM_HPP

#include <glad/glad.h>

#include "shader/Shader.hpp"
#include "exception/LinkException.hpp"

namespace GLCPP
{

    class Program
    {
    public:
        inline Program():
            id(glCreateProgram())
        {
        }

        inline ~Program() { glDeleteProgram(id); }

        inline void attachShader(Shader shader) const { glAttachShader(id, shader.getID()); }
        inline void attachShader(GLuint shader_id) const { glAttachShader(id, shader_id); }

        inline void linkProgram() const
        {
            linkProgramUnsafe();
            if (!isLinkProgramSuccess())
            {
                char info_log[512];
                throw LinkException(info_log);
            }
        }

        inline int isLinkProgramSuccess() const
        {
            int success;
            glGetShaderiv(id, GL_LINK_STATUS, &success);
            return success;
        }

        inline void getLog(char* info_log, int info_log_len) const
        {
            glGetProgramInfoLog(id, info_log_len, nullptr, info_log);
        }

        inline void linkProgramUnsafe() const { glLinkProgram(id); }

        inline void useProgram() const { glUseProgram(id); }

        inline GLuint getId() const { return id; }

    private:
        GLuint id;
    };

}

#endif //GLCPP_SRC_PROGRAM_HPP
