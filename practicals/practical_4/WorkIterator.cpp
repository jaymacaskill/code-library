// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// WorkIterator.cpp

#ifndef WORKITERATOR_CPP
#define WORKITERATOR_CPP

#include "WorkIterator.h"
#include "WorkComponent.h"

#include <iostream>
#include <vector>

using namespace std;

// === WORK ITERATOR IS ABSTRACT AND HAS NO IMPLEMENTATIONS === //

// === DEPTH FIRST ITERATOR === //

DepthFirstIterator::DepthFirstIterator(WorkComponent* root)
{
    // TODO
    throw "Not yet implemented";
}

bool DepthFirstIterator::hasNext()
{
    // TODO
    throw "Not yet implemented";
}

WorkComponent* WorkIterator::next()
{
    // TODO
    throw "Not yet implemented";
}

// ==== ACTIVE ONLY ITERATOR ==== //

ActiveOnlyIterator::ActiveOnlyIterator(WorkComponent* root)
{
    // TODO
    throw "Not yet implemented";
}

bool ActiveOnlyIterator::hasNext()
{
    // TODO
    throw "Not yet implemented";
}

WorkComponent* ActiveOnlyIterator::next()
{
    // TODO
    throw "Not yet implemented";
}

#endif // WORKITERATOR_CPP