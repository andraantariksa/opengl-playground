#ifndef GLCPP_SRC_MISC_HPP
#define GLCPP_SRC_MISC_HPP

#include <glad/glad.h>
namespace GLCPP
{

    enum class PolygonModeType : GLenum
    {
        Fill = GL_FILL,
        Line = GL_LINE,
        Point = GL_POINT
    };

    enum class PolygonFaceType : GLenum
    {
        FrontAndBack = GL_FRONT_AND_BACK,
        Front = GL_FRONT,
        Back = GL_BACK
    };

    inline void polygonMode(PolygonFaceType faceType = PolygonFaceType::FrontAndBack, PolygonModeType modeType = PolygonModeType::Fill)
    {
        glPolygonMode(static_cast<GLenum>(faceType), static_cast<GLenum>(modeType));
    }

}

#endif //GLCPP_SRC_MISC_HPP
