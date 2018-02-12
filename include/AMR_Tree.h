//
// Created by Travis on 8/28/2017.
//

#ifndef ADAPTIVE_MESH_REFINEMENT_AMR_TREE_H
#define ADAPTIVE_MESH_REFINEMENT_AMR_TREE_H

#include <iostream>
#include "Node.h"
#include "Point.h"
#include "Control.h"

template <class T> class AMR_Tree {

public:
    // Public variables.

    /**
     * Constructors:
     */

    // Public constructor.
    AMR_Tree(int dimensions, double *upper_bounds);
    // Default constructor.
    AMR_Tree();



    /**
     * Public functions:
     */
    //template <class T>
    void insert(T *T_ptr);

    //template <class T>
    void insert(vector<T *> T_ptr);

    //template <class T>
    void insert(T *T_ptr, int list_size);

    void restructure_tree();
    Node<T>* get_Head_Node();




protected:

    /**
     * Private variables:
     */

    // Protected variables.
    int dimensions;
    Node<T> *head;
    vector <double> lower_global, upper_global;




};



#endif //ADAPTIVE_MESH_REFINEMENT_AMR_TREE_H
