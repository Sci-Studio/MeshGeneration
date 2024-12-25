#include "rectangle.h"
#include "renderer.h"

Rectangle::Rectangle(QOpenGLClass& context, const float data[8]) : Shape(context)
{
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    va = new VertexArray(m_Context);
    vb = new VertexBuffer(m_Context, data, 4 * 2 * sizeof(float));
    layout = new VertexBufferLayout();
    layout->Push<float>(2);
    va->AddBuffer(*vb, *layout);
    ib = new IndexBuffer(m_Context, indices, 6);
}

void Rectangle::Render() const {
    this->Bind();
    GLCall(m_Context.glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0), m_Context);
}

void Rectangle::Bind() const {
    va->Bind();
    vb->Bind();
    ib->Bind();
}

void Rectangle::UnBind() const {
    va->UnBind();
    vb->UnBind();
    ib->UnBind();
}
