#include <iostream>
#include <random>
#include "AdjMatrix.h"
#include "AdjList.h"
#include "GraphInterface.h"

void graphToFile(int *graph, int size, const std::string& fileName= ""){
    // File handle
    std::ofstream file;
    // Open file
    file.open("../" + fileName, std::ios_base::app);

    // Utilities for random number generation
    std::random_device rd;
    std::mt19937 gen(123); //Seeded for testing
    std::uniform_int_distribution<> randVer(0, size - 1); // Random vertex

    // Count edges
    int numEdges = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j <= i; j++){
            if(graph[i*size+j] != 0){
                numEdges++;
            }
        }
    }

    int start = randVer(gen);

    std::cout << numEdges << "\t" << size << "\t" << start << "\n\n";
    for(int row = 0; row < size; row++){
        for(int col = row; col < size; col++){
            if(graph[row*size+col] != 0){
                std::cout << row << "\t" << col << "\t" << graph[row*size+col] << std::endl;
            }
        }
    }

}


void printMatrix(int *array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << std::setw(5) << std::fixed << array[i * size + j] << ", ";
        }
        std::cout << std::endl;
    }
}

void genGraph(int *graph,int size, int density = 100) {
    if (density < 0 || density > 100) {
        std::cerr << "Wrong density!" << std::endl;
        return;
    }

    // Range for random distance generation
    int min = 1;
    int max = 10;

    // Utilities for random number generation
    std::random_device rd;
    std::mt19937 gen(123); //Seeded for testing
    std::uniform_int_distribution<> randVer(0, size - 1); // Random vertex
    std::uniform_int_distribution<> randWeight(min, max); // Random weight

    int maxEdge = size * (size - 1) / 2; // Max number of edges
    int numEdge = (int) round(maxEdge * density / 100.0); // Number of edges to create for chosen density
    int remEdge = numEdge; // Number of edges left to create


    // Fill matrix with zeros
    for (int i = 0; i < size * size; i++) {
        graph[i] = 0;
    }

    // Create at one edge for each vertex
    for(int vertex = 0; vertex < size; vertex++){
        // Draw random target vertex
        int randomVertex = randVer(gen);
        // As long as it's not itself
        while(randomVertex == vertex || graph[vertex * size + randomVertex] != 0 || graph[randomVertex * size + vertex] != 0){
            randomVertex = randVer(gen);
        }
        // Assign random weight
        graph[randomVertex * size + vertex] = randWeight(gen);
        graph[vertex * size + randomVertex] = graph[randomVertex * size + vertex];
        // Decrease number of remaining edges
        remEdge--;
        //std::cout << vertex << " " << randomVertex << " " << graph[vertex*size+randomVertex] << std::endl;
    }

    // Generate remaining edges
    while(remEdge > 0){
        int dest = randVer(gen);
        int org = randVer(gen);
        // Destination and origin are different vertices, and this edge doesn't exist yet
        if(dest != org && graph[org * size + dest] == 0 && graph[dest * size + org] == 0){
            graph[dest * size + org] = randWeight(gen);
            graph[org * size + dest] = graph[dest * size + org];
            remEdge--;
        }

    }
}


int main() {
    int size = 6;
    int *arr = new int[size * size]{0, 2, 0, 0, 2, 0,
                                    2, 0, 1, 0, 1, 0,
                                    0, 1, 0, 3, 0, 0,
                                    0, 0, 3, 0, 3, 2,
                                    2, 1, 0, 3, 0, 0,
                                    0, 0, 0, 2, 0, 0};

    //AdjMatrix Mat(arr, 6);
    //Mat.printData();

    /*AdjList list{1, 2, 2};
    list.addNode(1, 5, 2);
    list.printData();*/

    //Mat.dijkstra(0);

    delete[] arr;

    int graphSize = 8;
    int *newGraph = new int[graphSize * graphSize];
    genGraph(newGraph, graphSize, 50);
    printMatrix(newGraph, graphSize);
    graphToFile(newGraph, graphSize);
    delete [] newGraph;
}
