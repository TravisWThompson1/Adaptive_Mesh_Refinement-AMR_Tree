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
        this->restructure_points();
        // Restructure tree if necessary.
        this->restructure_tree();
    }







private:





};


#endif //ADAPTIVE_MESH_REFINEMENT_STATIC_MESH_TREE_H
