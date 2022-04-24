#include <iostream>
#include <chrono>
#include "AdjMatrix.h"
#include "AdjList.h"
#include "Utilities.h"


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

    unsigned int matrixMemorySize = 0;
    unsigned int listMemorySize = 0;
    unsigned int instances = 1;
    unsigned int matrixTime = 0;
    unsigned int listTime = 0;
    //auto matrixTime;
    //auto listTime;

    // Data file generation
    //genDataFile();

    std::string fileName = "data.txt";

    // File handle
    std::ifstream file;
    // Open file
    file.open("../" + fileName);
    if (!file) {
        std::cerr << "Error: file couldn't be opened" << std::endl;
        return 0;
    }

    std::string line; // String for current line
    int num; // Temporary variable for numbers

    int header[3]; // Temporarily holds header info (edges, vertices, start vertex)

    while (std::getline(file, line)) {
        int headCount = 0; // Increments for header

        // Line contains data
        if (!line.empty()) {
            std::stringstream ss(line);
            // Read header from string skipping whitespaces
            while (ss >> num) {
                header[headCount++] = num;
            }
            //std::cout << header[0] << " " << header[1] << " " << header[2] << " " << std::endl;

            int *array = new int[3 * header[0]];
            int count = 0;

            // Read data for current data set
            for (int node = 0; node < header[0]; node++) {
                // Read next line
                std::getline(file, line);
                // Line contains data
                if (!line.empty()) {
                    std::stringstream ss2(line);
                    while (ss2 >> num) {
                        array[count++] = num;
                        //std::cout << num << " ";
                    }
                    //std::cout << std::endl;
                } else
                    node--;

                //std::cout << array[3*node+0] << " " << array[3*node+1] << " " << array[3*node+2] << " ";
            }
            //std::cout << std::endl;

            // Create adjacency matrix
            AdjMatrix matrixData(array, header[0], header[1]);
            AdjList listData(array, header[0], header[1]);
            //matrixData.printData();
            //listData.printData();
            //std::cout << std::endl;

            // Start measuring time for matrix
            auto start = std::chrono::high_resolution_clock::now();
            matrixData.dijkstra(header[2]); // Find paths
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            matrixTime += duration.count(); // Add time

            // Start measuring time for list
            start = std::chrono::high_resolution_clock::now();
            listData.dijkstra(header[2]); //Find paths
            stop = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            listTime += duration.count(); // Add time

            // Calculate memory usage
            matrixMemorySize = sizeof(AdjMatrix) + sizeof(int[header[1] * header[1]]);
            listMemorySize = sizeof(AdjList) + header[0] * sizeof(node);

            //std::cout << "Size: " << listData.graphSize() << std::endl;

            // Free memory
            delete[] array;
            if (instances == 1) {
                std::cout  << "M size,\t"  << "L size,\t" << "M time,\t" << "L time,\t" << std::endl;
            }
            if (instances % 100 == 0) {
                // Printing for testing
                //std::cout << "Size of AdjMatrix object: " << matrixMemorySize << "\tSize of AdjList object: " << listMemorySize << std::endl;
                //std::cout << "Matrix average time: " << matrixTime/100 << "\tList average time: " << listTime/100 << std::endl;

                // Printing excel-formated data
                std::cout << matrixMemorySize << ",\t" << listMemorySize << ",\t"
                          << matrixTime / 100 << ",\t" << listTime / 100 << ",\t" << std::endl;

                // Clear time variables
                matrixTime = 0;
                listTime = 0;
            }
            instances++;
        }
    }

    file.close();

}
