#include "shaderutils.h"
#include <fstream>
#include <sstream>
#include <iostream>

ShaderUtils::ShaderUtils()
{

}

unsigned int ShaderUtils::CompileShader(QOpenGLFunctions_4_2_Compatibility& context, unsigned int type, const std::string& source)
{
    unsigned int id = context.glCreateShader(type);
    const char* src = source.c_str();
    context.glShaderSource(id, 1, &src, nullptr);
    context.glCompileShader(id);

    int result;
    context.glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
       int length;
       context.glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
       char* message = (char*)alloca(length * sizeof(char));
       context.glGetShaderInfoLog(id, length, &length, message);
       std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
       std::cout << message << std::endl;

       context.glDeleteShader(id);
       return 0;
    }


    return id;
}

unsigned int ShaderUtils::CreateShader(QOpenGLFunctions_4_2_Compatibility& context, const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = context.QOpenGLFunctions_4_2_Compatibility::glCreateProgram();
    unsigned int vs = CompileShader(context, GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(context, GL_FRAGMENT_SHADER, fragmentShader);

    context.glAttachShader(program, vs);
    context.glAttachShader(program, fs);
    context.glLinkProgram(program);
    context.glValidateProgram(program);

    context.glDeleteShader(vs);
    context.glDeleteShader(fs);

    return program;
}

ShaderProgramSource ShaderUtils::ParseShader(const std::string &filepath)
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

void ShaderUtils::GLClearError(QOpenGLFunctions_4_2_Compatibility& context)
{
    while(context.glGetError() != GL_NO_ERROR);
}


void ShaderUtils::GLCheckError(QOpenGLFunctions_4_2_Compatibility &context)
{
    while(GLenum error = context.glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}
