#pragma once

struct Point {
    double x, y;

    // Default constructor (sets default values for x and y)
    Point() : x(0.0), y(0.0) {}

    Point(double _x, double _y) : x(_x), y(_y) {}
};
