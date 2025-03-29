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

RenderWidget::~RenderWidget()
{
    delete parser;
}


void RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();

    const std::vector<Vertex> meshPoints = {
        // Front Face
        { -0.5f, -0.5f,  0.5f },
        {  0.5f, -0.5f,  0.5f },
        { -0.5f,  0.5f,  0.5f },

        {  0.5f, -0.5f,  0.5f },
        {  0.5f,  0.5f,  0.5f },
        { -0.5f,  0.5f,  0.5f },

        // Rear Face
        { -0.5f, -0.5f, -0.5f },
        {  0.5f, -0.5f, -0.5f },
        { -0.5f,  0.5f, -0.5f },

        {  0.5f, -0.5f, -0.5f },
        {  0.5f,  0.5f, -0.5f },
        { -0.5f,  0.5f, -0.5f },

        // left side view
        { -0.5f, -0.5f,  0.5f },
        { -0.5f, -0.5f, -0.5f },
        { -0.5f,  0.5f, -0.5f },

        { -0.5f, -0.5f,  0.5f },
        { -0.5f,  0.5f,  0.5f },
        { -0.5f,  0.5f, -0.5f },

        // right side view
        {  0.5f, -0.5f,  0.5f },
        {  0.5f, -0.5f, -0.5f },
        {  0.5f,  0.5f, -0.5f },

        {  0.5f, -0.5f,  0.5f },
        {  0.5f,  0.5f,  0.5f },
        {  0.5f,  0.5f, -0.5f },
    };

    parser = new ObjParser("/home/hisham/dev_latest/GeometryMeshing/Data/hing-final.obj");
//    parser = new ObjParser("/home/hisham/dev_latest/Data/rectangle-prism-final.obj");
//    parser = new ObjParser("/home/hisham/dev_latest/Data/stem-final.obj");

    parser->parseObjFile();

    m_Color = { 0.1f, 0.3f, 0.8f, 1.0f };
    rotateCoordinates = { 45.0f, 0, 1, 0 };
    shapes.resize(1);
    shapes[0] = new Triangles(*this, parser->getRenderVertices());


    shader = new Shader(*this, "./basic.vert");
    shader->Bind();
    shader->SetUniform4f("u_Color", m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);


    shader->Unbind();

    for(unsigned int i = 0; i < shapes.size(); i++) {
        const auto& element = shapes[i];
        element->UnBind();
    }
}

void RenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    // Update the projection matrix
    projection.setToIdentity();
    projection.perspective(45.0f, static_cast<float>(w) / h, 0.1f, 100.0f);
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Bind();
    shader->SetUniform4f("u_Color", m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);

    // Set the model-view matrix
    modelView.setToIdentity();
    modelView.translate(0.0f, 0.0f, -5.0f); // Move the object back
    modelView.rotate(rotateCoordinates.angle, rotateCoordinates.x, rotateCoordinates.y, rotateCoordinates.z);
    shader->SetUniformMatrix("mvpMatrix", projection * modelView);

    for(unsigned int i = 0; i < shapes.size(); i++) {
        const auto& element = shapes[i];
        element->Render();
    }

}


void RenderWidget::changeColor(RGBAlpha color)
{
    m_Color = color;
    update();
}

void RenderWidget::rotate(RotateCoordinates rotateCoordinates)
{
    this->rotateCoordinates.angle += rotateCoordinates.angle;
    this->rotateCoordinates.x = rotateCoordinates.x;
    this->rotateCoordinates.y = rotateCoordinates.y;
    this->rotateCoordinates.z = rotateCoordinates.z;
    update();
}

void RenderWidget::importObjFile(std::string fileName)
{
    parser->setFileName(fileName);
    parser->parseObjFile();
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
