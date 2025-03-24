#pragma once

#include "pch.h"

#include <string>
#include <unordered_map>
#include <QMatrix4x4>


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
    QOpenGLClass& m_Context;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(QOpenGLClass& context, const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;


    // Set uniforms
    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
    void SetUniformMatrix(const std::string& name, QMatrix4x4 viewMatrix);

private:
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int GetUniformLocation(const std::string& name);
};
