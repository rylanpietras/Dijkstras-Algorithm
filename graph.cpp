#include <iostream>
#include "graph.hpp"

// Adds a new vertex to the graph given an input label
// New vertex will be given the label as a name 
void AdjList::addVertex(std::string label) {
    std::vector<Vert>::iterator it;
    it = graph.begin();
    while (it != graph.end()) {
        if (it->name == label) {
            std::cout << "\nVertex already exists" << std::endl;
            return;
        }
        it++;
    }

    Vert *temp = new Vert(label);
    graph.push_back(*temp);
}

// Adds a new Edge between two existing vertices on the graph given a start, end, and weight 
// One Neighbor is added to the start and end respectively, and given weight equal to the input 
void AdjList::addEdge(std::string label1, std::string label2, unsigned long weight) {
    // Returns if edge is between same vertex
    if (label1 == label2) {
        std::cout << "\nVertices cannot have edges to themselves" << std::endl;
        return;
    }

    // Preparing itorators for adj list
    std::vector<Vert>::iterator it1;
    std::vector<Vert>::iterator it2;
    it1 = graph.begin();
    it2 = graph.begin();

    // Puts iterators at each Vertex or end
    while (it1 != graph.end() && it1->name != label1) {
        it1++;
    }
    while (it2 != graph.end() && it2->name != label2) {
        it2++;
    }

    // Returns if either Vertex not found (do not exist in graph)
    if (it1 == graph.end() || it2 == graph.end()) {
        std::cout << "\nAt least one vertex does not exist" << std::endl;
        return;
    }

    // Temp variables for iterating over connecting nodes
    Neighbor *temp1 = it1->first;
    Neighbor *temp2 = it2->first;

    // Puts temp variables on neighbors if edge already exists
    while (temp1 != nullptr && temp1->name != label2) {
        temp1 = temp1->next;
    }
    while (temp2 != nullptr && temp2->name != label1) {
        temp2 = temp2->next;
    }

    // If edge already exists, no new edge is added
    if (temp1 != nullptr || temp2 != nullptr) {
        std::cout << "\nEdge already exists" << std::endl;
        return;
    }

    // Creates Neighbor class objects for the new edges
    Neighbor *newEdge1 = new Neighbor(label2, weight);
    Neighbor *newEdge2 = new Neighbor(label1, weight);

    // Places the new Neighbors right next to their respective Vertices
    newEdge1->next = it1->first;
    newEdge2->next = it2->first;
    it1->first = newEdge1;
    it2->first = newEdge2;
}

// Removes an Edge between two already existing vertices on the graph given and start and end label
void AdjList::removeEdge(std::string label, std::string label2) {

    // Used to iterate over vertices in adj list
    std::vector<Vert>::iterator itCheck1 = graph.begin();
    std::vector<Vert>::iterator itCheck2 = graph.begin();

    // Returns if at least one vertex between edge does not exist
    while (itCheck1 != graph.end() && itCheck1->name != label) {
            itCheck1++;
    }
    if (itCheck1 == graph.end()){
            std::cout << "\nAt least one vertex does not exist" << std::endl;
            return;
    }
    while (itCheck2 != graph.end() && itCheck2->name != label2) {
            itCheck2++;
    }
    if (itCheck2 == graph.end()){
            std::cout << "\nAt least one vertex does not exist" << std::endl;
            return;
    }

    // Used to iterate over neighbors
    AdjList::Neighbor *next_neighbor_check = itCheck1->first;

    // Returns if edge does not exist
    while(next_neighbor_check != nullptr){
            if (next_neighbor_check->name == label2){
                break;
            } 
            next_neighbor_check = next_neighbor_check->next;
    }
    if (next_neighbor_check == nullptr){
            return;
    }

    std::vector<Vert>::iterator it;
    it = graph.begin();

    // Look through AdjList for both labels 
    while (it != graph.end()){
        
        // If name of iterator is the first label, delete the connection to the second label 
        if (it->name == label){
            AdjList::Neighbor *next_neighbor = it->first;
            AdjList::Neighbor *prev_neighbor = nullptr;

            // Iterate over the Neighbors to find the connection 
            while(next_neighbor != nullptr){

                // If Neighbor's name matches the other label, get rid of it and re-link other neighbors 
                if (next_neighbor->name == label2){

                    // Check if the Neighbor is the first Neighbor or not before removing and make the proper changes
                    if (next_neighbor == it->first){
                        it->first = next_neighbor->next;
                        delete next_neighbor;
                        break;
                    }

                    prev_neighbor->next = next_neighbor->next; 
                    delete next_neighbor;
                    break;
                }

                // If label has not been found yet, move to next neighbor
                prev_neighbor = next_neighbor;
                next_neighbor = next_neighbor->next;
            }

        // If name of iterator is the second label, delete the connection to the first label 
        } else if (it->name == label2){
            AdjList::Neighbor *next_neighbor = it->first;
            AdjList::Neighbor *prev_neighbor = nullptr;

            // Iterate over the Neighbors to find the connection 
            while(next_neighbor != nullptr){

                // If Neighbor's name matches the other label, get rid of it and re-link other neighbors 
                if (next_neighbor->name == label){
                    if (next_neighbor == it->first){
                        it->first = next_neighbor->next;
                        delete next_neighbor;
                        break;
                    }

                    prev_neighbor->next = next_neighbor->next; 
                    delete next_neighbor;
                    break;
                }

                // If label has not been found yet, move to next neighbor
                prev_neighbor = next_neighbor;
                next_neighbor = next_neighbor->next;
            }
        }
        it++;
    }
}

// Removes a Vertex from the graph and removes any edges related to it provided the name of the Vertex
void AdjList::removeVertex(std::string label) {
    std::vector<Vert>::iterator it;
    it = graph.begin();
    
    // Iterate over AdjList to find any traces of the target Vertex
    while (it != graph.end()) {
        AdjList::Neighbor *next_neighbor = it->first;
        AdjList::Neighbor *prev_neighbor = nullptr;

        // Check if any of the current vertex's neighbors are the target and remove it if so, accounting for if it is first 
        while (next_neighbor != nullptr){

            if (next_neighbor->name == label){
                if (next_neighbor == it->first){ 
                    it->first = next_neighbor->next;
                    delete next_neighbor;
                    break;
                }

                prev_neighbor->next = next_neighbor->next;
                delete next_neighbor;
                break;
            }
            prev_neighbor = next_neighbor;
            next_neighbor = next_neighbor->next;
        }

        // If we have found our target vertex, delete all of its neighbors and then remove it from the graph 
        if (it->name == label){
            while (it->first != nullptr){
                AdjList::Neighbor* temp = it->first; 
                it->first = it->first->next;
                delete temp;
            }
            graph.erase(it);

            // Decrement the iterator once to compensate for the size of the graph decreasing by one 
            it--;
        }

        it++;
    }
}

// Prints out all of the vertices currently in the graph 
// Used for debugging purposes
void AdjList::printAllVert() {
    std::vector<Vert>::iterator it;
    it = graph.begin();

    while (it != graph.end()) {
        std::cout << it->name << std::endl;
        it++;
    }
}

// Prints out the full AdjList at a point in the program, including all vertices and their edges 
// Used for debugging purposes
void AdjList::printAll() {
    if (graph.empty()) {
        std::cout << "Empty graph" << std::endl;
        return;
    }

    std::vector<Vert>::iterator it;
    it = graph.begin();

    while (it != graph.end()) {
        std::cout << it->name << ": ";

        Neighbor *temp = it->first;
        while (temp != nullptr) {
            std::cout << temp->name << " ";
            temp = temp->next;
        }
        std::cout << std::endl;

        it++;
    }
}

// Deletes all edges and vertices in Adjlist without destroying the object
void AdjList::clear() {
    std::vector<Vert>::iterator it;
    it = graph.begin();
    while (it != graph.end()) {
        while (it->first != nullptr) {
            Neighbor *temp = it->first;
            removeEdge(it->name, temp->name);
        }
        it++;
    }
    graph.clear();
}

// Destructor; deletes all edges and vertices in the AdjList
AdjList::~AdjList() {
    std::vector<Vert>::iterator it;
    it = graph.begin();
    while (it != graph.end()) {
        while (it->first != nullptr) {
            Neighbor *temp = it->first;
            removeEdge(it->name, temp->name);
        }
        it++;
    }
    graph.clear();
}

// Comparison operator used to maintain the order of the minHeap
// Compares the pathValue (distance to get to a point using this path) tied to each node to sort them 
bool AdjList::HeapNode::Compare::operator()(const HeapNode &n1, const HeapNode &n2) const
{
    return lessThan ? n1.pathValue < n2.pathValue : n1.pathValue >= n2.pathValue;
}

// Comparison operator used to maintain the order of the minHeap 
// If pointers to HeapNodes are passed in instead of the nodes themselves, evaluate them and redirect to other comparison
bool AdjList::HeapNode::Compare::operator()(const HeapNode *n1, const HeapNode *n2) const
{
  return operator()(*n1, *n2);
}

// Determines the path to get from the Vertex with name = startLabel to the Vertex with name = endLabel
// Returns the amount of distance required to travel there and stores the path inside a provided string vector
unsigned long AdjList::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){

    // If graph does not have any nodes in it, return a -1 for shortest path 
    if (graph.size() == 0){
        return 0;

    // If graph only has one node in it, return a 0 for shortest path 
    } else if (graph.size() == 1){
        return 0;
    }

    // Find the starting vertex in the adjacency list and set the shortest distance to it to 0 
    std::vector<Vert>::iterator curr = graph.begin();
    while (curr->name != startLabel){
        curr++;
    }
    curr->distance = 0;
    curr->hasEstimate = true;
    
    // Create the minHeap  
    HeapQueue<HeapNode*, HeapNode::Compare> minHeap;

    // Loop until we reach the destination (endLabel) 
    while (curr->name != endLabel){
        curr->explored = true;

        // Update distance estimates to all neighbors and put them on the minHeap
        Neighbor* currNeighbor = curr->first;
        unsigned long estimate = curr->distance + currNeighbor->weight;

        while (currNeighbor != nullptr){
            estimate = curr->distance + currNeighbor->weight;

            // Find the neighbor's vertex equivalent in AdjList 
            std::vector<Vert>::iterator neighborVert = graph.begin();
            while(neighborVert->name != currNeighbor->name){
                neighborVert++;
            }
            
            // If neighbor's best estimate is -1 or higher than our estimate, give it our estimate 
            if ((!neighborVert->hasEstimate) || (estimate < neighborVert->distance)){
                neighborVert->distance = estimate; 
                neighborVert->lastVisted = &(*curr);
                neighborVert->hasEstimate = true;
            } 

            // Place estimate, whether best or not, in the minHeap
            HeapNode* newEntry = new HeapNode(currNeighbor->name, estimate);
            minHeap.insert(newEntry);

            currNeighbor = currNeighbor->next;
        }

        // Take the shortest, unexplored distance estimate and name from the minHeap 
        // Find the corresponding vertex, remove it, and set curr to the corresponding vertex
        bool notExplored = false;
        HeapNode* nextNode = minHeap.min();
        std::string nextName = nextNode->name;
        std::vector<Vert>::iterator findIt;

        // Assume that the corresponding vertex has already been explored until proven otherwise
        // Until an unexplored vertex is found, keep pulling from the heap 
        while (!notExplored){
            nextNode = minHeap.min();
            nextName = nextNode->name;
            findIt = graph.begin();

            while (findIt->name != nextName){
                findIt++;
            }
            if(findIt->explored){
                minHeap.removeMin();
                continue;
            } else{
                notExplored = true;
            }
        }

        minHeap.removeMin();
        curr = findIt;
    }

    // If endlabel has been reached, save the current distance estimate in a variable and walk with a pointer
    unsigned long totalDist = curr->distance;
    Vert* walkingPointer = &(*curr);

    // Place the name of every vertex visited into a stack, then reverse it to get the path from start -> end 
    std::vector<std::string> stack;
    while(walkingPointer != nullptr){
        stack.push_back(walkingPointer->name);
        walkingPointer = walkingPointer->lastVisted;
    }

    while(!stack.empty()){
        path.push_back(stack.back());
        stack.pop_back();
    }

    return totalDist;
}