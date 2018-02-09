//
// Created by Travis on 8/28/2017.
//

#ifndef ADAPTIVE_MESH_REFINEMENT_AMR_TREE_H
#define ADAPTIVE_MESH_REFINEMENT_AMR_TREE_H

#include <iostream>
#include "Node.h"
#include "Point.h"
#include "Control.h"

class AMR_Tree {

public:
    // Public variables.


    // Public constructor.
    AMR_Tree(int dimensions, double *upper_bounds);
    // Default constructor.
    AMR_Tree();

    // Public functions.
    void insertPoint(Point *point_ptr);
    void insertPoints(vector <Point *> points);
    void restructure_tree();
    Node* get_Head_Node();




protected:
    // Protected variables.
    int dimensions;
    Node *head;
    vector <double> lower_global, upper_global;

    // Private functions.




};



#endif //ADAPTIVE_MESH_REFINEMENT_AMR_TREE_H
