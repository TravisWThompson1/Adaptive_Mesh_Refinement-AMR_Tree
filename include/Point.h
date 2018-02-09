//
// Created by Travis on 9/21/2017.
//

#include "Control.h"

#ifndef ADAPTIVE_MESH_REFINEMENT_POINT_H
#define ADAPTIVE_MESH_REFINEMENT_POINT_H


class Point {

private:
    double mass;
    int dimensions;
    vector <double> coordinates, velocity;



public:
    // Constructor.
    Point(double mass, int dim, double coordinates[]);
    // Overloaded constructor.
    Point(double mass, int dim, double coordinates[], double velocities[]);

    // Public functions.
    double getMass();
    vector<double> getCoordinates();
    void updateCoordinates(double newCoords []);

};


#endif //ADAPTIVE_MESH_REFINEMENT_POINT_H
