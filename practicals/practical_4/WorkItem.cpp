// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 6 September 2026

// WorkItem.cpp

#ifndef WORKITEM_CPP
#define WORKITEM_CPP

#include <iostream>
#include <vector>

#include "WorkItem.h"
#include "WorkComponent.h"
#include "WorkIterator.h"
#include "TaskState.h"

using namespace std;

WorkItem::WorkItem(const string& name)
{
    this->name = name;
    this->state = new TodoState;
    this->progressPercent = 0;
    this->blockedHours = 0;
}

WorkItem::~WorkItem()
{
    if (state) { delete state; state = nullptr; }
}

string WorkItem::getName() const
{
    return this->name;
}

void WorkItem::display(int depth) const
{
    for (int j = 0; j < depth; j ++)
    {
        cout << "  ";
    }
    cout << "- " << name << " (" << state->getName() << ")";

    if (progressPercent > 0 && progressPercent < 100)
        cout << " " << progressPercent << "% done";
    else if (progressPercent >= 100)
        cout << " ⭐ Completed!";
    if (blockedHours > 0)
        cout << " ⛔ Blocked for " << blockedHours << "h";

    cout << endl;
}

void WorkItem::block()
{
    if (state->getName() == "In Progress" || state->getName() == "Todo")
        this->setState(new BlockedState);
}

void WorkItem::unblock()
{
    if (state->getName() == "Blocked")
        this->setState(new InProgressState);
}

void WorkItem::execute()
{
    if (state)
        state->handle(this);
    else
        cout << "⚠️ Error! This task has no state!\n";
}

WorkIterator* WorkItem::createIterator()
{
    return new DepthFirstIterator(this);
}

WorkIterator* WorkItem::createActiveIterator()
{
    return new ActiveOnlyIterator(this);
}

void WorkItem::appendTo(vector <WorkComponent*>& out)
{
    out.push_back(this);
}

void WorkItem::setState(TaskState* newState)
{
    if (state) delete state;
    state = newState;
}

TaskState* WorkItem::getState() const
{
    return state;
}

bool WorkItem::isActive() const
{
    return (this->progressPercent < 100);
}

void WorkItem::addProgress(int amount)
{
    this->progressPercent += amount;
}

void WorkItem::incrementBlockedTime(int hours)
{
    this->blockedHours += hours;
}

int WorkItem::getProgress() const
{
    return this->progressPercent;
}

int WorkItem::getBlockedHours() const
{
    return this->blockedHours;
}

#endif // WORKITEM_CPP