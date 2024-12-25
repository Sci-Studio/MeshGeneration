#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "pch.h"

#include "shape.h"
#include "indexbuffer.h"

class Rectangle : public Shape
{
public:
    Rectangle(QOpenGLClass& context, const float data[8]);

    void Render() const override;
    void Bind() const override;
    void UnBind() const override;

private:
    IndexBuffer* ib;
};

#endif // RECTANGLE_H
