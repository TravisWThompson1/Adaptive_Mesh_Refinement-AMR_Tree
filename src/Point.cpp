//
// Created by Travis on 9/21/2017.
//

#include "../include/Point.h"


/**
 * Point constructor with a given mass, dimensions, and location coordinates. The velocity vector is not specified
 * in the constructor and is set to 0 in all directions by default.
 *
 * @param mass Mass of the point.
 * @param dimensions Dimensions of the coordinate vector.
 * @param coordinates Coordinate vector of the point's location.
 */
Point::Point(double mass, int dimensions, double coordinates[]) {
    // Initialize dimensions.
    this->dimensions = dimensions;

    // Initialize mass.
    this->mass = mass;

    // Initialize coordinates and initialize velocities to 0.
    this->coordinates.reserve(dimensions);
    this->velocity.reserve(dimensions);
    for (int dim = 0; dim < dimensions; dim++) {
        this->coordinates.push_back(coordinates[dim]);
        this->velocity.push_back(0.0);
    }
}


/**
 * Overloaded Point constructor with a given mass, dimensions, coordinate vector, and velocity vector.
 *
 * @param mass Mass of the point.
 * @param dimensions Dimensions of the coordinate vector.
 * @param coordinates Coordinate vector of the point's location.
 * @param velocity Velocity vector of the point's veloctiy.
 */
Point::Point(double mass, int dimensions, double coordinates[], double velocities[]) {
    // Initialize dimensions.
    this->dimensions = dimensions;

    // Initialize mass.
    this->mass = mass;

    // Initialize coordinates and initialize velocities to 0.
    this->coordinates.reserve(dimensions);
    this->velocity.reserve(dimensions);
    for (int dim = 0; dim < dimensions; dim++) {
        this->coordinates.push_back(coordinates[dim]);
        this->velocity.push_back(velocities[dim]);
    }
}



double Point::getMass() {
    return this->mass;
}


vector<double> Point::getCoordinates() {
    return this->coordinates;
}

void Point::updateCoordinates(double *newCoords) {
    // Update coordinates.
    for (int dim = 0; dim < this->dimensions; dim++) {
        Point::coordinates[dim] = *(newCoords + dim);
    }
}






