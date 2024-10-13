#include <fstream>
#include <iostream>
#include "rectanglemesh.h"

// Constructor for Vertex struct
Vertex::Vertex(float _x, float _y) : x(_x), y(_y) {}

// Constructor for RectangleMesh class
RectangleMesh::RectangleMesh(float width, float height) {
    // Define the vertices of the rectangle
    vertices.push_back(Vertex(0.0f, 0.0f));      // Bottom-left
    vertices.push_back(Vertex(width, 0.0f));     // Bottom-right
    vertices.push_back(Vertex(width, height));   // Top-right
    vertices.push_back(Vertex(0.0f, height));    // Top-left
}

// Function to print the mesh vertices
void RectangleMesh::printMesh() const {
    std::cout << "Rectangle Mesh Vertices: " << std::endl;
    for (const auto& vertex : vertices) {
        std::cout << "(" << vertex.x << ", " << vertex.y << ")" << std::endl;
    }
}

void RectangleMesh::exportToOBJ(const std::string &fileName)
{
    std::ofstream objFile(fileName);
    if (!objFile.is_open()) {
        std::cerr << "Failed to open the file for writing" << fileName << std::endl;
    }

    // Write vertices to the file
    for (const auto& vertex: vertices) {
        objFile << "v " << vertex.x << " " << vertex.y << " 0.0\n";
    }

    objFile << "f 1 2 3\n";
    objFile << "f 1 3 4\n";

    objFile.close();
    std::cout << "Mesh exported to " << fileName << std::endl;
}
