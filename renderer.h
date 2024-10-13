#pragma once

#include <QDebug>
#include <QOpenGLFunctions_4_2_Compatibility>

#define ASSERT(x) if ( !(x)) qDebug() << "OpenGL Error";
#define GLCall(x, context) GLClearError(context);\
    x;\
    ASSERT(GLLogCall(context, #x, __FILE__, __LINE__))


void GLClearError(QOpenGLFunctions_4_2_Compatibility& context);

bool GLLogCall(QOpenGLFunctions_4_2_Compatibility& context, const char* function, const char* file, int line);
