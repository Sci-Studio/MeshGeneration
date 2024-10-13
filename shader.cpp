#include "shader.h"
#include "renderer.h"

#include <QDebug>
#include <fstream>
#include <sstream>

Shader::Shader(QOpenGLFunctions_4_2_Compatibility& context, const std::string& filepath)
    : m_Context(context), m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);

    m_RendererID = CreateShader(source.VertexSource , source.FragmentSource);
}

Shader::~Shader()
{
    GLCall(m_Context.glDeleteProgram(m_RendererID), m_Context);
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = m_Context.QOpenGLFunctions_4_2_Compatibility::glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(m_Context.glAttachShader(program, vs), m_Context);
    GLCall(m_Context.glAttachShader(program, fs), m_Context);
    GLCall(m_Context.glLinkProgram(program), m_Context);
    GLCall(m_Context.glValidateProgram(program), m_Context);

    GLCall(m_Context.glDeleteShader(vs), m_Context);
    GLCall(m_Context.glDeleteShader(fs), m_Context);

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = m_Context.glCreateShader(type), m_Context);
    const char* src = source.c_str();

    GLCall(m_Context.glShaderSource(id, 1, &src, nullptr), m_Context);
    GLCall(m_Context.glCompileShader(id), m_Context);

    int result;
    GLCall(m_Context.glGetShaderiv(id, GL_COMPILE_STATUS, &result), m_Context);
    if (result == GL_FALSE)
    {
       int length;
       GLCall(m_Context.glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length), m_Context);
       char* message = (char*)alloca(length * sizeof(char));
       GLCall(m_Context.glGetShaderInfoLog(id, length, &length, message), m_Context);
       qDebug() << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
       qDebug() << message;

       GLCall(m_Context.glDeleteShader(id), m_Context);
       return 0;
    }


    return id;
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
             else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

void Shader::Bind() const
{
    GLCall(m_Context.glUseProgram(m_RendererID), m_Context);
}

void Shader::Unbind() const
{
    GLCall(m_Context.glUseProgram(0), m_Context);
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = m_Context.glGetUniformLocation(m_RendererID, name.c_str()), m_Context);
    if (location == -1)
        qDebug() << "Warning uniform '" << name.c_str() << "' doesn't exist!";
    m_UniformLocationCache[name] = location;
    return location;
}

void Shader::SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3)
{
    GLCall(m_Context.glUniform4f(GetUniformLocation(name), f0, f1, f2, f3), m_Context);
}
