#include "airfoil.h"

#include <QDebug>
#include <cmath>
#include <iomanip>
#include <iostream>

AirFoil::AirFoil(int nAirfoilPoints, int nRadialLayers, double farFieldDistance)
    : nAirfoilPoints(nAirfoilPoints), nRadialLayers(nRadialLayers), farFieldDistance(farFieldDistance)
{

}

void AirFoil::generateAirfoilPoints()
{
    m_AirFoilPoints.clear();

    for (int i = 0; i < nAirfoilPoints; ++i)
    {
        float x = (float)i / (nAirfoilPoints - 1);
        float yt = NACAProfile(x);
        Point pUpper(x, yt);
        Point pLower(x, -yt);
        Point(3.0f, 2.0f);
        m_AirFoilPoints.push_back(pUpper);
        m_AirFoilPoints.push_back(pLower);
    }
}

// NACA 4-digit airfoil thickness calculation
float AirFoil::NACAProfile(float x, float t)
{
    return 5 * t * (0.2969 * sqrt(x) - 0.1260 * x - 0.3516 * pow(x, 2) + 0.2843 * pow(x, 3) - 0.1015 * pow(x, 4));
}

void AirFoil::generateStructuredMesh() {
    m_MeshPoints.clear();
    m_MeshPoints.resize(nRadialLayers, std::vector<Point>(nAirfoilPoints * 2));

    // Generate radial layers
    for (int layer = 0; layer < nRadialLayers; ++layer) {
        double r = 1.0 + (double)layer / (nRadialLayers - 1) * (farFieldDistance - 1.0); // Radial distance

        for (int i = 0; i < nAirfoilPoints * 2; ++i) {
            double x = m_AirFoilPoints[i].x * r; // Scale x and y by r
            double y = m_AirFoilPoints[i].y * r;
            Point p(x, y);
            m_MeshPoints[layer][i] = Point(x, y);  // Add to mesh
        }
    }
}

void AirFoil::printAirFoilPoints()
{
    for (auto& point : m_AirFoilPoints)
    {
        qDebug() << "X Value: " << point.x << " Y Value: " << point.y;
    }
}

void AirFoil::printMesh() {
    std::cout << std::fixed << std::setprecision(4);
    for (const auto& layer : m_MeshPoints) {
        for (const auto& point : layer) {
            std::cout << "(" << point.x << ", " << point.y << ") ";
        }
        std::cout << std::endl;
    }
}

