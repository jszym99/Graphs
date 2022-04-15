//
// Created by jszym on 15/04/2022.
//

#ifndef GRAPHS_UTILITIES_H
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
#define GRAPHS_UTILITIES_H

#define MAX_WEIGHT 10

//! Function appends graph to a file
void graphToFile(int *graph, int size, const std::string &fileName);
//! Function prints matrix stored as a 1D array
void printMatrix(int *array, int size);
//! Function generates random graph stored as a 1D array
void genGraph(int *graph, int size, int density = 100);
//! Function generates file with data sets
void genDataFile();

#endif //GRAPHS_UTILITIES_H
