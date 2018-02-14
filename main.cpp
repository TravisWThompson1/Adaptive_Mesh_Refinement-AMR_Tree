// C++ standard libraries
#include <iostream>
#include <random>
#include <iomanip>

// Local AMR included files
#include "include/AMR_Tree.h"
#include "include/Static_Mesh_Tree.h"
#include "include/Adaptive_Mesh_Tree.h"
#include "include/Point.h"


int main() {

    /// Set up Adaptive/Static Mesh Tree parameters:
    // Define the number of dimensions.
    int dimensions = 3;
    // Define upper bounds, lower bounds defaulted at 0.
    double upper_bounds [3] = {10, 10, 10};
    // Define depth of levels for Static tree (will produce (2^(dimensions))^(depth+1) - 1 Nodes).
    int depth = 8;

    /// Set up objects to add into the Tree, in this case a simple Point particle class (Point.cpp/Point.h):
    // Number of test points to add to the system.
    int number_points = 500;
    // Initialize an a vector of Points.
    vector <Point *> points;
    points.reserve(number_points);

    /// Create random coordinates within the region (0,0,0) to upper_bounds for each Point object.
    // Initialize uniform_real_distribution object for creating random coordinates for each Point.
    std::uniform_real_distribution<double> unif(0, upper_bounds[0]);
    std::default_random_engine rand_eng;
    // Create random coordinates for each Point in each dimension.
    for (int dim = 0; dim < number_points; dim++){
        // Initialize mass.
        int mass = dim;
        // Random coordinates.
        double rand_coords[dimensions];
        for (int i = 0; i < dimensions; i++){
            rand_coords[i] = unif(rand_eng);
        }
        // Create new Point object and add it to vector.
        points.push_back(new Point(mass, dimensions, rand_coords));
    }
    std::cout << number_points << " Points created." << std::endl;



    /// Initialize Static and Adaptive Mesh Trees for this example:
    // Initialize a Static Mesh Tree and an Adaptive Mesh Tree.
    Static_Mesh_Tree<Point> staticTree(depth, dimensions, upper_bounds);
    Adaptive_Mesh_Tree<Point> adaptTree(dimensions, upper_bounds);


    /// Use Static Mesh Tree:
    std::cout << "*** TESTING STATIC MESH TREE ***" << std::endl;
    // Insert points into Static Tree.
    staticTree.insert(points);
    std::cout << number_points << " Points inserted into AMR Tree." << std::endl;
    // Update tree - tree should be restructured after every coordinate update.
    staticTree.updateTree();
    std::cout << "Tree has been restructured" << std::endl;
    // Print out leftmost depth.
    std::cout << "Left-most depth = " << staticTree.get_depth() << std::endl;
    std::cout << std::endl;


    /// Use Adaptive Mesh Tree:
    std::cout << "*** TESTING ADAPTIVE MESH TREE ***" << std::endl;
    // Insert points into Adaptive Tree.
    adaptTree.insert(points);
    std::cout << number_points << " Points inserted into AMR Tree." << std::endl;
    // Update tree - tree should be restructured after every coordinate update.
    adaptTree.updateTree();
    std::cout << "Tree has been restructured" << std::endl;
    // Print out leftmost depth.
    std::cout << "Left-most depth = " << adaptTree.get_depth() << std::endl;
    std::cout << std::endl;

    return 0;
}



void rand_coords(double *coord, int dimensions, double length){

}









