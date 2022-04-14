//
// Created by jszym on 04/04/2022.
//

#include "AdjMatrix.h"

#define SPACING 5

//! Constructor
AdjMatrix::AdjMatrix(const int *array, int arraySize) {
    size = arraySize;
    matrix = new int[arraySize * arraySize];
    for (int i = 0; i < arraySize; i++) {
        for (int j = 0; j < arraySize; j++) {
            matrix[i * arraySize + j] = array[i * arraySize + j];
        }
    }
}

//! Function finding path by reverse iteration
int AdjMatrix::findPath(int *path, const int * prev, int source, int target) {
    int count = 0;
    int u = target;
    path[count++] = target;
    while(prev[u] != source){
        u = prev[u];
        path[count++] = u;
    }
    path[count] = source;
    return count;
}


//! Function finding index of nearest vertex
int AdjMatrix::minDist(const int *dist, const bool *vis) const
{
    int min = INF;
    int minIndex;

    // Find min dist
    for(int j = 0;j < size; j++){
        if(!vis[j] && dist[j] <= min){
            min = dist[j];
            minIndex = j;
        }
    }

    return minIndex;
}

//! Function prints results of dijkstra's shortest path finding
void AdjMatrix::printResults(const int * prev, const int * dist, int source) const {
    // Contains path sequence
    int *path = new int [size];

    // Print for every vertex
    for(int i = 0; i < size; i++) {
        //Don't print for source (source to source)
        if(i != source) {
            std::cout << "Start: " << source << " End: " << i << " Distance: " <<  dist[i] << "\nPath: ";
            // Find path
            int length = findPath(path, prev, source, i);
            // Print path
            for (int j = length; j >= 0; j--) {
                std::cout << path[j];
                if (j > 0)
                    std::cout << " -> ";
            }
            std::cout << std::endl;
        }
    }
    // Delete pointer
    delete [] path;
}

//! Function prints results of dijkstra's shortest path finding to a file
void AdjMatrix::printResultsToFile(const int *prev, const int *dist, int source, const std::string& fileName) const {

    // File handle
    std::ofstream file;
    // Open file
    file.open("../" + fileName, std::ios_base::app);

    // Contains path sequence
    int *path = new int [size];

    // Headline
    file << "From " << size << "x" << size << " adjacency matrix\n";

    // Print for every vertex
    for(int i = 0; i < size; i++) {
        //Don't print for source (source to source)
        if(i != source) {
            file << "Start: " << source << " End: " << i << " Distance: " <<  dist[i] << "\nPath: ";
            // Find path
            int length = findPath(path, prev, source, i);
            // Print path
            for (int j = length; j >= 0; j--) {
                file << path[j];
                if (j > 0)
                    file << " -> ";
            }
            file << "\n";
        }
    }
    file << "\n";
    // Close file
    file.close();
    // Delete pointer
    delete [] path;
}

//! Dijkstra shortest path finding
void AdjMatrix::dijkstra(int source) {
    int *dist = new int [size]; // List containing distances from source vertex
    int *prev = new int [size];
    bool *visited = new bool[size]; // List containing information about visited vertices

    // Fill dist with INF and visited with false
    for (int i = 0; i < size; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    // Assign distance to source (always 0)
    dist[source] = 0;
    // Assign previous vertex index (first is always source)
    prev[0] = source;

    for(int i = 0; i < size - 1; i++){

        // Nearest unvisited vertex index
        int u = minDist(dist, visited);

        // Change status to visited
        visited[u] = true;

        // Update "distance" and "previous" values for the chosen vertex
        for(int v = 0; v < size; v++){
            // Update distance only if:
            if (!visited[v] && matrix[u * size + v] && dist[u] != INF && dist[u] + matrix[u * size + v] < dist[v]){
                dist[v] = dist[u] + matrix[u * size + v];
                prev[v] = u;
            }
        }

    }

    // Print results
    printResults(prev,dist,source);
    // Save results
    printResultsToFile(prev,dist,source,"results.txt");

    // Delete pointers
    delete [] dist;
    delete [] prev;
    delete [] visited;
}

//! Function printing matrix
void AdjMatrix::printData() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
                std::cout << std::setw(SPACING) << std::fixed << matrix[i * size + j];
        }
        std::cout << std::endl;
    }
}