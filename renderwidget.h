#ifndef TRIANGLESHADER_H
#define TRIANGLESHADER_H

#include "pch.h"
#include "shader.h"
#include "vertexbuffer.h"
#include "vertexarray.h"
#include "vertexbufferlayout.h"
#include "parser/objparser.h"

#include <QMatrix4x4>
#include <QOpenGLWidget>

const unsigned int no_Coordinates_3D = 3;

struct RotateCoordinates {
    float angle;
    unsigned int x, y ,z;
};

struct RGBAlpha {
    float red, green, blue, alpha;
};

class RenderWidget: public QOpenGLWidget, protected QOpenGLClass
{
public:
    RenderWidget(QWidget *parent = nullptr);
    ~RenderWidget();

    void changeColor(RGBAlpha color);
    void rotate(RotateCoordinates rotateCoordinates);
    void importObjFile(std::string fileName);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    Shader* shader;

    RGBAlpha m_Color;
    RotateCoordinates m_RotateCoordinates;

    std::vector<float> m_FloatData;
    unsigned int m_NoOfVertices = 0;

    VertexArray* va;
    VertexBuffer* vb;
    VertexBufferLayout* layout;

    QMatrix4x4 projection;
    QMatrix4x4 modelView;

    ObjParser* parser;

    void updateVertexData();
};
#endif // TRIANGLESHADER_H
