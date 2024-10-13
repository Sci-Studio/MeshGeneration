#pragma once

#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class VertexArray
{
private:
    unsigned int m_RendererID;
    QOpenGLFunctions_4_2_Compatibility& m_Context;
public:
    VertexArray(QOpenGLFunctions_4_2_Compatibility& context);
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void UnBind() const;
};
