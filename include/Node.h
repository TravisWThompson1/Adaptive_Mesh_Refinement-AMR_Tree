//
// Created by Travis on 9/18/2017.
//

//#include "AMR_Tree.h"
#include <iostream>
#include "Point.h"
#include "Control.h"
#include <cmath>
#include <vector>
using namespace std;

#ifndef ADAPTIVE_MESH_REFINEMENT_NODE_H
#define ADAPTIVE_MESH_REFINEMENT_NODE_H

template <class T> class Node {

public:

    /**
     * Constructors:
     */

    // Define constructor.
    Node(Node<T> *parent, int dimensions, double lower[], double upper[]);
    // Empty constructor.
    Node();



    /**
     *  Public functions:
     */

    //template <class T>
    void insert(T *T_ptr);
    //template <class T>
    void insert(vector<T*> points);
    //template <class T>
    void insert(T *T_ptrs, int list_size);

    void restructure_tree();
    void restructure_points();
    void update_COM();
    vector<double> get_COM();
    double get_total_mass();

    int get_Dim();
    int get_depth();

    // Pointer to the array of children Nodes.
    vector <Node> children;


private:

    /**
     * Private variables:
     */

    // Number of dimensions of the system.
    int dimensions;
    // Pointer to an array of pointers to T object held by this node.
    //template <class T>
    vector <T *> local_points;
    // Pointer to the parent Node.
    Node *parent;
    // Points to the lower and upper bounds arrays.
    vector <double> lower_local, upper_local;




    /**
     * Private functions:
     */

    //template <class T>
    void add(T *T_ptr);

    //template <class T>
    int determine_child_number(T* T_ptr, int min, int max);

    void calculate_child_boundaries(double *child_lower, double *child_upper, int child_index, int min, int max);
    void generate_children();
    void depopulate_node();
    bool check_underpopulation_criteria();
    bool check_overpopulation_criteria();

    //template <class T>
    bool check_point_boundaries(T *T_ptr);
    //template <class T>
    void percolate_to_parent(T *T_ptr);

};



#endif //ADAPTIVE_MESH_REFINEMENT_NODE_H
