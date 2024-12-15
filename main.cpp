#include "mainwindow.h"

#include <QApplication>
#include "geometry/airfoil.h"

int main(int argc, char *argv[])
{
    int nAirfoilPoints = 50;        // Number of points on the airfoil surface
    int nRadialLayers = 30;         // Number of radial layers in the mesh
    double farFieldDistance = 5.0;  // Distance of the far-field boundary
    AirFoil foil(nAirfoilPoints, nRadialLayers, farFieldDistance);

    foil.generateAirfoilPoints();
    foil.generateStructuredMesh();
    foil.printMesh();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
