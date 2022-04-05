//
// Created by jszym on 04/04/2022.
//

#include "AdjList.h"

#define SPACING 5

AdjList::AdjList(int start, int end, int weight) {
    node *newNode = new node{start, end, nullptr, weight};
    head = newNode;
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
