// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// WorkComponent.h

// has no matching .cpp, no implementations needed

#ifndef WORKCOMPONENT_H
#define WORKCOMPONENT_H

#include "WorkIterator.h"

#include <iostream>
#include <vector>

using namespace std;

class WorkIterator;

/**
 * @brief Common interface for single work items and groups of them
 * This is the Component in the Composite pattern
 */
class WorkComponent
{
    public:

        /**
         * @brief Virtual destructor for the WorkComponent class
         */
        virtual ~WorkComponent() { };

        /**
         * @brief Getter for the name attribute
         * @return The name of the object
         */
        virtual string getName() const = 0;

        /**
         * @brief Prints the item and everything inside it to see the hierarchy
         * @param depth How deeply nested the object is, used to indent the output to create a readable tree
         */
        virtual void display(int depth = 0) const = 0;

        /**
         * @brief State dependent for each task, for a group it calls execute on its children
         * Makes the object do what is needed, each object does work differently
         */
        virtual void execute() = 0;

        /**
         * @brief The Iterator factory method
         * @return An iterator
         */
        virtual WorkIterator* createIterator() = 0;

        /**
         * @brief Adds a child to the children vector of a WorkGroup object
         * @param child The child to be added
         */
        virtual void add(WorkComponent* child) { }

        /**
         * @brief Removes a child from the children vector of a WorkGroup object
         * @param child The child to be removed
         */
        virtual void remove(WorkComponent* child) { }

        /**
         * @brief Used by iterators to flatten the tree
         * Avoids iterators using the private children vector directly
         * @param out The vector which this needs to be pushed into
         * We use & to avoid copying over a vector, in the event it gets large
         */
        virtual void appendTo(vector<WorkComponent*> &out) = 0;
};

#endif // WORKCOMPONENT_H