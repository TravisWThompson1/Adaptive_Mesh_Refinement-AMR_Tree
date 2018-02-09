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



class Node{

public:

    // Define constructor.
    Node(Node *parent, int dimensions, double lower[], double upper[]);
    // Empty constructor.
    Node();

    // Deconstructor.
    //~Node();


    // Public functions.
    void insert_point(Point* point_ptr);
    void insert_points(vector<Point *> points);
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
    // Private variables:
    // Number of dimensions of the system.
    int dimensions;
    // Pointer to an array of pointers to Point object held by this node.
    vector <Point *> local_points;
    //Point **local_points;//[INITIAL_POINT_ARRAY_SIZE] = {};
    // Pointer to the parent Node.
    Node *parent;
    // Pointer to the array of children Nodes.
    //vector <Node> children;
    //Node *children;
    // Points to the lower and upper bounds arrays.
    vector <double> lower_local, upper_local;
    // Total mass.
    double total_mass;
    vector<double> pos_mass;


    // Private functions:
    void add_point(Point *point_ptr);
    int determine_child_number(Point* point_ptr, int min, int max);
    void calculate_child_boundaries(double *child_lower, double *child_upper, int child_index, int min, int max);
    void generate_children();
    void depopulate_node();
    bool check_underpopulation_criteria();
    bool check_overpopulation_criteria();
    bool check_point_boundaries(Point *point);
    void percolate_to_parent(Point *point);
    void reset_COM();


};



#endif //ADAPTIVE_MESH_REFINEMENT_NODE_H
