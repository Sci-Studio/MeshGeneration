#include "renderwidget.h"
#include "renderer.h"

#include <string>
#include <QMatrix4x4>




RenderWidget::RenderWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

void RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();

//    float positions[8] = {
//        -0.5f, -0.5f,
//         0.5f, -0.5f,
//         0.5f,  0.5f,
//        -0.5f,  0.5f
//    };

    float horLineVert[] = {
        -0.5f,  -0.5f, 0.0f,
         0.5f,  -0.5f, 0.0f
    };

//    unsigned int indices[] = {
//        0, 1, 2,
//        2, 3, 0
//    };

    color.resize(4);
    color[0] = 0.1f;
    color[1] = 0.3f;
    color[2] = 0.8f;
    color[3] = 1.0f;

    // va = new VertexArray(*this);
    // vb = new VertexBuffer(*this, positions, 4 * 2 * sizeof(float));
    // layout = new VertexBufferLayout();
    // layout->Push<float>(2);
    // va->AddBuffer(*vb, *layout);
    // ib = new IndexBuffer(*this, indices, 6);

    // horizontal line
    va = new VertexArray(*this);
    vb = new VertexBuffer(*this, horLineVert,  2 * 3 * sizeof(float), GL_ARRAY_BUFFER);
    layout = new VertexBufferLayout();
    layout->Push<float>(3);
    va->AddBuffer(*vb, *layout);

    shader = new Shader(*this, "/home/hisham/dev_latest/MeshGen/basic.vert");
    shader->Bind();
    shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);

    va->UnBind();
    shader->Unbind();
    vb->UnBind();
    // ib->UnBind();
}

void RenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render Rectangle
//    shader->Bind();
//    shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);
//    va->Bind();
//    ib->Bind();

//    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0), *this);

    // Render Line
    shader->Bind();
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
