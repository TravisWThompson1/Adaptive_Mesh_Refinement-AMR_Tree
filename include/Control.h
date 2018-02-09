//
// Created by Travis on 9/19/2017.
//

#ifndef ADAPTIVE_MESH_REFINEMENT_CONTROL_H
#define ADAPTIVE_MESH_REFINEMENT_CONTROL_H

#include <iostream>
#include <vector>
using namespace std;

// Initial size of T array held by each Node.
//#define INITIAL_POINT_ARRAY_SIZE 10
// Size of increase to a T array when an increase of size is needed.
//#define POINT_ARRAY_INCREASE 10


// Maximum number of points allowed to be held by a Node before subdividing.
#define MAX_POINTS_ALLOWED 10
// Minimum number of points allowed to be held by a Node before merging.
#define MIN_POINTS_ALLOWED 3




#endif //ADAPTIVE_MESH_REFINEMENT_CONTROL_H
