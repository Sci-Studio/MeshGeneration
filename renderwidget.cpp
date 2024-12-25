#include "renderwidget.h"
#include "renderer.h"
#include "shapes/rectangle.h"
#include "shapes/line.h"
#include "shapes/point.h"
#include "shapes/curve.h"

#include "geometry/airfoil.h"

#include <string>
#include <QMatrix4x4>




RenderWidget::RenderWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

void RenderWidget::initializeGL()
{
    initializeOpenGLFunctions();


    float positions[8] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    float horLineVert[] = {
        -0.7f,  -0.7f, 0.0f,
         0.7f,  -0.7f, 0.0f
    };

    float vertLineVert[] = {
        -0.7f,  -0.7f, 0.0f,
        -0.7f,   0.7f, 0.0f
    };

    float newSquare[8] = {
        -0.7f, -0.3f,
        -0.5f, -0.3f,
        -0.5f,  0.3f,
        -0.7f,  0.3f
    };

    float points[] = {
        -0.5f,  0.5f, 0.0f,  // Point 1
         0.0f,  0.0f, 0.0f,  // Point 2
         0.5f, -0.5f, 0.0f   // Point 3
    };


    float airfoilCurve[] = {
        -0.9f,  0.1f, 0.0f,
        -0.6f,  0.3f, 0.0f,
        -0.3f,  0.2f, 0.0f,
         0.0f,  0.0f, 0.0f,
         0.3f, -0.1f, 0.0f,
         0.6f, -0.2f, 0.0f,
         0.9f, -0.1f, 0.0f
    };

    int nAirfoilPoints = 100;        // Number of points on the airfoil surface
    int nRadialLayers = 30;         // Number of radial layers in the mesh
    double farFieldDistance = 5.0;  // Distance of the far-field boundary
    Airfoil foil(nAirfoilPoints, nRadialLayers, farFieldDistance);

    std::vector<CoordinatePoint> upperFoilPoints = foil.getUpperAirfoilPoints();
    std::vector<CoordinatePoint> lowerFoilPoints = foil.getLowerAirfoilPoints();


    size_t dataSize = upperFoilPoints.size() * 3; // Each Point has 2 floats
    float upperCurve[dataSize];
    float lowerCurve[dataSize];

    // Fill the array
    for (size_t i = 0; i < upperFoilPoints.size(); ++i) {
        upperCurve[i * 3] = upperFoilPoints[i].x;     // Assign x
        upperCurve[i * 3 + 1] = upperFoilPoints[i].y; // Assign y
        upperCurve[i * 3 + 2] = 0.0f; // Assign y
    }

    for (size_t i = 0; i < lowerFoilPoints.size(); ++i) {
        lowerCurve[i * 3] = lowerFoilPoints[i].x;     // Assign x
        lowerCurve[i * 3 + 1] = lowerFoilPoints[i].y; // Assign y
        lowerCurve[i * 3 + 2] = 0.0f; // Assign y
    }

    std::string naca = "2412"; // Example NACA airfoil
    std::string naca2424 = "1408"; // Example NACA airfoil
    int n_points = 100;        // Number of points along the chord
    float chord = 1.0f;        // Chord length
    Airfoil cordFoil(naca, n_points, chord);

    cordFoil.printUpperAirFoilPoints();
    std::vector<CoordinatePoint> chordUpperFoilPoints = cordFoil.getUpperAirfoilPoints();
    std::vector<CoordinatePoint> chordLowerFoilPoints = cordFoil.getLowerAirfoilPoints();

    size_t chordDataSize = chordUpperFoilPoints.size() * 3; // Each Point has 2 floats
    float chordUpperCurve[chordDataSize];
    float chordLowerCurve[chordDataSize];

    // Fill the array
    for (size_t i = 0; i < chordUpperFoilPoints.size(); ++i) {
        chordUpperCurve[i * 3] = chordUpperFoilPoints[i].x;     // Assign x
        chordUpperCurve[i * 3 + 1] = chordUpperFoilPoints[i].y; // Assign y
        chordUpperCurve[i * 3 + 2] = 0.0f; // Assign y
    }

    for (size_t i = 0; i < chordLowerFoilPoints.size(); ++i) {
        chordLowerCurve[i * 3] = chordLowerFoilPoints[i].x;     // Assign x
        chordLowerCurve[i * 3 + 1] = chordLowerFoilPoints[i].y; // Assign y
        chordLowerCurve[i * 3 + 2] = 0.0f; // Assign y
    }

    color.resize(4);
    color[0] = 0.1f;
    color[1] = 0.3f;
    color[2] = 0.8f;
    color[3] = 1.0f;

    shapes.clear();
//    shapes[0] = new Rectangle(*this, positions);
//    shapes[1] = new Line(*this, horLineVert);
//    shapes[2] = new Line(*this, vertLineVert);
//    shapes[3] = new Rectangle(*this, newSquare);
//    shapes[0] = new Curve(*this, airfoilCurve, 7);
//    shapes[1] = new Point(*this, airfoilCurve, 7);
//    shapes.push_back(new Curve(*this, upperCurve, nAirfoilPoints));
//    shapes.push_back(new Curve(*this, lowerCurve, nAirfoilPoints));
    shapes.push_back(new Curve(*this, chordUpperCurve, n_points));
    shapes.push_back(new Curve(*this, chordLowerCurve, n_points));

    shader = new Shader(*this, "/home/hisham/dev_latest/MeshGen/basic.vert");
    shader->Bind();
    shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);

    shader->Unbind();

    for(unsigned int i = 0; i < shapes.size(); i++) {
        const auto& element = shapes[i];
        element->UnBind();
    }
}

void RenderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void RenderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Bind();
    shader->SetUniform4f("u_Color", color[0], color[1], color[2], color[3]);

    for(unsigned int i = 0; i < shapes.size(); i++) {
        const auto& element = shapes[i];
        element->Render();
    }

}

void RenderWidget::changeColor(std::vector<float> color)
{
    if (color.size() > 4)
    {
        qDebug() << "invalid rgba color float";
    }
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->color[3] = color[3];
    update();
}
