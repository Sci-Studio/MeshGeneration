#include "triangleshader.h"
#include "renderer.h"
#include <iostream>
#include <string>
#include <QMatrix4x4>

TriangleShader::TriangleShader(QWidget *parent) :
    QOpenGLWidget(parent),
    positions(new std::vector<float>( {-0.5f, -0.5f,
                                        0.5f, -0.5f,
                                        0.5f,  0.5f,
                                       -0.5f,  0.5f   // Bottom-left
                                     }))
{

}

void TriangleShader::initializeGL()
{
    initializeOpenGLFunctions();

    setupVertexData();
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

//    // Specify the data of the triangle vertices




//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);

//    // Generate a buffer and pass the pointer that will be used
//    glGenBuffers(1, &vbo);
//    // Bind the generated buffer to an id
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    // Define the size of the buffer, pass the data and its usage
//    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions->data(), GL_STATIC_DRAW);

//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    // unsigned int ibo;
//    glGenBuffers(1, &ibo);
//    // Bind the generated buffer to an id
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//    // Define the size of the buffer, pass the data and its usage
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 *sizeof(unsigned int), indices, GL_STATIC_DRAW);
    // Unbind VAO
    glBindVertexArray(0);

    ShaderProgramSource source = ShaderUtils::ParseShader("/home/hisham/dev_latest/MeshGen/basic.vert");

    shader = ShaderUtils::CreateShader(*this, source.VertexSource , source.FragmentSource);
    glUseProgram(shader);

    color.resize(4);
    color[0] = 0.1f;
    color[1] = 0.3f;
    color[2] = 0.8f;
    color[3] = 1.0f;

//    glDeleteBuffers(1, &buffer);
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


    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0), *this);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    ShaderUtils::GLCheckError(*this);

    glBindVertexArray(0);
}

void TriangleShader::setupVertexData()
{
    // Generate and bind VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Generate VBO and bind it
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, positions->size() * sizeof(float), positions->data(), GL_STATIC_DRAW);

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Generate and bind EBO (element buffer)
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
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

void TriangleShader::changeDimiensions(std::vector<unsigned int> dim)
{
//    QMatrix4x4 projection;

//    float left = -(dim[0]/2.0);
//    float right = dim[0]/2.0;
//    float bottom = -(dim[1]/2.0);
//    float top = dim[1]/2.0;

//    projection.ortho(left, right, bottom, top, -1.0f, 1.0f);

//    QVector3D vertices[] = {
//        QVector3D(-1.0f, -1.0f, 0.0f),  // Bottom-left
//        QVector3D(1.0f, -1.0f, 0.0f),   // Bottom-right
//        QVector3D(1.0f, 1.0f, 0.0f),    // Top-right
//        QVector3D(-1.0f, 1.0f, 0.0f)    // Top-left
//    };

//    QVector3D transformedVertices[4];

//    for (int i = 0; i < 4; ++i) {
//        transformedVertices[i] = projection * vertices[i];
//    }

//     positions->assign({
//        transformedVertices[0][0], transformedVertices[0][1],
//        transformedVertices[1][0], transformedVertices[1][1],
//        transformedVertices[2][0], transformedVertices[2][1],
//        transformedVertices[3][0], transformedVertices[3][1]
//     });

     positions->assign({
        -1.0f, -1.0f,
         0.7f, -0.5f,
         0.7f,  0.5f,
        -0.7f,  0.5f
     });
     std::vector<float> newData = {
         -1.0f, -1.0f,
          0.7f, -0.5f,
          0.7f,  0.5f
     };

    ShaderUtils::GLClearError(*this);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(float), newData.data());
    update();
    ShaderUtils::GLCheckError(*this);



}
