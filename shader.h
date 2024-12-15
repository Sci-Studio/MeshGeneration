#pragma once

#include <string>
#include <unordered_map>
#include <QOpenGLFunctions_4_2_Compatibility>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    QOpenGLFunctions_4_2_Compatibility& m_Context;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(QOpenGLFunctions_4_2_Compatibility& context, const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;


    // Set uniforms
    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);

private:
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int GetUniformLocation(const std::string& name);
};
