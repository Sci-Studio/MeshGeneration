#pragma once

#include "pch.h"

#include <QDebug>


#define ASSERT(x) if ( !(x)) qDebug() << "OpenGL Error";
#define GLCall(x, context) GLClearError(context);\
    x;\
    ASSERT(GLLogCall(context, #x, __FILE__, __LINE__))


void GLClearError(QOpenGLClass& context);

bool GLLogCall(QOpenGLClass& context, const char* function, const char* file, int line);
