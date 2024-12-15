#pragma once

#include "pch.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class VertexArray
{
private:
    unsigned int m_RendererID;
    QOpenGLClass& m_Context;
public:
    VertexArray(QOpenGLClass& context);
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void UnBind() const;
};
