#pragma once

#include <QOpenGLFunctions_4_2_Compatibility>

class VertexBuffer
{
private:
    unsigned int m_RendererID;
    QOpenGLFunctions_4_2_Compatibility& m_Context;
public:
    VertexBuffer(QOpenGLFunctions_4_2_Compatibility& context, const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};

