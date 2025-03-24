#include "triangles.h"
#include "renderer.h"

Triangles::Triangles(QOpenGLClass& context, const std::vector<Vertex> data) : Shape(context)
{
    m_NoOfVertices = data.size();

    std::vector<float> floatData;
    floatData.reserve(m_NoOfVertices * 3);

    for (const auto& v : data) {
        floatData.push_back(v.x);
        floatData.push_back(v.y);
        floatData.push_back(v.z);
    }

    m_FloatDataPtr = floatData.data(); // Safe access to underlying array

    va = new VertexArray(m_Context);
    vb = new VertexBuffer(m_Context, m_FloatDataPtr, m_NoOfVertices * no_Coordinates_3D * sizeof(float));
    layout = new VertexBufferLayout();
    layout->Push<float>(no_Coordinates_3D);
    va->AddBuffer(*vb, *layout);
}

Triangles::~Triangles()
{
    delete[] m_FloatDataPtr;
}

void Triangles::Render() const {
    this->Bind();
    GLCall(m_Context.glDrawArrays(GL_TRIANGLES, 0, m_NoOfVertices), m_Context);

}

void Triangles::Bind() const {
    va->Bind();
    vb->Bind();
}

void Triangles::UnBind() const {
    va->UnBind();
    vb->UnBind();
}
