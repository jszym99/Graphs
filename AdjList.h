//
// Created by jszym on 04/04/2022.
//

#ifndef GRAPHS_ADJLIST_H
#include <iostream>
#include <iomanip>
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
    node * head;
public:
    AdjList(int start, int end, int weight);
    void addNode(int start, int end, int weight);
    void printData() const override;
};


#endif //GRAPHS_ADJLIST_H
