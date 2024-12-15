#ifndef TRIANGLESHADER_H
#define TRIANGLESHADER_H

#include "pch.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbufferlayout.h"
#include "shader.h"

#include <QOpenGLWidget>

class TriangleShader: public QOpenGLWidget, protected QOpenGLClass
{
public:
    TriangleShader(QWidget *parent = nullptr);
    void changeColor(std::vector<float> color);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    VertexArray* va;
    VertexBuffer* vb;
    IndexBuffer* ib;
    VertexBufferLayout* layout;
    Shader* shader;

    std::vector<float> color;
};
#endif // TRIANGLESHADER_H
