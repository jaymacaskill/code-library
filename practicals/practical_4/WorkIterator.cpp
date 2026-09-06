// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 6 September 2026

// WorkIterator.cpp

#ifndef WORKITERATOR_CPP
#define WORKITERATOR_CPP

#include "WorkIterator.h"
#include "WorkComponent.h"
#include "WorkItem.h"

#include <iostream>
#include <vector>

using namespace std;

// === WORK ITERATOR IS ABSTRACT AND HAS NO IMPLEMENTATIONS === //

// === DEPTH FIRST ITERATOR === //

DepthFirstIterator::DepthFirstIterator(WorkComponent* root)
{
    position = 0;
    if(root)
        root->appendTo(flattened);
}

bool DepthFirstIterator::hasNext()
{
    return position < flattened.size();
}

WorkComponent* DepthFirstIterator::next()
{
    if (!hasNext())
        return nullptr;

    return flattened[position ++];
}

// ==== ACTIVE ONLY ITERATOR ==== //

ActiveOnlyIterator::ActiveOnlyIterator(WorkComponent* root)
{
    position = 0;
    if (!root) return;

    vector<WorkComponent*> temp;
    root->appendTo(temp);

    for (size_t i = 0; i < temp.size(); i ++)
    {
        WorkItem* item = dynamic_cast<WorkItem*>(temp[i]);

        if (item && item->isActive())
            flattened.push_back(item);
    }
}

bool ActiveOnlyIterator::hasNext()
{
    return position < flattened.size();
}

WorkComponent* ActiveOnlyIterator::next()
{
    if (!hasNext())
        return nullptr;

    return flattened[position ++];
}

#endif // WORKITERATOR_CPP