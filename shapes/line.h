#ifndef LINE_H
#define LINE_H

#include "pch.h"

#include "shape.h"

class Line : public Shape
{
public:
    Line(QOpenGLClass& context, const float data[6]);

    void Render() const override;
    void Bind() const override;
    void UnBind() const override;
};

#endif // LINE_H
