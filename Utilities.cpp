//
// Created by jszym on 15/04/2022.
//

#include "Utilities.h"

//! Function appends graph to a file
void graphToFile(int *graph, int size, const std::string &fileName) {
    // File handle
    std::ofstream file;
    // Open file
    file.open("../" + fileName, std::ios_base::app);

    // Utilities for random number generation
    std::random_device rd;
    //std::mt19937 gen(123); //Seeded for testing
    std::mt19937 gen(rd()); // Not seeded
    std::uniform_int_distribution<> randVer(0, size - 1); // Random vertex

    // Count edges
    int numEdges = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            if (graph[i * size + j] != 0) {
                numEdges++;
            }
        }
    }

    // Assign random start vertex
    int start = randVer(gen);

    file << numEdges << "\t\t" << size << "\t\t" << start << "\n\n";
    for (int row = 0; row < size; row++) {
        for (int col = row; col < size; col++) {
            if (graph[row * size + col] != 0) {
                file << row << "\t" << col << "\t" << graph[row * size + col] << std::endl;
            }
        }
    }
    file << "\n\n";
}

//! Function prints matrix stored as a 1D array
void printMatrix(int *array, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << std::setw(5) << std::fixed << array[i * size + j] << ", ";
        }
        std::cout << std::endl;
    }
}

//! Function generates random graph stored as a 1D array
void genGraph(int *graph, int size, int density) {
    if (density < 0 || density > 100) {
        std::cerr << "Wrong density!" << std::endl;
        return;
    }

    // Range for random weight generation
    int min = 1;
    int max = MAX_WEIGHT;

    // Utilities for random number generation
    std::random_device rd;
    //std::mt19937 gen(123); // Seeded for testing
    std::mt19937 gen(rd()); // Not seeded
    std::uniform_int_distribution<> randVer(0, size - 1); // Random vertex
    std::uniform_int_distribution<> randWeight(min, max); // Random weight

    int maxEdge = size * (size - 1) / 2; // Max number of edges
    int numEdge = (int) round(maxEdge * density / 100.0); // Number of edges to create for chosen density
    int remEdge = numEdge; // Number of edges left to create

    bool connectedVertex[size];

    // Initialize list with false
    for(int i = 1; i < size;i++){
        connectedVertex[i] = false;
    }
    connectedVertex[0] = true;

    // Fill matrix with zeros
    for (int i = 0; i < size * size; i++) {
        graph[i] = 0;
    }

    // Create at one edge for each vertex
    for (int vertex = 0; vertex < size; vertex++) {
        // Draw random target vertex
        int randomVertex = randVer(gen);
        // As long as it's not itself
        while (randomVertex == vertex || graph[vertex * size + randomVertex] != 0 || (!connectedVertex[randomVertex] && !connectedVertex[vertex])) {
            randomVertex = randVer(gen);
        }
        // Assign random weight
        graph[randomVertex * size + vertex] = randWeight(gen);
        graph[vertex * size + randomVertex] = graph[randomVertex * size + vertex];
        connectedVertex[randomVertex] = true;
        // Decrease number of remaining edges
        remEdge--;
    }

    // Generate remaining edges
    while (remEdge > 0) {
        int dest = randVer(gen);
        int org = randVer(gen);
        // Destination and origin are different vertices, and this edge doesn't exist yet
        if (dest != org && graph[org * size + dest] == 0 && graph[dest * size + org] == 0) {
            graph[dest * size + org] = randWeight(gen);
            graph[org * size + dest] = graph[dest * size + org];
            remEdge--;
        }
    }
}

//! Function generates file with data sets
void genDataFile() {
    std::string fileName = "data.txt"; // Name of data file
    int graphSize[] = {16, 24, 32, 40, 48}; // Numbers of vertices in graph
    int graphDensity[] = {25, 50, 75, 100}; // Graph densities

    int nElements = 0;

    // For each graph graphSize
    for (int size: graphSize) {
        // Allocate space for a graph
        int *graph = new int[size * size];
        std::cout << "Size: " << size << std::endl;

        // For each graph density
        for (int density: graphDensity) {
            std::cout << "Density: " << density << std::endl;
            // Generate 100 graphs
            for (int series = 0; series < 100; series++) {
                // Generate new random graph
                genGraph(graph, size, density);
                // Append graph to file
                graphToFile(graph, size, fileName);
                nElements++;
            }
        }
        delete[] graph;
    }
    std::cout << "Number of generated instances: " << nElements << std::endl;
}

