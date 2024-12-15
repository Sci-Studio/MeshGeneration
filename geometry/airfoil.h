#pragma once

#include <vector>
#include "geom.h"

class AirFoil
{
private:
    int nAirfoilPoints;     // Number of points on the airfoil surface
    int nRadialLayers;      // Number of layers in the radial direction (from airfoil to far-field)
    double farFieldDistance; // Distance of the far-field from the airfoil

    std::vector<Point> m_AirFoilPoints;
    std::vector<std::vector<Point>> m_MeshPoints; // 2D structured mesh points

    float NACAProfile(float x, float t = 0.12f);
public:
    AirFoil(int nAirfoilPoints, int nRadialLayers, double farFieldDistance);
    void generateAirfoilPoints();
    void generateStructuredMesh();

    void printAirFoilPoints();
    void printMesh();              // Outputs the mesh to the console (or file)
};


