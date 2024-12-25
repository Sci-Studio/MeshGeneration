#ifndef GEOM_H
#define GEOM_H

struct CoordinatePoint {
    double x, y;

    // Default constructor (sets default values for x and y)
    CoordinatePoint() : x(0.0), y(0.0) {}

    CoordinatePoint(double _x, double _y) : x(_x), y(_y) {}
};

#endif // GEOM_H
