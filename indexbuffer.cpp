#include "indexbuffer.h"
#include "renderer.h"

IndexBuffer::IndexBuffer(QOpenGLFunctions_4_2_Compatibility& context, const void* data, unsigned int count)
    : m_Context(context), m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));


    GLCall(context.glGenBuffers(1, &m_RendererID), context);
    GLCall(context.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID), context);
    GLCall(context.glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW), context);
}

IndexBuffer::~IndexBuffer()
{
    GLCall(m_Context.glDeleteBuffers(1, &m_RendererID), m_Context);
}

void IndexBuffer::Bind() const
{
    GLCall(m_Context.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID), m_Context);
}

void IndexBuffer::UnBind() const
{
    GLCall(m_Context.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0), m_Context);
}
