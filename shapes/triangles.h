#ifndef TRIANGLES_H
#define TRIANGLES_H

#include "pch.h"

#include "shape.h"
#include "indexbuffer.h"
#include "parser/objparser.h"

const unsigned int no_Coordinates_2D = 2;
const unsigned int no_Coordinates_3D = 3;

class Triangles : public Shape
{
public:
    Triangles(QOpenGLClass& context, const std::vector<Vertex> data);
    ~Triangles();

    void Render() const override;
    void Bind() const override;
    void UnBind() const override;

private:
    IndexBuffer* m_IB;
    float* m_FloatDataPtr;
    unsigned int m_NoOfVertices;
};

#endif // TRIANGLES_H
