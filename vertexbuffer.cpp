#include "vertexbuffer.h"
#include "renderer.h"

VertexBuffer::VertexBuffer(QOpenGLClass& context, const void* data, unsigned int size, GLenum target)
    : m_Context(context), m_target(target)
{
    GLCall(context.glGenBuffers(1, &m_RendererID), context);
    GLCall(context.glBindBuffer(target, m_RendererID), context);
    GLCall(context.glBufferData(target, size, data, GL_STATIC_DRAW), context);
}

VertexBuffer::~VertexBuffer()
{
    GLCall(m_Context.glDeleteBuffers(1, &m_RendererID), m_Context);
}

void VertexBuffer::Bind() const
{
    GLCall(m_Context.glBindBuffer(m_target, m_RendererID), m_Context);
}

void VertexBuffer::UnBind() const
{
    GLCall(m_Context.glBindBuffer(m_target, 0), m_Context);
}
