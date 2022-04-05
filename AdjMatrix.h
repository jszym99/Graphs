//
// Created by jszym on 04/04/2022.
//

#ifndef GRAPHS_ADJMATRIX_H
#include <iostream>
#include <iomanip>
#include "GraphInterface.h"
#define GRAPHS_ADJMATRIX_H

class AdjMatrix : public GraphInterface {
private:
    int *matrix;
    int size;
public:
    AdjMatrix(int *array, int arraySize);

    void printData() const override;

};

#endif //GRAPHS_ADJMATRIX_H
