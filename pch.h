#ifndef PCH_H
#define PCH_H

// Define the OpenGL header macro
#define QOPENGL_HEADER <QOpenGLFunctions_4_2_Compatibility>
#include QOPENGL_HEADER

// Define an alias for the OpenGL class
using QOpenGLClass = QOpenGLFunctions_4_2_Compatibility;

#endif // PCH_H
