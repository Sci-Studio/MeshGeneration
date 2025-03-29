#pragma once

#include "pch.h"

class VertexBuffer
{
private:
    unsigned int m_RendererID;
    QOpenGLClass& m_Context;
public:
    VertexBuffer(QOpenGLClass& context, const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
    void UpdateVertexData(const void* data, unsigned int size) const;
};

