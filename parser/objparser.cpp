#include "objparser.h"

#include <sstream>
#include <iostream>
#include <fstream>


ObjParser::ObjParser(const std::string fileName)
    : m_fileName(fileName)
{
    std::ifstream objFile(fileName);

    if(!objFile.is_open()) {
        std::cerr << "Failed to open the OBJ file!" << std::endl;
        return;
    }

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
    std::cout << "Vertices:\n";
    for (const auto& v : m_Vertices) {
        std::cout << "v " << v.x << " " << v.y << " " << v.z << "\n";
    }

    std::cout << "\nNormals:\n";
    for (const auto& n : m_Normals) {
        std::cout << "vn " << n.x << " " << n.y << " " << n.z << "\n";
    }

    std::cout << "\nFaces:\n";
    for (const auto& f : m_Faces) {
        std::cout << "f ";
        for (size_t i = 0; i < f.vertexIndices.size(); i++) {
            std::cout << f.vertexIndices[i] << "//" << f.normalIndices[i] << " ";
        }
        std::cout << "\n";
    }
}
