#include "curve.h"

Curve::Curve(QOpenGLClass& context, const float data[]) : Shape(context)
{
    va = new VertexArray(m_Context);
    vb = new VertexBuffer(m_Context, data,  7 * 3 * sizeof(float));
    layout = new VertexBufferLayout();
    layout->Push<float>(3);
    va->AddBuffer(*vb, *layout);
}

void Curve::Render() const {
    this->Bind();
    GLCall(m_Context.glLineWidth(2.0f), m_Context);
    GLCall(m_Context.glDrawArrays(GL_LINE_STRIP, 0, 7), m_Context);
}

void Curve::Bind() const {
    va->Bind();
    vb->Bind();
}

void Curve::UnBind() const {
    va->UnBind();
    vb->UnBind();
}
