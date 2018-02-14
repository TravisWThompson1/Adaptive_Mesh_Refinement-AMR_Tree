//
// Created by Travis on 2/14/2018.
//

#ifndef ADAPTIVE_MESH_REFINEMENT_ADAPTIVE_MESH_TREE_H
#define ADAPTIVE_MESH_REFINEMENT_ADAPTIVE_MESH_TREE_H

#include "AMR_Tree.h"

template <class T> class Adaptive_Mesh_Tree : public AMR_Tree {

public:

    int mDimensions;
    double *mUpperBounds;

    /**
     * Contructor
     */

    Adaptive_Mesh_Tree(int dimensions, double *upper_bounds) : AMR_Tree<T>(dimensions, upper_bounds) {
        // Set member variables.
        mDimensions = dimensions;
        mUpperBounds = upper_bounds;
    }






};




#endif //ADAPTIVE_MESH_REFINEMENT_ADAPTIVE_MESH_TREE_H
