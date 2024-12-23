#include "line.h"
#include "renderer.h"

Line::Line(QOpenGLClass& context, const float data[6]) : Shape(context)
{
    va = new VertexArray(m_Context);
    vb = new VertexBuffer(m_Context, data,  2 * 3 * sizeof(float));
    layout = new VertexBufferLayout();
    layout->Push<float>(3);
    va->AddBuffer(*vb, *layout);
}

void Line::Render() const {
    this->Bind();
    GLCall(m_Context.glDrawArrays(GL_LINES, 0, 2), m_Context);
}

void Line::Bind() const {
    va->Bind();
    vb->Bind();
}

void Line::UnBind() const {
    va->UnBind();
    vb->UnBind();
}
