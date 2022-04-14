//
// Created by jszym on 04/04/2022.
//

#ifndef GRAPHS_ADJMATRIX_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include "GraphInterface.h"
#define GRAPHS_ADJMATRIX_H

class AdjMatrix : public GraphInterface {
private:
    int *matrix; // Pointer to the first element of the square matrix
    int size; // Size of the square matrix

    //! Function finding path by reverse iteration
    static int findPath(int * path, const int * prev, int source, int target);
    //! Function finding index of nearest vertex
    int minDist(const int *dist, const bool *vis) const;
    //! Function prints results of dijkstra's shortest path finding
    void printResults(const int * prev, const int * dist, int source) const;
    //! Function prints results of dijkstra's shortest path finding to a file
    void printResultsToFile(const int * prev, const int * dist, int source, const std::string& fileName) const;
public:
    //! Constructor
    AdjMatrix(const int *array, int arraySize);
    //! Destructor
    ~AdjMatrix() {delete [] matrix;}

    //! Function printing matrix
    void printData();
    //! Dijkstra shortest path finding
    void dijkstra(int source);
};

#endif //GRAPHS_ADJMATRIX_H
