#include "priorityQueue.hpp"

void priorityQueue::addElement(std::string str, unsigned long value) {
    std::vector<queueNode>::iterator it;
    it = minQueue.begin();

    if (!minQueue.empty()) {
        while ((it != minQueue.end()) && (value > it->pathValue)) {
            it++;
        }
    }

    queueNode *newNode = new queueNode;
    newNode->name = str;
    newNode->pathValue = value;
    minQueue.emplace(it, *newNode);
}

void priorityQueue::removeFront() {
    if (minQueue.empty()) 
        return;

    minQueue.erase(minQueue.begin());
}

std::string priorityQueue::getFrontStr() {
    return (minQueue.front()).name;
}

unsigned long priorityQueue::getFrontVal() {
    return (minQueue.front()).pathValue;    
}