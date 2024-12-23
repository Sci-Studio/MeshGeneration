#ifndef SHAPE_H
#define SHAPE_H

#include "pch.h"

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "vertexbufferlayout.h"

class Shape {
public:
    Shape(QOpenGLClass& context) : m_Context(context) {}

    virtual void render() const = 0;
    virtual void Bind() const = 0;
    virtual void UnBind() const = 0;
protected:
    QOpenGLClass& m_Context;
    VertexArray* va;
    VertexBuffer* vb;
    VertexBufferLayout* layout;
};

#endif // SHAPE_H
