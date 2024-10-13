#ifndef RECTANGLEMESH_H
#define RECTANGLEMESH_H

#include <vector>
#include <string>

struct Vertex {
    float x, y;
    Vertex(float _x, float _y);
};

class RectangleMesh
{
public:
    RectangleMesh(float width, float height);
    void printMesh() const;
    void exportToOBJ(const std::string& fileName);

private:
    std::vector<Vertex> vertices;
};

#endif // RECTANGLEMESH_H
