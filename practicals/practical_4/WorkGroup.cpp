// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 6 September 2026

// WorkGroup.cpp

#ifndef WORKGROUP_CPP
#define WORKGROUP_CPP

#include "WorkGroup.h"
#include "WorkComponent.h"
#include "WorkIterator.h"
#include "WorkItem.h"

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

void WorkGroup::display(int depth) const
{
    for (int j = 0; j < depth; j ++)
    {
        cout << "  ";
    }

    cout << "[Group] " << name << ": " << calculateState() << endl;

    for (size_t j = 0; j < children.size(); j ++)
    {
        children[j]->display(depth + 1);
    }
}

string WorkGroup::calculateState() const
{
    if (children.empty())
    {
        return "Empty";
    }

    int todo = 0;
    int progress = 0;
    int blocked = 0;
    bool done = false;

    for (size_t i = 0; i < children.size(); i ++)
    {
        WorkItem* item = dynamic_cast<WorkItem*>(children[i]);
        if (item)
        {
            if (item->getState()->getName() == "In Progress") progress ++;
            else if (item->getState()->getName() == "Todo") todo ++;
            else if (item->getState()->getName() == "Blocked") blocked ++;
        }
        else
        {
            WorkGroup* group = dynamic_cast<WorkGroup*>(children[i]);
            if (group)
            {
                string state = group->calculateState();
                if (state == "Blocked ⚠️") blocked ++;
                else if (state == "In Progress 🕓") progress ++;
                else if (state == "Todo 🎯") todo ++;
                else { /* nothing */ }
            }
        }
    }

    done = (todo == 0) && (progress == 0) && (blocked == 0);

    if (done)
        return "Complete! ⭐";

    if (blocked > 0)
        return "Blocked ⚠️";

    if (progress > 0)
        return "In Progress 🕓";

    return "Todo 🎯";
}

void WorkGroup::execute()
{
    cout << "▶️ Executing [" << name << "]" << endl;
    for (size_t i = 0; i < children.size(); i ++)
        children[i]->execute();

    cout << "✅ " << name << " Executed. State: " << calculateState() << endl;
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

void WorkGroup::decorate(WorkComponent* target, WorkComponent* decorator)
{
    for (size_t i = 0; i < children.size(); i ++)
    {
        if (children[i] == target)
        {
           children[i] = decorator; // replaces the child with the decorated componenet,
           // decorator now owns the child
            return;
        }
    }

    cout << "⚠️ Target not found in this group!\n";
}

#endif // WORKGROUP_CPP