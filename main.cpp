#include <iostream>
#include "graph.hpp"

int main() {
    // AdjList g1;

    // g1.addVertex("v1");
    // g1.addVertex("v2");
    // g1.addVertex("v3");
    // g1.addVertex("v4");

    // g1.addEdge("v1", "v2", 1);
    // g1.addEdge("v1", "v3", 2);
    // g1.addEdge("v2", "v3", 3);
    // g1.addEdge("v3", "v4", 4);

    // // g1.printAll();
    // // std::cout << std::endl;

    // // g1.removeEdge("v1", "v2");

    // g1.printAll();
    // std::cout << std::endl;

    // // g1.~AdjList();

    // g1.printAll();
    // std::cout << std::endl;

    // // g1.removeVertex("v3");

    // // g1.printAll();
    // // std::cout << std::endl;

    // // g1.removeVertex("v1");

    // // g1.printAll();
    // // std::cout << std::endl;

    // std::vector<std::string> vertices1 = {"1","2","3","4","5","6"};
    // std::vector<std::tuple<std::string, std::string, unsigned long>> edges1 = {{"1","2",7}, {"1","3",9}, {"1","6",14}, {"2","3",10}, {"2","4",15}, {"3","4",11}, {"3","6",2}, {"4","5",6}, {"5", "6", 9}};

    // g1.addVertex("1");
    // g1.addVertex("2");
    // g1.addVertex("3");
    // g1.addVertex("4");
    // g1.addVertex("5");
    // g1.addVertex("6");

    // g1.addEdge("1", "2", 7);
    // g1.addEdge("1", "3", 9);
    // g1.addEdge("1", "6", 14);
    // g1.addEdge("2", "3", 10);
    // g1.addEdge("2", "4", 15);
    // g1.addEdge("3", "4", 11);
    // g1.addEdge("3", "6", 2);
    // g1.addEdge("4", "5", 6);
    // g1.addEdge("5", "6", 9);

    // std::vector<std::string> path;
    // unsigned long shortestDist = g1.shortestPath("1", "5", path);
    // std::vector<std::string>::iterator pathIt = path.begin();
    // std::cout << "Shortest path to end is: " << shortestDist << "\n";
    // while(pathIt != path.end()){
    //     std::cout << *pathIt << " ";
    //     pathIt++;
    // }

    // TESTING ABOVE

    AdjList g; // graph object
    bool loop = true; // bool to keep program running until user terminates

    // Loop to keep accepting user input until program terminated or algorithm executed
    while (loop) {
        // Output for describing user inputs
        std::cout 
        << "\nInput v to add vertex to graph\n" 
        << "Input e to add edge between two vertices\n" 
        << "Input r to remove a vertex from the graph\n" 
        << "Input t to remove an edge between two vertices\n"
        << "Input c to clear existing graph\n" 
        << "Input g to load example graph from assignment\n" 
        << "Input p to print all vertices and edges in graph\n" 
        << "Input d to use Dijkstra's Algorithm to find the shortest path and distance between two vertices\n" 
        << "Input s to stop program\n" 
        << std::endl;

        // Initializing variebles for user input
        std::cout << "Input: ";
        char userChar;
        std::cin >> userChar;
        std::string userStr1, userStr2;
        unsigned long userNum;
        std::vector<std::string> shortestPath;

        // Switch Case to continuously accept user input until algorithm executed or program terminated
        switch (userChar) {
            // Adds a vertex to the graph
            case 'v':
                std::cout << "Enter name of vertex to add: ";
                std::cin >> userStr1;

                g.addVertex(userStr1);

                break;

            // Adds an edge to the graph
            case 'e':
                std::cout << "Enter name of first connecting vertex: ";
                std::cin >> userStr1;

                std::cout << "Enter name of second connecting vertex: ";
                std::cin >> userStr2;

                std::cout << "Enter weight of edge: ";
                std::cin >> userNum;

                g.addEdge(userStr1, userStr2, userNum);

                break;

            // Removes a vertex from the graph
            case 'r':
                std::cout << "Enter name of vertex to remove: ";
                std::cin >> userStr1;

                g.removeVertex(userStr1);

                break;

            // Removes an edge from the graph
            case 't':
                std::cout << "Enter name of first connecting vertex: ";
                std::cin >> userStr1;

                std::cout << "Enter name of second connecting vertex: ";
                std::cin >> userStr2;

                g.removeEdge(userStr1, userStr2);

                break;

            // Deletes all vertices and edges of existing graph
            case 'c':
                g.clear();

                break;

            // Loads the example graph featured in the assignment description
            case 'g':
                std::cout << "Load graph 1 or graph 2? (input 1 or 2): ";
                std::cin >> userChar;

                if (userChar == '1') {
                    g.clear();

                    g.addVertex("1");
                    g.addVertex("2");
                    g.addVertex("3");
                    g.addVertex("4");
                    g.addVertex("5");
                    g.addVertex("6");

                    g.addEdge("1", "2", 7);
                    g.addEdge("1", "3", 9);
                    g.addEdge("1", "6", 14);
                    g.addEdge("2", "3", 10);
                    g.addEdge("2", "4", 15);
                    g.addEdge("3", "4", 11);
                    g.addEdge("3", "6", 2);
                    g.addEdge("4", "5", 6);
                    g.addEdge("5", "6", 9);
                }
                else if (userChar == '2') {
                    g.clear();

                    g.addVertex("A");
                    g.addVertex("B");
                    g.addVertex("C");
                    g.addVertex("D");
                    g.addVertex("E");
                    g.addVertex("F");
                    g.addVertex("G");
                    g.addVertex("H");

                    g.addEdge("A", "B", 1);
                    g.addEdge("A", "C", 10);
                    g.addEdge("B", "E", 3);
                    g.addEdge("C", "D", 7);
                    g.addEdge("D", "E", 2);
                    g.addEdge("D", "F", 3);
                    g.addEdge("D", "G", 8);
                    g.addEdge("F", "G", 2);
                    g.addEdge("G", "H", 1);
                }
                else {
                    std::cout << "Invalid input" << std::endl;
                }

                break;

            // Prints the entire graph in an adjacency list form
            case 'p':
                std::cout << std::endl;
                g.printAll();

                break;

            // Executes Dijkstra's Algorithm and terminates program
            case 'd':
                std::cout << "Enter starting vertex: ";
                std::cin >> userStr1;

                std::cout << "Enter target vertex: ";
                std::cin >> userStr2;   

                std::cout << std::endl;

                userNum = g.shortestPath(userStr1, userStr2, shortestPath);

                std::cout << "The shortest path from " << userStr1 << " to " << userStr2 << " is: ";
                for (std::string str : shortestPath) {
                    std::cout << str << " ";
                }
                std::cout << std::endl;

                std::cout << "This is the length of this path: " << userNum << std::endl;

                std::cout << std::endl;

                loop = false;
                break;

            // Terminates program
            case 's':
                loop = false;
                break;

            // Informs user of invalid input (any input not specified)
            default:
                std::cout << "Invalid input" << std::endl;
                break;

        }
    }

    return 0;
}