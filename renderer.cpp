#include "renderer.h"

void GLClearError(QOpenGLFunctions_4_2_Compatibility& context)
{
    while(context.glGetError() != GL_NO_ERROR);
}

bool GLLogCall(QOpenGLFunctions_4_2_Compatibility &context, const char* function, const char* file, int line)
{
    while(GLenum error = context.glGetError())
    {
        qDebug() << "[OpenGL Error] (" << error << "): " << function <<
                    " " << file << ":" <<  line ;
        return false;
    }
    return true;
}
