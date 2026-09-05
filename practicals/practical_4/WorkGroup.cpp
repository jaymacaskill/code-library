// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// WorkGroup.cpp

#ifndef WORKGROUP_CPP
#define WORKGROUP_CPP

#include "WorkGroup.h"
#include "WorkComponent.h"
#include "WorkIterator.h"

#include <iostream>
#include <vector>

using namespace std;

class WorkComponent;
class WorkIterator;

WorkGroup::WorkGroup(const string& name)
{
    this->name = name;
}

WorkGroup::~WorkGroup()
{
    // TODO
    throw "Not yet implemented";
}

string WorkGroup::getName() const
{
    return this->name;
}

void WorkGroup::display(int depth = 0) const
{
    // TODO
    throw "Not yet implemented";
}

void WorkGroup::execute()
{
    // TODO
    throw "Not yet implemented";
}

WorkIterator* WorkGroup::createIterator()
{
    // TODO
    throw "Not yet implemented";
}

void WorkGroup::add(WorkComponent* child)
{
    // TODO
    throw "Not yet implemented";
}

void WorkGroup::remove(WorkComponent* child)
{
    // TODO
    throw "Not yet implemented";
}

void WorkGroup::appendTo(vector<WorkComponent*>& out)
{
    out.push_back(this);
    for (size_t i = 0; i < children.size(); i ++)
        children[i]->appendTo(out);
}

#endif // WORKGROUP_CPP