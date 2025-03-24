#ifndef TRIANGLESHADER_H
#define TRIANGLESHADER_H

#include "pch.h"
#include "shader.h"
#include "shapes/shape.h"

#include <QMatrix4x4>
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

    QMatrix4x4 projection;
    QMatrix4x4 modelView;
};
#endif // TRIANGLESHADER_H
