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

    void printObjFile();

private:
    std::string m_fileName;
    std::vector<Vertex> m_Vertices;
    std::vector<Normal> m_Normals;
    std::vector<Face> m_Faces;

    Face parseFaceLine(const std::string& line);
};

#endif // OBJPARSER_H
