#ifndef CURVE_H
#define CURVE_H

#include "pch.h"

#include "shape.h"

class Curve : public Shape
{
public:
    Curve(QOpenGLClass& context, const float data[]);

    void Render() const override;
    void Bind() const override;
    void UnBind() const override;
};

#endif // CURVE_H
