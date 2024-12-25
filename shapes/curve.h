#ifndef CURVE_H
#define CURVE_H

#include "pch.h"

#include "shape.h"

class Curve : public Shape
{
public:
    Curve(QOpenGLClass& context, const float data[], unsigned int size);

    void Render() const override;
    void Bind() const override;
    void UnBind() const override;
private:
    unsigned int m_Size;
};

#endif // CURVE_H
