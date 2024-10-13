#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class RenderWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
        Q_OBJECT
public:
    explicit RenderWidget(QWidget *parent = nullptr);

    // Function to se the dimensions for the shape
    void setDimensions(float width, float height, float depth);
    void setShape(bool isCube); // true for cube, false for rectangular prism
    void createData();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initData();
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string& source);

private:
    float width, height, depth;
    bool isCube;
};

#endif // RENDERWIDGET_H
