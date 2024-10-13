#include "triangleshader.h"

#include <iostream>
#include <string>
#include <QMatrix4x4>

#include "renderer.h"


TriangleShader::TriangleShader(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

void TriangleShader::initializeGL()
{
    initializeOpenGLFunctions();

    setupVertexData();

    ShaderProgramSource source = ShaderUtils::ParseShader("/home/hisham/dev_latest/MeshGen/basic.vert");

    shader = ShaderUtils::CreateShader(*this, source.VertexSource , source.FragmentSource);
    glUseProgram(shader);

    color.resize(4);
    color[0] = 0.1f;
    color[1] = 0.3f;
    color[2] = 0.8f;
    color[3] = 1.0f;

//    glDeleteProgram(shader);
}

void TriangleShader::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void TriangleShader::paintGL()
{
    //ShaderUtils::GLClearError(*this);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int location = glGetUniformLocation(shader, "u_Color");
    Q_ASSERT(location != -1);
    glUniform4f(location, color[0], color[1], color[2], color[3]);

    glBindVertexArray(vao);
    ib->Bind();

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0), *this);

    glBindVertexArray(0);
}

void TriangleShader::setupVertexData()
{
    float positions[8] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Generate and bind VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vb = new VertexBuffer(*this, positions, 4 * 2 * sizeof(float));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    ib = new IndexBuffer(*this, indices, 6);

    // Unbind VAO
    glBindVertexArray(0);
}

void TriangleShader::changeColor(std::vector<float> color)
{
    if (color.size() > 4)
    {
        std::cout << "invalid rgba color float" << std::endl;
    }
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->color[3] = color[3];
    update();
}
