#ifndef TRIANGLESHADER_H
#define TRIANGLESHADER_H

#include "pch.h"
#include "shader.h"
#include "shapes/shape.h"
#include "parser/objparser.h"

#include <QMatrix4x4>
#include <QOpenGLWidget>

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

    std::vector<Shape*> shapes;
    RGBAlpha m_Color;
    std::vector<float> color;
    RotateCoordinates rotateCoordinates;

    QMatrix4x4 projection;
    QMatrix4x4 modelView;

    ObjParser* parser;
};
#endif // TRIANGLESHADER_H
