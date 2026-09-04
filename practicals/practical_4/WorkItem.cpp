// Amira Ajanaku
// Senzo Lukhele
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 4 September 2026

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
}

WorkItem::~WorkItem()
{
    delete state;
    state = nullptr;
}

string WorkItem::getName() const
{
    return this->name;
}

void WorkItem::display(int depth = 0) const
{
    // TODO
    throw "Not yet implemented";
}

void WorkItem::execute()
{
    // TODO
    throw "Not yet implemented";
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