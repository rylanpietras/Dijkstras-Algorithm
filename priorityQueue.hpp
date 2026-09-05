#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <iostream>
#include <vector>
#include <string>

class queueNode {
private:
    std::string name;
    unsigned long pathValue;

    friend class priorityQueue;
};

class priorityQueue {
private:
    std::vector<queueNode> minQueue;

public:
    void addElement(std::string str, unsigned long value);

    void removeFront();

    std::string getFrontStr();

    unsigned long getFrontVal();
};

#endif