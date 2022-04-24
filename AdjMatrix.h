//
// Created by jszym on 04/04/2022.
//

#ifndef GRAPHS_ADJMATRIX_H
#include "GraphInterface.h"
#define GRAPHS_ADJMATRIX_H

class AdjMatrix : public GraphInterface {
private:
    int *matrix; // Pointer to the first element of the square matrix
    int size; // Size of the square matrix

    //! Function finding path by reverse iteration
    int findPath(int * path, const int * prev, int source, int target) const override;
    //! Function finding index of nearest vertex
    int minDist(const int *dist, const bool *vis) const override;
    //! Function prints results of dijkstra's shortest path finding
    void printResults(const int * prev, const int * dist, int source) const override;
    //! Function prints results of dijkstra's shortest path finding to a file
    void printResultsToFile(const int * prev, const int * dist, int source, const std::string& fileName) const override;
public:
    //! Constructor taking matrix as input data
    AdjMatrix(const int *array, int arraySize);
    //! Constructor taking list of edges as an array
    AdjMatrix(const int *array, int edges, int vertices);
    //! Destructor freeing allocated memory
    ~AdjMatrix() override {delete [] matrix;}

    //! Function printing matrix
    void printData() const override;
    //! Dijkstra shortest path finding
    void dijkstra(int source) const override;
};

#endif //GRAPHS_ADJMATRIX_H
