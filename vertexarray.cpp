#include "vertexarray.h"
#include "renderer.h"

VertexArray::VertexArray(QOpenGLClass& context)
    : m_Context(context)
{
    GLCall(m_Context.glGenVertexArrays(1, &m_RendererID), m_Context);
    GLCall(m_Context.glBindVertexArray(m_RendererID), m_Context);
}

VertexArray::~VertexArray()
{
   GLCall(m_Context.glDeleteVertexArrays(1, &m_RendererID), m_Context);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(m_Context.glEnableVertexAttribArray(i), m_Context);
        GLCall(m_Context.glVertexAttribPointer(i, element.count, element.type,
                                               element.normalized, layout.GetStride(), (const void*) offset), m_Context);
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

void VertexArray::Bind() const
{
    GLCall(m_Context.glBindVertexArray(m_RendererID), m_Context);
}

void VertexArray::UnBind() const
{
    GLCall(m_Context.glBindVertexArray(0), m_Context);
}
