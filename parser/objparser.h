#ifndef OBJPARSER_H
#define OBJPARSER_H


// Data structures
struct Vertex {
    float x, y, z;
};

struct Normal {
    float x, y, z;
};

struct Face {
    std::vector<int> vertexIndices;
    std::vector<int> normalIndices;
};

class ObjParser
{
public:
    ObjParser(const std::string fileName);

    Face parseFaceLine(const std::string& line);
    void printObjFile();

private:
    std::string m_fileName;
    std::vector<Vertex> m_Vertices;
    std::vector<Normal> m_Normals;
    std::vector<Face> m_Faces;
};

#endif // OBJPARSER_H
