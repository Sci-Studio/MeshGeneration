#include "renderwidget.h"
#include "renderer.h"
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

    parser = new ObjParser("/home/hisham/dev_latest/GeometryMeshing/Data/hing-final.obj");
//    parser = new ObjParser("/home/hisham/dev_latest/GeometryMeshing/Data/rectangle-prism-final.obj");
//    parser = new ObjParser("/home/hisham/dev_latest/Data/stem-final.obj");

    parser->parseObjFile();
    updateVertexData();

    m_Color = { 0.1f, 0.3f, 0.8f, 1.0f };
    m_RotateCoordinates = { 45.0f, 0, 1, 0 };

    shader = new Shader(*this, "./basic.vert");
    shader->Bind();
    shader->SetUniform4f("u_Color", m_Color.red, m_Color.green, m_Color.blue, m_Color.alpha);

    va = new VertexArray(*this);
    vb = new VertexBuffer(*this, m_FloatData.data(), m_NoOfVertices * no_Coordinates_3D * sizeof(float));
    layout = new VertexBufferLayout();
    layout->Push<float>(no_Coordinates_3D);
    va->AddBuffer(*vb, *layout);

    shader->Unbind();
    va->UnBind();
    vb->UnBind();

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
    modelView.rotate(m_RotateCoordinates.angle, m_RotateCoordinates.x, m_RotateCoordinates.y, m_RotateCoordinates.z);
    shader->SetUniformMatrix("mvpMatrix", projection * modelView);

    va->Bind();
    vb->Bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, m_NoOfVertices), *this);

}


void RenderWidget::changeColor(RGBAlpha color)
{
    m_Color = color;
    update();
}

void RenderWidget::rotate(RotateCoordinates rotateCoordinates)
{
    m_RotateCoordinates.angle += rotateCoordinates.angle;
    m_RotateCoordinates.x = rotateCoordinates.x;
    m_RotateCoordinates.y = rotateCoordinates.y;
    m_RotateCoordinates.z = rotateCoordinates.z;
    update();
}

void RenderWidget::importObjFile(std::string fileName)
{
    parser->setFileName(fileName);
    parser->parseObjFile();
    updateVertexData(true);
    update();
}

void RenderWidget::updateVertexData(bool modifyData)
{
    std::vector<Vertex> vertices = parser->getRenderVertices();
    m_NoOfVertices = vertices.size();
    m_FloatData.clear();

    for (const auto& v : vertices) {
        m_FloatData.push_back(v.x);
        m_FloatData.push_back(v.y);
        m_FloatData.push_back(v.z);
    }

    if (modifyData) {
        vb->UpdateVertexData(m_FloatData.data(), m_NoOfVertices * no_Coordinates_3D * sizeof(float));
    }
}

void deprecatedRender()
{
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
