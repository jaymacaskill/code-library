// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// WorkItem.cpp

#include <iostream>
#include <vector>

#include "WorkItem.h"
#include "WorkComponent.h"
#include "WorkIterator.h"
#include "TaskState.h"

using namespace std;

//Every new item starts with the TodoState
WorkItem::WorkItem(const string& name)
 : name(name), state(new TodoState()), progressPercent(0), blockedHours(0)
{ }

WorkItem::~WorkItem()
{
    delete state;
    state = nullptr;
}

string WorkItem::getName() const
{
    return this->name;
}

void WorkItem::display(int depth) const
{
    cout << string(depth*2, ' ') << "- " << name << " [" << state->getName()
         << ", " << progressPercent << "%]" << endl;
}

void WorkItem::execute()
{
   state->handle(this);
}

WorkIterator* WorkItem::createIterator()
{
    // TODO
    throw "Not yet implemented";
}

void WorkItem::appendTo(vector <WorkComponent*>& out)
{
    out.push_back(this);
}

void WorkItem::setState(TaskState* newState)
{
    delete state;
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
    progressPercent += amount;
    if (progressPercent > 100) 
      progressPercent = 100;
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