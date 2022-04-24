//
// Created by jszym on 04/04/2022.
//

#ifndef GRAPHS_GRAPHINTERFACE_H
#include <iostream>
#include <iomanip>
#include <fstream>
#define INF INT_MAX
#define GRAPHS_GRAPHINTERFACE_H


class GraphInterface {
private:
    //! Function finding path by reverse iteration
    virtual int findPath(int * path, const int * prev, int source, int target) const = 0;
    //! Function finding index of nearest vertex
    virtual int minDist(const int *dist, const bool *vis) const = 0;
    //! Function prints results of dijkstra's shortest path finding
    virtual void printResults(const int * prev, const int * dist, int source) const {}
    //! Function prints results of dijkstra's shortest path finding to a file
    virtual void printResultsToFile(const int * prev, const int * dist, int source, const std::string& fileName) const {}
public:
    virtual ~GraphInterface () = default;
    //! Function printing matrix
    virtual void printData() const {}
    //! Dijkstra shortest path finding
    virtual void dijkstra(int source) const {}
};


#endif //GRAPHS_GRAPHINTERFACE_H
