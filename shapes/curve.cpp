#include "curve.h"

Curve::Curve(QOpenGLClass& context, const float data[], unsigned int size) : Shape(context), m_Size(size)
{
    va = new VertexArray(m_Context);
    vb = new VertexBuffer(m_Context, data,  m_Size * 3 * sizeof(float));
    layout = new VertexBufferLayout();
    layout->Push<float>(3);
    va->AddBuffer(*vb, *layout);
}

void Curve::Render() const {
    this->Bind();
    GLCall(m_Context.glLineWidth(2.0f), m_Context);
    GLCall(m_Context.glDrawArrays(GL_LINE_STRIP, 0, m_Size), m_Context);
}

void Curve::Bind() const {
    va->Bind();
    vb->Bind();
}

void Curve::UnBind() const {
    va->UnBind();
    vb->UnBind();
}
