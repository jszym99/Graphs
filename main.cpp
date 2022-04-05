#include <iostream>
#include "AdjMatrix.h"
#include "AdjList.h"
#include "GraphInterface.h"

int main() {
    int size = 6;
    int *arr = new int [size*size] {0,2,INF,INF,2,INF,
                                    2,0,1,INF,1,INF,
                                    INF,1,0,3,INF,INF,
                                    INF,INF,3,0,3,2,
                                    2,1,INF,3,0,INF,
                                    INF,INF,INF,2,INF,0};

    AdjMatrix Mat(arr, 6);
    Mat.printData();

    AdjList list{1, 2, 2};
    list.addNode(1, 5, 2);
    list.printData();

    delete arr;

}
