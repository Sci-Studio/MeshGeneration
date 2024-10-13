#ifndef SHADERUTILS_H
#define SHADERUTILS_H

#include <QOpenGLFunctions_4_2_Compatibility>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class ShaderUtils
{
public:
    ShaderUtils();
    static ShaderProgramSource ParseShader(const std::string& filepath);
    static unsigned int CompileShader(QOpenGLFunctions_4_2_Compatibility& context, unsigned int type, const std::string& source);
    static unsigned int CreateShader(QOpenGLFunctions_4_2_Compatibility& context, const std::string& vertexShader, const std::string& fragmentShader);
    static void GLClearError(QOpenGLFunctions_4_2_Compatibility& context);
    static void GLCheckError(QOpenGLFunctions_4_2_Compatibility& context);
};

#endif // SHADERUTILS_H
