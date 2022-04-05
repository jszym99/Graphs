//
// Created by jszym on 04/04/2022.
//

#include "AdjMatrix.h"

#define SPACING 5

AdjMatrix::AdjMatrix(int *array, int arraySize) {
    int *newMatrix = new int[arraySize * arraySize];
    for (int i = 0; i < arraySize; i++) {
        for (int j = 0; j < arraySize; j++) {
            newMatrix[i * arraySize + j] = array[i * arraySize + j];
        }
    }

    size = arraySize;
    matrix = newMatrix;
}

void AdjMatrix::printData() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i * size + j] == INF)
                std::cout << std::setw(SPACING) << std::fixed << "INF";
            else
                std::cout << std::setw(SPACING) << std::fixed << matrix[i * size + j];
        }
        std::cout << std::endl;
    }
}