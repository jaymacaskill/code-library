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
    cout << "🎯 Todo: [" << task->getName() << "]" << endl;
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
    cout << "🔄 [" << task->getName() << "] Progress: " << task->getProgress() << "%" << endl;
    
    if (task->getProgress() >= 100)
        task->setState(new DoneState);
}

bool InProgressState::next(WorkItem* task)
{
    if (task->getProgress() >= 100)
    {
        cout << "[" << task->getName() << "] is complete! ⭐" << endl;
        task->setState(new DoneState);
        return true;
    }

    cout << "⚠️ [" << task->getName() << "] is only " << task->getProgress() << "% complete" << endl;
    return false;

}

string InProgressState::getName() const
{
    return "In Progress";
}

// === BLOCKED STATE === //

void BlockedState::handle(WorkItem* task)
{
    cout << "❌ [" << task->getName() << "] has been blocked for " << task->getBlockedHours() << "h" << endl;
    task->incrementBlockedTime(1);
}

bool BlockedState::next(WorkItem* task)
{
    cout << "🔎 Unblocking " << task->getName() << endl;
    task->unblock();
    return true;
}

string BlockedState::getName() const
{
    return "Blocked";
}

// === DONE STATE === //

void DoneState::handle(WorkItem* task)
{
    cout << "[" << task->getName() << "] Complete! ⭐" << endl;
    return;
}

bool DoneState::next(WorkItem* task)
{
    cout << "[" << task->getName() << "] is already complete! ⭐" << endl;
    return false;
}

string DoneState::getName() const
{
    return "Done";
}

#endif // TASKSTATE_CPP
