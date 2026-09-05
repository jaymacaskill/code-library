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
    for (size_t i = 0; i < children.size(); i ++)
        delete children[i];
    children.clear();
}

string WorkGroup::getName() const
{
    return this->name;
}

void WorkGroup::display(int depth = 0) const
{
    for (int j = 0; j < depth; j ++)
    {
        cout << "  ";
    }
    cout << "[Group] " << name << endl;

    for (size_t j = 0; j < children.size(); j ++)
    {
        children[j]->display(depth + 1);
    }
}

void WorkGroup::execute()
{
    for (size_t i = 0; i < children.size(); i ++)
        children[i]->execute();
}

WorkIterator* WorkGroup::createIterator()
{
    return new DepthFirstIterator(this);
}

WorkIterator* WorkGroup::createActiveIterator()
{
    return new ActiveOnlyIterator(this);
}

void WorkGroup::add(WorkComponent* child)
{
    for (size_t i = 0; i < children.size(); i ++)
    {
        if (children[i] == child)
        {
            cout << "⚠️ This WorkComponent has already been added to this WorkGroup!\n";
            return;
        }
    }
    children.push_back(child);
    cout << "✅ WorkComponent added to WorkGroup successfully!\n";
}

WorkComponent* WorkGroup::remove(WorkComponent* child)
{
    for (size_t i = 0; i < children.size(); i ++)
    {
        if (children[i] == child)
        {
            WorkComponent* removed = children[i];
            children.erase(children.begin() + i);
            cout << "✅ WorkComponent removed from WorkGroup successfully!\n";
            return removed; /* here we return the removed child to prevent
            orphaning and allow restoration of independent living */
        }
    }
    cout << "⚠️ This WorkComponent could not be found in this WorkGroup!\n";
    return nullptr;
}

void WorkGroup::appendTo(vector<WorkComponent*>& out)
{
    out.push_back(this);
    for (size_t i = 0; i < children.size(); i ++)
        children[i]->appendTo(out);
}

#endif // WORKGROUP_CPP