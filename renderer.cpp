#include "renderer.h"

void GLClearError(QOpenGLClass& context)
{
    while(context.glGetError() != GL_NO_ERROR);
}

bool GLLogCall(QOpenGLClass &context, const char* function, const char* file, int line)
{
    while(GLenum error = context.glGetError())
    {
        qDebug() << "[OpenGL Error] (" << error << "): " << function <<
                    " " << file << ":" <<  line ;
        return false;
    }
    return true;
}
