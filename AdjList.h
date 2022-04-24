//
// Created by jszym on 04/04/2022.
//

#ifndef GRAPHS_ADJLIST_H
#include "GraphInterface.h"
#define GRAPHS_ADJLIST_H

struct node{
    int orgVertex; // Origin vertex
    int destVertex; // Destination vertex
    node * nextNode; // Next node address
    int weight; // Weight of the edge
};

class AdjList : public GraphInterface {
private:
    node * head; // Pointer to the first element of the linked list

    //! Function finding path by reverse iteration
    int findPath(int * path, const int * prev, int source, int target) const override;
    //! Function finding index of nearest vertex
    int minDist(const int *dist, const bool *vis) const override;
    //! Function prints results of dijkstra's shortest path finding
    void printResults(const int * prev, const int * dist, int source) const override;
    //! Function prints results of dijkstra's shortest path finding to a file
    void printResultsToFile(const int * prev, const int * dist, int source, const std::string& fileName) const override;
public:
    AdjList(int start, int end, int weight);
    AdjList(const int *array, int edges, int vertices);
    //! Destructor freeing allocated memory
    ~AdjList() override;
    //! Function adds node to the object
    void addNode(int start, int end, int weight);
    //! Function deletes last node from the list
    void deleteLast();
    //! Function returns number of vertices in the graph
    [[nodiscard]] int graphSize() const;
    //! Function returns weight of an edge between vertices a and b
    [[nodiscard]] int getEdgeWeight(int a, int b) const;
    //! Function printing matrix
    void printData() const override;
    //! Dijkstra shortest path finding
    void dijkstra(int source) const override;
};


#endif //GRAPHS_ADJLIST_H
