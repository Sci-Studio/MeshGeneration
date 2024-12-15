#ifndef SHADERUTILS_H
#define SHADERUTILS_H


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
    static unsigned int CompileShader(QOpenGLClass& context, unsigned int type, const std::string& source);
    static unsigned int CreateShader(QOpenGLClass& context, const std::string& vertexShader, const std::string& fragmentShader);
    static void GLClearError(QOpenGLClass& context);
    static void GLCheckError(QOpenGLClass& context);
};

#endif // SHADERUTILS_H
