// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// WorkIterator.cpp


#include "WorkIterator.h"
#include "WorkComponent.h"
#include "WorkItem.h"

#include <iostream>
#include <vector>

using namespace std;

// === WORK ITERATOR IS ABSTRACT AND HAS NO IMPLEMENTATIONS === //

// === DEPTH FIRST ITERATOR === //

DepthFirstIterator::DepthFirstIterator(WorkComponent* root)
 : position(0)
{
    if (root) {
        root->appendTo(flattened);
    }
}

bool DepthFirstIterator::hasNext()
{
    return (position < flattened.size());
}

WorkComponent* DepthFirstIterator::next()
{
    return flattened[position++];
}

// ==== ACTIVE ONLY ITERATOR ==== //

ActiveOnlyIterator::ActiveOnlyIterator(WorkComponent* root)
 : position(0)
{
    vector<WorkComponent*> all;
    if (root) {
        root->appendTo(all);
    }
    for (WorkComponent* x : all) {
        WorkItem* item = dynamic_cast<WorkItem*>(x);
        if (item != nullptr && item->isActive()) {
            flattened.push_back(x);
        }
    }
}

bool ActiveOnlyIterator::hasNext()
{
   return (position < flattened.size());
}

WorkComponent* ActiveOnlyIterator::next()
{
    return flattened[position++];
}