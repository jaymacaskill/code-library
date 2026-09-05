// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// WorkGroup.cpp

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

//Deletion cascades down ato destroy the whole subtree beneath it
WorkGroup::~WorkGroup()
{
   for (WorkComponent* child : children) {
    delete child;
   }
   children.clear();
}

string WorkGroup::getName() const
{
    return this->name;
}

void WorkGroup::display(int depth) const
{
    cout << string(depth*2, ' ') << "+ " << name << endl;
    for (WorkComponent* child : children) {
        child->display(depth + 1);
    }
}

void WorkGroup::execute()
{
    for (WorkComponent* child : children) {
        child->execute();
    }
}

WorkIterator* WorkGroup::createIterator()
{
    return new DepthFirstIterator(this);
}

void WorkGroup::add(WorkComponent* child)
{
   children.push_back(child);
}

void WorkGroup::remove(WorkComponent* child)
{
    for (size_t i = 0; i < children.size(); i++) {
        if (children[i] == child) {
            children.erase(children.begin() + i); //removal
            break; //to stop after the first match
        }
    }
}

void WorkGroup::appendTo(vector<WorkComponent*>& out)
{
    out.push_back(this);
    for (size_t i = 0; i < children.size(); i ++)
        children[i]->appendTo(out);
}