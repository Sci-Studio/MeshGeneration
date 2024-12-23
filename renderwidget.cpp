#include "renderwidget.h"
#include "renderer.h"
#include "shapes/rectangle.h"

#include <string>
#include <QMatrix4x4>




RenderWidget::RenderWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

void RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();

    float positions[8] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    float horLineVert[] = {
        -0.5f,  -0.7f, 0.0f,
         0.5f,  -0.7f, 0.0f
    };

    shape = new Rectangle(*this, positions);
    color.resize(4);
    color[0] = 0.1f;
    color[1] = 0.3f;
    color[2] = 0.8f;
    color[3] = 1.0f;


    // horizontal line
    va = new VertexArray(*this);
    vb = new VertexBuffer(*this, horLineVert,  2 * 3 * sizeof(float));
    layout = new VertexBufferLayout();
    layout->Push<float>(3);
    va->AddBuffer(*vb, *layout);

    shader = new Shader(*this, "/home/hisham/dev_latest/MeshGen/basic.vert");
    shader->Bind();
    shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);


    shader->Unbind();
    shape->UnBind();
    va->UnBind();
    vb->UnBind();
}

void RenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Render Rectangle
    shader->Bind();
    shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);
    shape->render();

    // Render Line
    va->Bind();
    shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);

    GLCall(glDrawArrays(GL_LINES, 0, 2), *this);

}

void RenderWidget::changeColor(std::vector<float> color)
{
    if (color.size() > 4)
    {
        qDebug() << "invalid rgba color float";
    }
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->color[3] = color[3];
    update();
}
