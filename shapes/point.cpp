#include "point.h"

Point::Point(QOpenGLClass& context, const float data[]) : Shape(context)
{
    va = new VertexArray(m_Context);
    vb = new VertexBuffer(m_Context, data,  7 * 3 * sizeof(float));
    layout = new VertexBufferLayout();
    layout->Push<float>(3);
    va->AddBuffer(*vb, *layout);
}

void Point::Render() const {
    this->Bind();
    GLCall(m_Context.glDrawArrays(GL_POINTS, 0, 7), m_Context);
    GLCall(m_Context.glPointSize(10.0f), m_Context);
}

void Point::Bind() const {
    va->Bind();
    vb->Bind();
}

void Point::UnBind() const {
    va->UnBind();
    vb->UnBind();
}
