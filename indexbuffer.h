#pragma once

#include <QOpenGLFunctions_4_2_Compatibility>

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
    QOpenGLFunctions_4_2_Compatibility& m_Context;
public:
    IndexBuffer(QOpenGLFunctions_4_2_Compatibility& context, const void* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline unsigned int getCount() const { return m_Count; }
};

