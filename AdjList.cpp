//
// Created by jszym on 04/04/2022.
//

#include "AdjList.h"

#define SPACING 5

AdjList::AdjList(int start, int end, int weight) {
    head = new node{start, end, nullptr, weight};
}

AdjList::AdjList(const int *array, int edges, int vertices) {
    // Create first element of the list
    head = new node{array[0],array[1], nullptr, array[2]};

    // Add the rest
    for(int edge = 1; edge < edges; edge++) {
        addNode(array[3*edge],array[3*edge+1],array[3*edge+2]);
    }
}

AdjList::~AdjList() {
    while(head->nextNode != nullptr){
        deleteLast();
    }
    delete head;
}

void AdjList::addNode(int start, int end, int weight) {
    node *newNode = new node();
    node *last = head;
    newNode->orgVertex = start;
    newNode->destVertex = end;
    newNode->weight = weight;
    newNode->nextNode = nullptr;

    if (head == nullptr) {
        return;
    }

    while (last->nextNode != nullptr) {
        last = last->nextNode;
    }

    last->nextNode = newNode;
}

void AdjList::deleteLast() {
    node *last = head;
    // Find last element's address
    while (last->nextNode->nextNode != nullptr) {
        last = last->nextNode;
    }
    delete last->nextNode;
    last->nextNode = nullptr;
}

int AdjList::graphSize() const {
    node *last = head;
    int largest = 0;
    // Find largest vertex index
    while (last->nextNode != nullptr) {
        if(last->orgVertex > largest) {
            largest = last->orgVertex;
        }
        if(last->destVertex > largest) {
            largest = last->destVertex;
        }

        last = last->nextNode;
    }
    return largest+1;
}

int AdjList::getEdgeWeight(int a, int b) const {
    node *last = head;
    while (last->nextNode != nullptr){
        last = last->nextNode;
        if((last->orgVertex == a && last->destVertex == b) || (last->orgVertex == b && last->destVertex == a)){
            return last->weight;
        }
    }
    return 0;
}

int AdjList::findPath(int *path, const int *prev, int source, int target) const {
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

int AdjList::minDist(const int *dist, const bool *vis) const {
    int min = INF;
    int minIndex;
    // Number of vertices
    int size = graphSize();

    // Find min dist
    for(int j = 0;j < size; j++){
        if(!vis[j] && dist[j] <= min){
            min = dist[j];
            minIndex = j;
        }
    }

    return minIndex;
}

void AdjList::printResults(const int *prev, const int *dist, int source) const {
    // Number of vertices
    int size = graphSize();
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

void AdjList::printResultsToFile(const int *prev, const int *dist, int source, const std::string &fileName) const {
    // Number of vertices
    int size = graphSize();

    // File handle
    std::ofstream file;
    // Open file
    file.open("../" + fileName, std::ios_base::app);

    // Contains path sequence
    int *path = new int [size];

    // Headline
    file << "From " << size << " adjacency list\n";

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

void AdjList::dijkstra(int source) const {
    // Number of vertices
    int size = graphSize();

    int *dist = new int [size]; // List of distances from source vertex
    int *prev = new int [size]; // List of preceding vertices
    bool *visited = new bool[size]; // List of visited vertices

    // Fill dist with INF and visited with false
    for (int i = 0; i < size; i++) {
        dist[i] = INF;
        visited[i] = false;
        prev[i] = source;
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
            int edgeWeight = getEdgeWeight(u,v);
            // Update distance only if:
            if (!visited[v] && edgeWeight && dist[u] != INF && dist[u] + edgeWeight < dist[v]){
                dist[v] = dist[u] + edgeWeight;
                prev[v] = u;
            }
        }

    }

    // Print results (uncomment to print)
    //printResults(prev,dist,source);
    // Save results
    printResultsToFile(prev,dist,source,"listResults.txt");

    // Delete pointers
    delete [] dist;
    delete [] prev;
    delete [] visited;
}

void AdjList::printData() const {
    std::cout << std::setw(SPACING) << std::fixed << "Org" << std::setw(SPACING) << "Dest" << std::setw(SPACING) << "Wgt" << std::endl;
    node *last = head;
    while (last != nullptr) {
        std::cout << std::setw(SPACING) << std::fixed << last->orgVertex;
        std::cout << std::setw(SPACING) << std::fixed << last->destVertex;
        std::cout << std::setw(SPACING) << std::fixed << last->weight;
        std::cout << std::endl;
        last = last->nextNode;
    }
}
