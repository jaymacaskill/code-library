// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// TaskState.cpp

#ifndef TASKSTATE_CPP
#define TASKSTATE_CPP

#include "TaskState.h"
#include "WorkItem.h"

#include <iostream>

using namespace std;

// TaskState is abstract, it has no implementations

// === TODO STATE === //

void TodoState::handle(WorkItem* task)
{
    // no-op
}

bool TodoState::next(WorkItem* task)
{
    task->setState(new InProgressState);
    return true;
}

string TodoState::getName() const
{
    return "Todo";
}

// === IN PROGRESS STATE === //

void InProgressState::handle(WorkItem* task)
{
    task->addProgress(25);
    if (task->getProgress() >= 100)
        task->setState(new DoneState);
}

bool InProgressState::next(WorkItem* task)
{
    // TODO
    throw "Not yet implemented";
}

string InProgressState::getName() const
{
    return "In Progress";
}

// === BLOCKED STATE === //

void BlockedState::handle(WorkItem* task)
{
    task->incrementBlockedTime(1);
}

bool BlockedState::next(WorkItem* task)
{
    // TODO
    throw "Not yet implemented";
}

string BlockedState::getName() const
{
    return "Blocked";
}

// === DONE STATE === //

void DoneState::handle(WorkItem* task)
{
    return;
}

bool DoneState::next(WorkItem* task)
{
    return false;
}

string DoneState::getName() const
{
    return "Done";
}

#endif // TASKSTATE_CPP
