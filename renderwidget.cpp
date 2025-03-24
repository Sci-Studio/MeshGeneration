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
//    parser = new ObjParser();
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

    parser = new ObjParser("/home/hisham/dev_latest/Data/hing-final.obj");
//    parser = new ObjParser("/home/hisham/dev_latest/Data/rectangle-prism-final.obj");
//    parser = new ObjParser("/home/hisham/dev_latest/Data/stem-final.obj");

//    parser = new ObjParser("/home/hisham/freecad_models/example1-BodyFillet002.obj");
//    parser = new ObjParser("/home/hisham/freecad_models/stem-final.obj");
//    parser = new ObjParser("/home/hisham/dev_latest/Data/sphere-final.obj");

    parser->parseObjFile();

    color.resize(4);
    color[0] = 0.1f;
    color[1] = 0.3f;
    color[2] = 0.8f;
    color[3] = 1.0f;

    rotateCoordinates = {45.0f, 0, 1, 0};
    shapes.resize(1);
//    shapes[0] = new Triangles(*this, meshPoints);
    shapes[0] = new Triangles(*this, parser->getRenderVertices());


    shader = new Shader(*this, "/home/hisham/dev_latest/MeshGeneration/basic.vert");
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
    // Update the projection matrix
    projection.setToIdentity();
    projection.perspective(45.0f, static_cast<float>(w) / h, 0.1f, 100.0f);
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Bind();
    shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);

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
//    for(unsigned int i = 0; i < shapes.size(); i++) {
//        const auto& element = shapes[i];
//        element->UnBind();
//    }
//    float newSquare[8] = {
//        -0.7f, -0.3f,
//        -0.5f, -0.3f,
//        -0.5f,  0.3f,
//        -0.7f,  0.3f
//    };
//    shapes[0] = new Rectangle(*this, newSquare);
//    modelView.scale(parser->getScaleFactor());
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
