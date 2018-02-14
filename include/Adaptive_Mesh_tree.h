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




    /**
     * Public functions
     */

    /**
     * Checks all objects in adaptive mesh tree to see if any objects need to be moved to new Nodes due to recent
     * coordinate updates. Then, the the tree will be restructured if existing Nodes have become to populated or too
     * unpopulated. Calls restructure_points() and restructure_tree() functions in super (AMR_Tree).
     */
    void updateTree(){
        // Restructure objects in tree.
        restructure_points();
        // Restructure tree if necessary.
        restructure_tree();
    }



};




#endif //ADAPTIVE_MESH_REFINEMENT_ADAPTIVE_MESH_TREE_H
