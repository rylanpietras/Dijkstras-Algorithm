#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "graphbase.hpp"
#include "HeapQueue.hpp"

class AdjList {
private:
    // Class to describe edge between between vertex stored in name from class Neighbor and vertex stored in name from class Vert
    class Neighbor { 
    public:
        std::string name;
        int weight;
        Neighbor *next = nullptr;
        Neighbor(std::string name, int weight) { this->name = name, this->weight = weight; }
    };
    // Class to describe a vertex in graph
    class Vert { 
    public:
        Vert(std::string str) { name = str; }
        std::string name;
        bool hasEstimate = false;
        bool explored = false;
        unsigned long distance;
        Vert *lastVisted = nullptr;
        Neighbor* first = nullptr;
    };
    // Node used in heap for priority queue
    class HeapNode {
        public:
        HeapNode(std::string name, unsigned long pathValue) { this->name = name, this->pathValue = pathValue; }
        std::string name; 
        unsigned long pathValue;

        // Used to compare between two HeapNodes
        class Compare {
            public:
            Compare(bool lessThan = true) : lessThan(lessThan) {};
            bool operator()(const HeapNode &n1, const HeapNode &n2) const;
            bool operator()(const HeapNode *n1, const HeapNode *n2) const;
            private:
            bool lessThan;
        };

    };

    // Adjacency list used to represent graph
    std::vector<Vert> graph;

public:
    // Adds vertex to the graph
    void addVertex(std::string label);

    // Removes vertex from the graph
    void removeVertex(std::string label);

    // Adds an edge to the graph between two vertices
    void addEdge(std::string label1, std::string label2, unsigned long weight);

    // Removes an edge from the graph between two vertices
    void removeEdge(std::string label1, std::string label2);

    // Uses Dijkstra's Algorithm to find the shortest path and distance between two vertices in the graph
    unsigned long shortestPath(std::string startLabel, std::string endLabel,
    std::vector<std::string> &path);

    // Prints all vertices
    void printAllVert();

    // Prints all vertices and the respective vertices that each are connected to
    void printAll();

    // Clears the adjacency list
    void clear();

    // Destructor that clears adjacency list
    ~AdjList();
};

#endif