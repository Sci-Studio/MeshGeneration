#ifndef AIRFOIL_H
#define AIRFOIL_H

#include <vector>
#include "geom.h"

class Airfoil
{
public:
    Airfoil(int nAirfoilPoints, int nRadialLayers, double farFieldDistance);
    Airfoil(const std::string& naca, int n_points, float chord);

    void printUpperAirFoilPoints();
    const std::vector<CoordinatePoint> getUpperAirfoilPoints();
    const std::vector<CoordinatePoint> getLowerAirfoilPoints();
private:
    int nAirfoilPoints;     // Number of points on the airfoil surface
    int nRadialLayers;      // Number of layers in the radial direction (from airfoil to far-field)
    double farFieldDistance; // Distance of the far-field from the airfoil

    std::vector<CoordinatePoint> m_UpperAirFoilPoints;
    std::vector<CoordinatePoint> m_LowerAirFoilPoints;


    float NACAProfile(float x, float t = 0.12f);
};

#endif // AIRFOIL_H
