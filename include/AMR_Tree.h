//
// Created by Travis on 8/28/2017.
//

#ifndef ADAPTIVE_MESH_REFINEMENT_AMR_TREE_H
#define ADAPTIVE_MESH_REFINEMENT_AMR_TREE_H

#include <iostream>
#include "Node.h"
#include "Control.h"

template <class T> class AMR_Tree {

public:

    /**
     * AMR Tree constructor given the number of dimensions of the system and the length of the system as an array. The
     * input of the length "upper_bounds" array will be used to create a system boundary from 0 to the length in each
     * dimension.
     *
     * @param dimensions The number of dimensions of the system.
     * @param upper_bounds An array of the length of the system along each dimension. The number of elements in the array
     * should be the number of dimensions.
     */
    AMR_Tree(int dimensions, double upper_bounds[]) {
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
        this->head = new Node<T>(NULL, dimensions, lower_bounds, upper_bounds);
    }


    /**
    * Default constructor.
    */
    AMR_Tree(){

    }



    /**
    * Insert a Point pointer into the AMR Tree.
    *
    * @param point_ptr Pointer to a Point object that will be inserted into the AMR Tree.
    */
    void insert(T *T_ptr){
        // Call insert method in the head Node.
        this->head->insert(T_ptr);
    }


    /**
    * Insert an array of Point pointers into the AMR Tree.
    *
    * @param point_ptr P The first Point pointer in a Point pointer array that will be inserted into the AMR Tree.
    * @param num_points Number of elements in Point pointer array to be added to the AMR_Tree.
    */
    void insert(vector<T *> T_ptrs){
        // Call insert method in the head Node.
        this->head->insert(T_ptrs);
    }


    /**
    * Insert an array of Point pointers into the AMR Tree.
    *
    * @param point_ptr P The first Point pointer in a Point pointer array that will be inserted into the AMR Tree.
    * @param num_points Number of elements in Point pointer array to be added to the AMR_Tree.
    */
    void insert(T *T_ptrs, int list_size){
        // Call insert method in the head Node.
        this->head->insert(T_ptrs, list_size);
    }


    /**
    * Recursively passes through all Nodes to check if any Nodes should be further subdivided or merged.
    */
    void restructure_tree() {
        // Call Node::restructure_points() routine on head Node.
        this->head->restructure_points();
        // Call Node::restucture_tree() routine on head Node.
        this->head->restructure_tree();
    }


    /**
     * Return pointer to the head Node.
     * @return Node pointer to head node.
     */
    Node<T>* get_Head_Node() {
        // Return head node.
        return head;
    }



    int getDim(){
        return dimensions;
    }






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