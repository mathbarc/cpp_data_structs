#ifndef NODE_H
#define NODE_H

#include "data_interface/comparable_data_interface.hpp"

class Node
{
  public:
    ComparableDataWrapperInterface *data;
    Node *next;

    // Constructor
    Node(ComparableDataWrapperInterface *dataValue) : data(dataValue), next(nullptr)
    {
    }

    // Destructor to manage the data's memory
    ~Node()
    {
        if(data != nullptr)
        {
            delete data;
            data = nullptr;
        }
    }
};

#endif
