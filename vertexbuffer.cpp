#include "vertexbuffer.h"
#include "renderer.h"

VertexBuffer::VertexBuffer(QOpenGLClass& context, const void* data, unsigned int size)
    : m_Context(context)
{
    GLCall(m_Context.glGenBuffers(1, &m_RendererID), m_Context);
    GLCall(m_Context.glBindBuffer(GL_ARRAY_BUFFER, m_RendererID), m_Context);
    GLCall(m_Context.glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW), m_Context);
}

VertexBuffer::~VertexBuffer()
{
    GLCall(m_Context.glDeleteBuffers(1, &m_RendererID), m_Context);
}

void VertexBuffer::Bind() const
{
    GLCall(m_Context.glBindBuffer(GL_ARRAY_BUFFER, m_RendererID), m_Context);
}

void VertexBuffer::UnBind() const
{
    GLCall(m_Context.glBindBuffer(GL_ARRAY_BUFFER, 0), m_Context);
}

void VertexBuffer::UpdateVertexData(const void* data, unsigned int size) const
{
    GLCall(m_Context.glBindBuffer(GL_ARRAY_BUFFER, m_RendererID), m_Context);
    GLCall(m_Context.glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW), m_Context);
}
