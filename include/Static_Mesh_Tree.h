//
// Created by Travis on 10/10/2017.
//

#ifndef ADAPTIVE_MESH_REFINEMENT_STATIC_MESH_TREE_H
#define ADAPTIVE_MESH_REFINEMENT_STATIC_MESH_TREE_H

#include "AMR_Tree.h"


template <class T>
class Static_Mesh_Tree : public AMR_Tree<T> {

public:

    int mDepth;
    int mDimensions;
    double *mUpperBounds;

    // Constructor.
    Static_Mesh_Tree(int depth, int dimensions, double *upper_bounds) : AMR_Tree<T>(dimensions, upper_bounds){
        // Set member variables.
        mDepth = depth;
        mDimensions = dimensions;
        mUpperBounds = upper_bounds;
        // Set depth of AMR Tree.
        this->set_depth(depth);
    }






private:





};


#endif //ADAPTIVE_MESH_REFINEMENT_STATIC_MESH_TREE_H
