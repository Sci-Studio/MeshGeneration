#include "renderwidget.h"
#include "renderer.h"
#include "shapes/rectangle.h"
#include "shapes/line.h"
#include "shapes/point.h"
#include "shapes/curve.h"
#include "shapes/triangles.h"
#include "parser/objparser.h"

#include <string>
#include <QMatrix4x4>




RenderWidget::RenderWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

void RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();

    const std::vector<Vertex> meshPoints = {
        {  0.5f,  0.3f, 0.0f },
        {  0.0f,  0.5f, 0.0f },
        {  0.5f,  0.5f, 0.0f },

        { -0.3f, -0.3f, 0.0f },
        {  0.3f, -0.3f, 0.0f },
        {  0.3f,  0.3f, 0.0f },
    };

    color.resize(4);
    color[0] = 0.1f;
    color[1] = 0.3f;
    color[2] = 0.8f;
    color[3] = 1.0f;

    shapes.resize(1);
    shapes[0] = new Triangles(*this, meshPoints);

    shader = new Shader(*this, "/home/hisham/dev_latest/MeshGen/basic.vert");
    shader->Bind();
    shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);

    shader->Unbind();

    for(unsigned int i = 0; i < shapes.size(); i++) {
        const auto& element = shapes[i];
        element->UnBind();
    }
}

void RenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Bind();
    shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);

    for(unsigned int i = 0; i < shapes.size(); i++) {
        const auto& element = shapes[i];
        element->Render();
    }

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

void deprecatedRender()
{
    float positions[8] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    float horLineVert[] = {
        -0.7f,  -0.7f, 0.0f,
         0.7f,  -0.7f, 0.0f
    };

    float vertLineVert[] = {
        -0.7f,  -0.7f, 0.0f,
        -0.7f,   0.7f, 0.0f
    };

    float newSquare[8] = {
        -0.7f, -0.3f,
        -0.5f, -0.3f,
        -0.5f,  0.3f,
        -0.7f,  0.3f
    };

    float points[] = {
        -0.5f,  0.5f, 0.0f,  // Point 1
         0.0f,  0.0f, 0.0f,  // Point 2
         0.5f, -0.5f, 0.0f   // Point 3
    };

    float airfoilCurve[] = {
        -0.9f,  0.1f, 0.0f,
        -0.6f,  0.3f, 0.0f,
        -0.3f,  0.2f, 0.0f,
         0.0f,  0.0f, 0.0f,
         0.3f, -0.1f, 0.0f,
         0.6f, -0.2f, 0.0f,
         0.9f, -0.1f, 0.0f
    };

    //    shapes[0] = new Rectangle(*this, positions);
    //    shapes[1] = new Line(*this, horLineVert);
    //    shapes[2] = new Line(*this, vertLineVert);
    //    shapes[3] = new Rectangle(*this, newSquare);
    //    shapes[0] = new Curve(*this, airfoilCurve);
    //    shapes[1] = new Point(*this, airfoilCurve);
}
