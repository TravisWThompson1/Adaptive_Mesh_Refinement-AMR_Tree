#include <iostream>
#include <random>
#include "include/AMR_Tree.h"
#include "include/Point.h"
#include <iomanip>

int main() {

    // Define the number of dimensions.
    int dimensions = 3;

    // Define upper bounds, lower bounds defaulted at 0.
    double upper [3] = {10, 10, 10};

    // Initialize AMR tree.
    AMR_Tree<Point> tree(dimensions, upper);

    // Number of test points to add to the system.
    int number_points = 500;

    std::cout << tree.get_Head_Node()->get_Dim() << std::endl;

    // Initialize an a vector of *T.
    vector <Point *> points;
    points.reserve(number_points);

    // Initialize random object for creating random coordinates for each T.
    std::uniform_real_distribution<double> unif(0, upper[0]);
    std::default_random_engine rand_eng;


    // Create random coordinates for each T in each dimension.
    for (int dim = 0; dim < number_points; dim++){
        // Initialize mass.
        int mass = dim;
        // Random coordinates.
        double rand_coords[dimensions];
        for (int i = 0; i < dimensions; i++){
            rand_coords[i] = unif(rand_eng);
        }
        // Create new T object.
        points.push_back(new Point(mass, dimensions, rand_coords));
    }
    std::cout << number_points << " Points created." << std::endl;

    // Insert points into AMR_Tree.
    tree.insert(points);
    std::cout << number_points << " Points inserted into AMR Tree." << std::endl;

    // Restructure tree - tree should be restructured after every coordinate update.
    tree.restructure_tree();
    std::cout << "Tree has been restructured" << std::endl;

    // Print out leftmost depth.
    std::cout << "Depth: " << tree.get_Head_Node()->get_depth() << std::endl;

    return 0;
}



void rand_coords(double *coord, int dimensions, double length){

}









