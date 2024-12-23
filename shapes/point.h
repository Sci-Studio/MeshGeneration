#ifndef POINT_H
#define POINT_H

#include "pch.h"

#include "shape.h"

class Point : public Shape
{
public:
    Point(QOpenGLClass& context, const float data[9]);

    void Render() const override;
    void Bind() const override;
    void UnBind() const override;
};

#endif // POINT_H
