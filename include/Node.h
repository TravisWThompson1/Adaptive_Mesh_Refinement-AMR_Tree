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

    // Pointer to the array of children Nodes.
    vector <Node> children;

    /**
     * Constructors:
     */


    /**
    * Constructor for the Node object. Each node represents a section of the system which is determined by in the input
    * parameter arrays "lower" and "upper", which are used as the upper and lower local boundaries. The number of
    * dimensions should be the same as the number of elements in the "upper" and "lower" boundary arrays. Lastly, each
    * Node has a parent Node that it descends from, that is, except for the Head node, which has NULL for a parent.
    *
    * @param parent Pointer to the parent Node object.
    * @param dimensions Number of dimensions of the system (and length of the "upper" and "lower"  parameter arrays).
    * @param lower Local lower boundary given in an array of length "dimensions".
    * @param upper Local upper boundary given in an array of length "dimensions".
    */
    Node(Node<T> *parent, int dimensions, double lower[], double upper[]) {
        // Initialize parent node.
        this->parent = parent;

        // Initialize dimensions.
        this->dimensions = dimensions;

        // Initialize upper and lower bound pointers.
        this->upper_local.reserve(dimensions);
        this->lower_local.reserve(dimensions);
        for (int dim = 0; dim < dimensions; dim++){
            this->upper_local.push_back(upper[dim]);
            this->lower_local.push_back(lower[dim]);
        }

        // Initialize children vector array to the size of 2^dimensions.
        this->children.reserve((int) pow(2, dimensions));

    }


    /**
    * The empty Node constructor should only be used to create an empty Node instance, generally for array initialization.
    */
    Node() {

    };



    /**
    * Deconstructor.
    */
    /*
    ~Node() {
        delete [] this->upper_local;
        delete [] this->lower_local;
        delete [] this->local_points;
        if (this->children  != NULL){
            delete [] this->children;
        }
    }
    */



    /**
    * Recursively inserts a single pointer of a T (template) object into the proper Node based off of local boundaries. This
    * function either accepts the pointer into its array of T, or it will determine the correct child to pass this pointer to
    * and will call this function again recursively on its children until the lowest level Node is found with the correct
    * boundaries.
    *
    * @param T_ptr Pointer to a template T object that will be attempted to be inserted into this Node.
    */
    void insert(T *T_ptr) {
        // Check if there are children.
        if (this->children.size() == 0) {
            // T should be held in this Node.
            this->add(T_ptr);
        } else {
            // Determine child that this point should belong to.
            int child_num = this->determine_child_number(T_ptr, 0, (int) pow(2, this->dimensions) - 1);
            // Pass point to child.
            this->children.at(child_num).insert(T_ptr);
        }
    }


    /**
    * Insert an array of pointers to objects into the AMR_Tree object. This function calls the AMR_Tree::insert()
    * function for each point in the given array.
    *
    * @param T_ptrs Pointer to the first element of a Point pointer array.
    */
    void insert(vector<T *> T_ptrs) {
        // Call insert routine for all T_ptrs given.
        for (int i = 0; i < T_ptrs.size(); i++) {
            T *T_ptr = T_ptrs.at(i);
            // Insert point.
            this->insert(T_ptr);
        }
    }




    /**
    * Insert an array of pointers to objects into the AMR_Tree object. This function calls the AMR_Tree::insert()
    * function for each point in the given array.
    *
    * @param T_ptrs Pointer to the first element of a Point pointer array.
    */
    void insert(T *T_ptrs, int list_size) {
        // Call insert routine for all T_ptrs given.
        for (int i = 0; i < list_size; i++) {
            T *T_ptr = T_ptrs[i];
            // Insert point.
            this->insert(T_ptr);
        }
    }



    /**
    * Creates 2^dimensions children Nodes to divide this Node's volume.
    */
    void generate_children() {
        // Calculate the number of children.
        int num_children = pow(2, this->dimensions);
        // Initialize new children nodes.
        for (int i = 0; i < num_children; i++){
            // Initialize lower and upper boundaries for the child Node.
            double child_lower[dimensions], child_upper[dimensions];
            // Determine the lower and upper boundaries of the child Node.
            this->calculate_child_boundaries(child_lower, child_upper, i, 0, num_children-1);
            //std::cout << "(" << child_lower[0] << "," << child_lower[1] << "," << child_lower[2] << ") (" <<
            //          child_upper[0] << "," << child_upper[1] << "," << child_upper[2] << ")" << std::endl;
            // Create new child Node.
            this->children.push_back(Node<T>(this, this->dimensions, child_lower, child_upper));
        }
    }


    /**
    * Recursively passes through all Nodes to check if any Nodes should be further subdivided or merged. This function is
    * typically called after the Node::restructure_points() function, which is typically called after the Points contained
    * in this AMR Tree have had their position updated.
    */
    void restructure_tree() {
        // Check if there are children Nodes.
        if (this->children.size() == 0) {
            // No children nodes, this Node is the lowest on its chain.
            bool subdivide = this->check_overpopulation_criteria();
            if (subdivide == true){
                // This Node will be subdivided.
                this->generate_children();
                // Insert points by calling insert function on this node, which will properly pass the points to
                // the newly generated children.
                this->insert(this->local_points);
                // Empty this Node's pointer list.
                this->local_points.clear();
                // Move to children nodes.
                for (int i = 0; i < this->children.size(); i++){
                    Node<T> *child = &(this->children[i]);
                    child->restructure_tree();
                }
            }

            // There are children Nodes, check if a merge should be performed.
        } else {
            // Check if there are any grandchildren (children of children).
            bool grandchildren = false;
            for (int i = 0; i < this->children.size(); i++){
                if (this->children.at(i).children.size() != 0){
                    // There are grandchildren (this->child->child).
                    grandchildren = true;
                    break;
                }
            }
            // Check if a merge is allowed.
            if (grandchildren == false){
                // Check if merge should happen.
                bool merge = this->check_underpopulation_criteria();
                if (merge == true){
                    // Depopulate children nodes.
                    for (int i = 0; i < this->children.size(); i++){
                        // Call depopulate() function on each child node.
                        this->children.at(i).depopulate_node();
                    }
                    // Clear children node list.
                    this->children.clear();
                }
            } else {
                // Merge not allowed, recursively call the restructure function on all of this Node's children.
                for (int i = 0; i < this->children.size(); i++){
                    this->children.at(i).restructure_tree();
                }
            }
        }
    }




    /**
    * Recursively passes through all Nodes' children to check if any points should be redistributed into different local
    * Nodes. This function is typically called after the positions of the Points have been updated, and should therefore
    * be updated in the AMR Tree as well. This function recursively moves through all children first to reach the bottom,
    * where it checks if there are any points that do no belong in the current Node they are stored in. These out-of-bounds
    * Points will be passed upwards until they are held by a Node that does contain the Point. At that time, this function
    * will call the insert_point function to insert it into that Node, or recursively into its children, as handled by the
    * insert_point function.
    */
    void restructure_points() {
        // Move to children Nodes.
        for (int i = 0; i < this->children.size(); i++){
            // Call this function on children Nodes.
            this->children.at(i).restructure_points();
        }
        // Check if this Node has points to check the boundaries of.
        int offset = 0;
        for (int i = 0; i < this->local_points.size(); i++){
            // Check if each point belongs in this Node.
            Point *point = this->local_points[i + offset];
            bool local = this->check_point_boundaries(point);
            if (local == false) {
                // This T does not belong in this Node, it will be percolated up to its parent.
                this->percolate_to_parent(point);
                // Remove this T from this Node.
                this->local_points.erase(this->local_points.begin() + i + offset);
                // Increase offset amount.
                offset += -1;
            }
        }
        // Now that Points have been percolated up into the correctly boundaried Nodes, we must percolate them down into
        // the lowest Nodes that each T belongs in. (Note: if this Node's local_points vector does not contain any
        // Points, then the Node::insert() function will simply return.
        if (this->children.size() != 0) {
            this->insert(this->local_points);
        }
    }








    // Extra stuff
    int get_Dim() {
        return this->dimensions;
    }


    int get_depth() {
        if (this->children.size() == 0){
            return 1;
        } else {
            return 1 + this->children.at(0).get_depth();
        }
    }



















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
    * PRIVATE FUNCTIONS:
    */


    /**
    * Recursively determines the integer value (in array of child Node pointers) that the given point belongs in.
    * @param point_ptr Point pointer to the Point that will be passed to a child Node.
    * @param dim Number of dimensions to work with in the current iteration (should be number of dimensions of the system
    * when this function is called.
    * @return Returns the integer value of the index of the Point pointer array of children.
    */
    int determine_child_number(T *T_ptr, int min, int max) {
        // Determine number of children in the range min to max (1-indexed).
        int num_of_children = max - min + 1;
        // Determine the current dimension number to divide axes (total_dimensions - num_of_checked_dimensions).
        int dim = this->dimensions - (int) log2(num_of_children);
        // Check recursive stop condition (one index remaining).
        if (num_of_children == 1){
            // Return child pointer index.
            return min;
        }
        // Calculate dividing value.
        double middle_value = (this->upper_local[dim] - this->lower_local[dim]) / 2 + (this->lower_local[dim]);
        // Determine if the T falls within the lower or upper half of the current node.
        if (T_ptr->getCoordinates().at(dim) <= middle_value){
            // T belongs on lower side of this axis.
            return this->determine_child_number(T_ptr, min, num_of_children/2+min-1);
        } else {
            // T belongs on the upper side of this axis.
            return this->determine_child_number(T_ptr, num_of_children/2+min, max);
        }
    }


    /**
    * Add point to this Node's Point pointer array.
    *
    * @param T_ptr Point to be added to this Node's Point pointer array.
    */
    void add(T *T_ptr) {
        // Add this T to T array.
        local_points.push_back(T_ptr);
    }



    /**
    * Recursively determines the boundaries of the child Node that the given child Node index belongs in. The children
    * Nodes are recursively divided in half, where the lower half belongs on the lower half of this Node's
    * local boundaries. For example, there are 2^dimensions children nodes. In a 3 dimensional system, there are 8 nodes.
    * The (0-indexed) 0-3 nodes belong on the lower half of this Node's x boundaries, while the 4-7 nodes belong on the upper
    * half. This function will recursively call itself again on the lower or upper half and determine if the child node
    * belongs on the lower (0-1, or 4-5) half or the upper (2-3, or 6-7) half for the y dimension. Lastly, it will call
    * itself one more time to determine if the z is in the upper or lower half of this boundary. So the result is a
    * determination of if each axis is in the upper or lower half of this Node's boundary for each dimension.
    *
    * @param child_lower Pointer to the array of the child's lower boundaries to be determined by this function.
    * @param child_upper Pointer to the array of the child's upper boundaries to be determined by this function.
    * @param child_index Index of the child Node (from 0 to (2^dimensions)-1).
    * @param min Minimum index of the range to search of children indexes (from 0 to (2^dimensions)-1). Value of the first
    * call to this function should be 0.
    * @param min Maximum index of the range to search of children indexes (from 0 to (2^dimensions)-1). Value of the first
    * call to this function should be (2^dimensions)-1.
    */
    void calculate_child_boundaries(double *child_lower, double *child_upper, int child_index, int min, int max) {
        // Determine number of children in the range min to max (1-indexed).
        int num_of_children = max - min + 1;
        // Determine the current dimension number to divide axes (total_dimensions - num_of_checked_dimensions).
        int dim = this->dimensions - (int) log2(num_of_children);
        // Check recursive stop condition (one index remaining).
        if (num_of_children == 1){
            // All dimensions have been traversed.
            return;
        }
        // Calculate dividing value.
        double middle_value = (this->upper_local[dim] - this->lower_local[dim]) / 2.0 + (this->lower_local[dim]);
        // Determine if the T falls within the lower or upper half of the current node.
        if (child_index < min + num_of_children/2){
            // This dimension's boundary belongs on lower side of the middle of this Node's boundaries.
            child_lower[dim] = this->lower_local[dim];
            child_upper[dim] = middle_value;
            // Determine next dimension values.
            return this->calculate_child_boundaries(child_lower, child_upper, child_index, min, num_of_children/2+min-1);
        } else {
            // This dimension's boundary belongs on upper side of the middle of this Node's boundaries.
            child_lower[dim] = middle_value;
            child_upper[dim] = this->upper_local[dim];
            // Determine next dimension values.
            return this->calculate_child_boundaries(child_lower, child_upper, child_index, num_of_children/2+min, max);
        }
    }




    /**
    * Pass all Point pointers to the parents Node.
    */
    void depopulate_node() {
        // Check if there is a parent node to pass items to.
        if (this->parent == NULL){
            std::cout << "Attempted call to function Node::depopulate_node() to pass items to a NULL parent. Node refuses to depopulate." << std::endl;
        } else {
            for (int i = 0; i < this->local_points.size(); i++){
                // Add all T pointers to parent.
                this->parent->add(this->local_points[i]);
            }
        }
    }


    /**
    * Check if the total number of points in the children Nodes are greater than MIN_POINTS_ALLOWED.
    * @return True if there are less points than the minimum, or false if there are more than the minimum.
    */
    bool check_underpopulation_criteria(){
        // Count the number of points in the children Node.
        int count = 0;
        for (int i = 0; i < (int) pow(2, this->dimensions); i++){
            count += this->children.at(i).local_points.size();
        }
        // Check if the Node's children are underpopulated.
        if (count < MIN_POINTS_ALLOWED){
            // Children Nodes are underpopulated and should be merged back into the parent Node.
            return true;
        } else {
            // Children Nodes are sufficiently populated and should not be merged back into the parent Node.
            return false;
        }
    }


    /**
    * Check if the number of Points this Node contains is ove the MAX_POINTS_ALLOWED value and should be subdivided.
    * @return True if this Node is overpopulated, or false if it is not.
    */
    bool check_overpopulation_criteria() {
        // Check if there are more points in this Node than the MAX_POINTS_ALLOWED value.
        int size = this->local_points.size();
        if (this->local_points.size() > MAX_POINTS_ALLOWED){
            // This Node is overpopulated.
            return true;
        } else {
            // This Node is not overpopulated.
            return false;
        }
    }


    /**
    * Given a Point pointer, this function will check if the Point's coordinates are within this Node's boundaries.
    *
    * @param T_ptr Point pointer to be check if it is within the local Node's boundaries.
    * @return True if the Point is within this Node's boundaries, or false if it is not.
    */
    bool check_point_boundaries(T *T_ptr) {
        // Get T's coordinates.
        vector<double> coords = T_ptr->getCoordinates();
        // Check if point is within local boundaries of this Node.
        for (int dim = 0; dim < this->dimensions; dim++){
            if ((coords[dim] < this->lower_local[dim]) || (coords[dim] > this->upper_local[dim])){
                // T is not within local boundaries.
                return false;
            }
        }
        // T is within local boundaries.
        return true;
    }


    /**
    * Inserts Point pointer into the Parent Node.
    * @param T_ptr Pointer pointer to be added to the parent Node.
    */
    void percolate_to_parent(T *T_ptr) {
        // Check if there is a parent node to pass items to.
        if (this->parent == NULL){
            std::cout << "Attempted call to function Node::percolate_to_parent() to pass items to a NULL parent. Node refuses to pass items." << std::endl;
        } else {
            // Insert T pointer into parent Node.
            this->parent->add(T_ptr);
        }
    }


};



#endif //ADAPTIVE_MESH_REFINEMENT_NODE_H
