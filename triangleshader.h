#ifndef TRIANGLESHADER_H
#define TRIANGLESHADER_H

#include "shaderutils.h"
#include "rectanglemesh.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_2_Compatibility>


class TriangleShader: public QOpenGLWidget, protected QOpenGLFunctions_4_2_Compatibility
{
public:
    TriangleShader(QWidget *parent = nullptr);
    void changeColor(std::vector<float> color);
    void changeDimiensions(std::vector<unsigned int> dim);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void setupVertexData();

    std::vector<float> *positions;
    std::vector<float> color;
    std::vector<unsigned int> indicies;
    GLuint vbo, vao, ibo;
    unsigned int shader;

};
#endif // TRIANGLESHADER_H
