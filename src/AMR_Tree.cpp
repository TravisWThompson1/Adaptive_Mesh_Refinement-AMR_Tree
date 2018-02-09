//
// Created by Travis on 8/28/2017.
//

#include "../include/AMR_Tree.h"


/**
 * AMR Tree constructor given the number of dimensions of the system and the length of the system as an array. The
 * input of the length "upper_bounds" array will be used to create a system boundary from 0 to the length in each
 * dimension.
 *
 * @param dimensions The number of dimensions of the system.
 * @param upper_bounds An array of the length of the system along each dimension. The number of elements in the array
 * should be the number of dimensions.
 */
AMR_Tree::AMR_Tree(int dimensions, double upper_bounds[]) {
    // Initialize dimensions.
    this->dimensions = dimensions;

    // Initialize upper and lower bound pointers.
    double lower_bounds[dimensions];
    this->upper_global.reserve(dimensions);
    this->lower_global.reserve(dimensions);
    for (int dim = 0; dim < dimensions; dim++){
        this->upper_global.push_back(upper_bounds[dim]);
        this->lower_global.push_back(0.0);
        lower_bounds[dim] = 0.0;
    }

    // Initialize head node.
    this->head = new Node(NULL, dimensions, lower_bounds, upper_bounds);
}



/**
 * Default constructor.
 */
AMR_Tree::AMR_Tree(){

}




/**
 * Insert a Point pointer into the AMR Tree.
 *
 * @param point_ptr Pointer to a Point object that will be inserted into the AMR Tree.
 */
void AMR_Tree::insertPoint(Point* point_ptr){
    // Call insert_point method in the head Node.
    this->head->insert_point(point_ptr);
}


/**
 * Insert an array of Point pointers into the AMR Tree.
 *
 * @param point_ptr P The first Point pointer in a Point pointer array that will be inserted into the AMR Tree.
 * @param num_points Number of elements in Point pointer array to be added to the AMR_Tree.
 */
void AMR_Tree::insertPoints(vector <Point *> points){
    // Call insert_points method in the head Node.
    this->head->insert_points(points);
}



/**
 * Recursively passes through all Nodes to check if any Nodes should be further subdivided or merged.
 */
void AMR_Tree::restructure_tree() {
    // Call Node::restructure_points() routine on head Node.
    this->head->restructure_points();
    // Call Node::restucture_tree() routine on head Node.
    this->head->restructure_tree();
    // Call Node::update_COM() routine on head Node.
    this->head->update_COM();
}







// Extra stuff

Node *AMR_Tree::get_Head_Node() {
    return head;
}


























