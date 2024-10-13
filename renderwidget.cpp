#include "renderwidget.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <iostream>

RenderWidget::RenderWidget(QWidget *parent) :
     QOpenGLWidget(parent), width(1), height(1), depth(1), isCube(true)
{


}

unsigned int RenderWidget::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // TODO: Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
       int length;
       glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
       char* message = (char*)alloca(length * sizeof(char));
       glGetShaderInfoLog(id, length, &length, message);
       std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
       std::cout << message << std::endl;

       glDeleteShader(id);
       return 0;
    }


    return id;
}

unsigned int RenderWidget::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
     unsigned int program = glCreateProgram();
     unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
     unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

     glAttachShader(program, vs);
     glAttachShader(program, fs);
     glLinkProgram(program);
     glValidateProgram(program);

     glDeleteShader(vs);
     glDeleteShader(fs);

     return program;
}

void RenderWidget::createData()
{
    initData();
}

void RenderWidget::setDimensions(float w, float h, float d)
{
    width = w;
    height = h;
    depth = d;
    update(); // Trigger a repaint
}

void RenderWidget::setShape(bool cube)
{
    isCube = cube;
    update(); // Trigger a repaint
}

void RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void RenderWidget::initData()
{
    // Specify the data of the triangle vertices
    float positions[6] = {
       -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f, -0.5f
    };
    // create apointer
    unsigned int buffer;
    // Generate a buffer and pass the pointer that will be used
    glGenBuffers(1, &buffer);
    // Bind the generated buffer to an id
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // Define the size of the buffer, pass the data and its usage
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) in vec4 position;"
            "\n"
            "void main()\n"
            "{\n"
            " gl_Position = position;\n"
            "}\n";
    std::string fragmentShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) out vec4 color;"
            "\n"
            "void main()\n"
            "{\n"
            " color = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "}\n";
    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);
}
void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glBegin(GL_TRIANGLES);
//    glVertex2f(-0.5f, -0.5f);
//    glVertex2f( 0.0f,  0.5f);
//    glVertex2f( 0.5f, -0.5f);

    glEnd();

    glGetString(GL_VERSION);

    glFlush();
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(75.0, float(width) / height, 1.0, 100.0);

//    // Set the camera
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(0.0, 0.0, 5.0,  // Camera position (x, y, z)
//              0.0, 0.0, 0.0,  // Look at this point (center of the scene)
//              0.0, 1.0, 0.0); // Up direction

//    // Move and rotate the object
//    glTranslatef(0.0f, 0.0f, -6.0f);
//    glRotatef(30, 1.0, 0.0, 0.0);  // Rotate around X-axis
//    glRotatef(45, 0.0, 1.0, 0.0);  // Rotate around Y-axis

//    glEnable(GL_DEPTH_TEST);

//    // Draw cube or recatangular prism
//    if (isCube) {
//        // Cube: All sides equal
//        glScalef(1.0f, 1.0f, 1.0f);
//    } else {
//        // Rectangular prism: Different dimensions
//        glScalef(width, height, depth);
//    }

//    // Draw a simple cube or rectangular prism
//    glBegin(GL_QUADS);
//    // Front face
//    glVertex3f(-1.0f, -1.0f,  1.0f);
//    glVertex3f( 1.0f, -1.0f,  1.0f);
//    glVertex3f( 1.0f,  1.0f,  1.0f);
//    glVertex3f(-1.0f,  1.0f,  1.0f);

//    // Back face
//    glVertex3f(-1.0f, -1.0f, -1.0f);
//    glVertex3f( 1.0f, -1.0f, -1.0f);
//    glVertex3f( 1.0f,  1.0f, -1.0f);
//    glVertex3f(-1.0f,  1.0f, -1.0f);

    // Other faces...

}
