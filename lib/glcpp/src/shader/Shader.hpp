#ifndef GLCPP_SRC_SHADER_SHADER_HPP
#define GLCPP_SRC_SHADER_SHADER_HPP

#include <glad/glad.h>
#include "../exception/CompileException.hpp"

namespace GLCPP
{

    class Shader
    {
    public:
        enum class Type : GLenum
        {
            VertexShader = GL_VERTEX_SHADER,
            FragmentShader = GL_FRAGMENT_SHADER
        };

        inline Shader(Type type, const char* code)
        {
            id = glCreateShader(static_cast<GLenum>(type));
            glShaderSource(id, 1, &code, nullptr);
        }

        inline ~Shader() { glDeleteShader(id); }

        inline void compile() const
        {
            compileUnsafe();
            if (!isCompileSuccess())
            {
                char info_log[512];
                getLog(info_log, 512);
                throw CompileException(info_log);
            }
        }

        inline void compileUnsafe() const
        {
            glCompileShader(id);
        }

        [[nodiscard]]
        inline int isCompileSuccess() const
        {
            int success;
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            return success;
        }

        inline void getLog(char* info_log, int info_log_len) const
        {
            glGetShaderInfoLog(id, info_log_len, nullptr, info_log);
        }

        [[nodiscard]]
        const GLuint& getID() const { return id; }
    private:
        GLuint id;
    };

}

#endif //GLCPP_SRC_SHADER_SHADER_HPP
