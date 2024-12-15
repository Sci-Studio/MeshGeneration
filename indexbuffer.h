#pragma once

#include "pch.h"

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
    QOpenGLClass& m_Context;
public:
    IndexBuffer(QOpenGLClass& context, const void* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline unsigned int getCount() const { return m_Count; }
};

