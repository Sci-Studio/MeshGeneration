#include "objparser.h"

#include <sstream>
#include <fstream>
#include <QDebug>

float minX = std::numeric_limits<float>::max();
float maxX = -std::numeric_limits<float>::max();
float minY = std::numeric_limits<float>::max();
float maxY = -std::numeric_limits<float>::max();
float minZ = std::numeric_limits<float>::max();
float maxZ = -std::numeric_limits<float>::max();

ObjParser::ObjParser() {}

ObjParser::ObjParser(const std::string fileName)
    : m_FileName(fileName) {}

void ObjParser::setFileName(std::string fileName)
{
    m_FileName = fileName;
}

void ObjParser::parseObjFile()
{
    std::ifstream objFile(m_FileName);

    if(!objFile.is_open()) {
        qDebug() << "Failed to open the OBJ file!";
        return;
    }

    m_Vertices.clear();
    m_Normals.clear();
    m_Faces.clear();

    m_RenderVertices.clear();
    m_RenderNormals.clear();

    std::string line;
    while(std::getline(objFile, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            Vertex v;
            iss >> v.x >> v.y >> v.z;
            this->m_Vertices.push_back(v);
        } else if (type == "vn") {
            Normal n;
            iss >> n.x >> n.y >> n.z;
            m_Normals.push_back(n);
        } else if (type == "f") {
            Face face = parseFaceLine(line);
            m_Faces.push_back(face);
        }
    }

    objFile.close();

    float scaleFactor = getScaleFactor();
    for (const Face& face : m_Faces) {
        for (int i = 0; i < face.vertexIndices.size(); i++) {
            Vertex v = m_Vertices[face.vertexIndices[i] - 1];
            v.x *= scaleFactor;
            v.y *= scaleFactor;
            v.z *= scaleFactor;
            m_RenderVertices.push_back(v);

            if (!m_Normals.empty()) {
                Normal n = m_Normals[face.normalIndices[i]];
                m_RenderNormals.push_back(n);
            }
        }
    }
}

Face ObjParser::parseFaceLine(const std::string& line)
{
    Face face;
    std::istringstream iss(line);
    std::string token;

    // Skip the "f" keyword
    iss >> token;

    while (iss >> token) {
        std::istringstream tokenStream(token);
        int vertexIndex = -1, normalIndex = -1;
        std::string part;

        // Extract vertex index
        if (std::getline(tokenStream, part, '/')) {
            vertexIndex = std::stoi(part);
        }

        // Skip texture coordinate (if present)
        if (std::getline(tokenStream, part, '/')) {
            // Texture coordinate index (not used in this example)
        }

        // Extract normal index
        if (std::getline(tokenStream, part, '/')) {
            normalIndex = std::stoi(part);
        }

        // Store indices
        if (vertexIndex != -1) {
            face.vertexIndices.push_back(vertexIndex);
        }
        if (normalIndex != -1) {
            face.normalIndices.push_back(normalIndex);
        }
    }

    return face;
}

void ObjParser::printObjFile() {
    qDebug() << "Vertices:";
    for (const auto& v : m_Vertices) {
        qDebug() << "v " << v.x << " " << v.y << " " << v.z;
    }

    qDebug() << "\nNormals:\n";
    for (const auto& n : m_Normals) {
        qDebug() << "vn " << n.x << " " << n.y << " " << n.z;
    }

    qDebug() << "\nFaces:\n";
    for (const auto& f : m_Faces) {
        qDebug() << "f ";
        for (size_t i = 0; i < f.vertexIndices.size(); i++) {
            qDebug() << f.vertexIndices[i] << "//" << f.normalIndices[i] << " ";
        }
    }
}

std::vector<Vertex> ObjParser::getVertices()
{
    return m_Vertices;
}

std::vector<Normal> ObjParser::getNormals()
{
    return m_Normals;
}

std::vector<Face> ObjParser::getFaces()
{
    return m_Faces;
}

std::vector<Vertex> ObjParser::getRenderVertices()
{
    return m_RenderVertices;
}

std::vector<Normal> ObjParser::getRenderNormals()
{
    return m_RenderNormals;
}

float ObjParser::getScaleFactor()
{
    for (const Vertex& v : m_Vertices) {
        minX = std::min(minX, v.x);
        maxX = std::max(maxX, v.x);
        minY = std::min(minY, v.y);
        maxY = std::max(maxY, v.y);
        minZ = std::min(minZ, v.z);
        maxZ = std::max(maxZ, v.z);
    }

    float sizeX = maxX - minX;
    float sizeY = maxY - minY;
    float sizeZ = maxZ - minZ;

    // Find the largest dimension
    float maxSize = std::max({sizeX, sizeY, sizeZ});

    return 2.0f / maxSize;
}
