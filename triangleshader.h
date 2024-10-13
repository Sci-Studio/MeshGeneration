#ifndef TRIANGLESHADER_H
#define TRIANGLESHADER_H

#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbufferlayout.h"
#include "shader.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_2_Compatibility>


class TriangleShader: public QOpenGLWidget, protected QOpenGLFunctions_4_2_Compatibility
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
