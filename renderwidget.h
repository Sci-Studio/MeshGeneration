#ifndef TRIANGLESHADER_H
#define TRIANGLESHADER_H

#include "pch.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbufferlayout.h"
#include "shader.h"
#include "shapes/shape.h"

#include <QOpenGLWidget>

class RenderWidget: public QOpenGLWidget, protected QOpenGLClass
{
public:
    RenderWidget(QWidget *parent = nullptr);
    void changeColor(std::vector<float> color);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    Shader* shader;

    std::vector<Shape*> shapes;
    std::vector<float> color;
};
#endif // TRIANGLESHADER_H
