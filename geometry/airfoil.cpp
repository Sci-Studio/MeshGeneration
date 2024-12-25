#include "airfoil.h"

#include <cmath>
#include <QDebug>

Airfoil::Airfoil(int nAirfoilPoints, int nRadialLayers, double farFieldDistance)
    : nAirfoilPoints(nAirfoilPoints), nRadialLayers(nRadialLayers), farFieldDistance(farFieldDistance)
{
    m_UpperAirFoilPoints.clear();
    m_LowerAirFoilPoints.clear();

    for (int i = 0; i < nAirfoilPoints; ++i)
    {
        float x = (float)i / (nAirfoilPoints - 1);
        float yt = NACAProfile(x);
        CoordinatePoint pUpper(x, yt);
        CoordinatePoint pLower(x, -yt);
        CoordinatePoint(3.0f, 2.0f);
        m_UpperAirFoilPoints.push_back(pUpper);
        m_LowerAirFoilPoints.push_back(pLower);
    }
}

Airfoil::Airfoil(const std::string& naca, int nAirfoilPoints, float chord) : nAirfoilPoints(nAirfoilPoints) {

    m_UpperAirFoilPoints.clear();
    m_LowerAirFoilPoints.clear();

    // Parse NACA 4-digit parameters
    float m = (naca[0] - '0') * 0.01f;         // Maximum camber
    float p = (naca[1] - '0') * 0.1f;          // Position of maximum camber
    float t = ((naca[2] - '0') * 10 + (naca[3] - '0')) * 0.01f; // Maximum thickness

    for (int i = 0; i < nAirfoilPoints; ++i) {
        float x = chord * (1 - cos(M_PI * i / (nAirfoilPoints - 1))); // Cosine spacing

        // Thickness distribution
        float yt = 5 * t * (0.2969f * sqrt(x / chord) -
                            0.1260f * (x / chord) -
                            0.3516f * pow(x / chord, 2) +
                            0.2843f * pow(x / chord, 3) -
                            0.1015f * pow(x / chord, 4));

        // Camber line and slope
        float yc = 0.0f;
        float dyc_dx = 0.0f;
        if (x / chord < p) {
            yc = m / (p * p) * (2 * p * (x / chord) - pow(x / chord, 2));
            dyc_dx = 2 * m / (p * p) * (p - x / chord);
        } else {
            yc = m / ((1 - p) * (1 - p)) * ((1 - 2 * p) + 2 * p * (x / chord) - pow(x / chord, 2));
            dyc_dx = 2 * m / ((1 - p) * (1 - p)) * (p - x / chord);
        }

        // Angle of the camber line
        float theta = atan(dyc_dx);

        // Upper and lower surfaces
        float xu = x - yt * sin(theta);
        float yu = yc + yt * cos(theta);
        float xl = x + yt * sin(theta);
        float yl = yc - yt * cos(theta);

        // Store upper and lower points
        m_UpperAirFoilPoints.push_back({xu, yu});
        m_LowerAirFoilPoints.push_back({xl, yl});
    }
}

// NACA 4-digit airfoil thickness calculation
float Airfoil::NACAProfile(float x, float t)
{
    return 5 * t * (0.2969 * sqrt(x) - 0.1260 * x - 0.3516 * pow(x, 2) + 0.2843 * pow(x, 3) - 0.1015 * pow(x, 4));
}

void Airfoil::printUpperAirFoilPoints()
{
    for (auto& point : m_UpperAirFoilPoints)
    {
        qDebug() << "X Value: " << point.x << " Y Value: " << point.y;
    }
}

const std::vector<CoordinatePoint> Airfoil::getUpperAirfoilPoints() {
    return m_UpperAirFoilPoints;
}

const std::vector<CoordinatePoint> Airfoil::getLowerAirfoilPoints() {
    return m_LowerAirFoilPoints;
}
