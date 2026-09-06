// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 6 September 2026

// TaskDecorator.cpp

#ifndef TASKDECORATOR_CPP
#define TASKDECORATOR_CPP

#include "WorkComponent.h"
#include "WorkIterator.h"
#include "TaskDecorator.h"
#include "WorkItem.h"

#include <iostream>
#include <ctime>
#include <cstring>

using namespace std;

class WorkComponent;
class WorkIterator;

// === TASK DECORATOR === //

TaskDecorator::TaskDecorator(WorkComponent* wrapped)
{
    this->wrapped = wrapped;
}

TaskDecorator::~TaskDecorator()
{   
    delete wrapped;
}

string TaskDecorator::getName() const
{
    if (wrapped) return wrapped->getName();
    return "";
}

void TaskDecorator::execute()
{
    if (wrapped) wrapped->execute();
}

WorkIterator* TaskDecorator::createIterator()
{
    if (wrapped) return wrapped->createIterator();
    return nullptr;
}

WorkIterator* TaskDecorator::createActiveIterator()
{
    if (wrapped) return wrapped->createActiveIterator();
    return nullptr;
}

void TaskDecorator::appendTo(vector<WorkComponent*>& out)
{
    out.push_back(this);
}

void TaskDecorator::display(int depth) const
{
    if (!wrapped) { cout << "🚨 No wrapped component!\n"; return; }
    wrapped->display(depth);
}

// === PRIORITY DECORATOR === //

PriorityDecorator::PriorityDecorator(WorkComponent* wrapped, int priority) : TaskDecorator(wrapped)
{
    this->priority = priority;
}

void PriorityDecorator::execute()
{
    if (!wrapped)
    {
        cout << "⚠️ PriorityDecorator: No wrapped component!\n";
        return;
    }
    
    WorkItem* item = dynamic_cast<WorkItem*>(wrapped);
    if (item && item->getState()->getName() == "Done")
    {
        cout << "⚠️ PriorityDecorator: Task [" << wrapped->getName() << "] is already done! Cannot add priority.\n";
        return;
    }
    else if (item && item->getState()->getName() == "Blocked")
    {
        cout << "PriorityDecorator: ⚠️ Unblocking the priority task.\n";
        item->unblock();
    }
    else if (item && item->getState()->getName() == "In Progress" && item->getProgress() < 50)
    {
        cout << "PriorityDecorator: Boosting progress. 🚀\n";
        item->addProgress(25);
    }

    cout << "⭐ Priority level " << priority << " for task " << wrapped->getName() << endl;

    wrapped->execute();
}

void PriorityDecorator::display(int depth) const
{
    if (!wrapped)
    {
        for (int i = 0; i < depth; i ++)
            cout << "  ";
        cout << "🚨 No wrapped component!\n";
        return;
    }

    for (int j = 0; j < depth; j ++)
        cout << "  ";

    cout << "⭐ " << wrapped->getName() << " [Priority: " << priority << "]";

    wrapped->display(depth);

    cout << endl;
}

string PriorityDecorator::getName() const
{
    return wrapped->getName() + " [Priority]";
}

// === LOGGING DECORATOR === //

LoggingDecorator::LoggingDecorator(WorkComponent* wrapped) : TaskDecorator(wrapped) { }

void LoggingDecorator::execute()
{
    if (!wrapped)
    {
        cout << "📝 LoggingDecorator: No wrapped component!\n";
        return;
    }

    time_t now = time(nullptr);
    char* dt = ctime(&now);
    dt[strlen(dt) - 1] = '\0';

    cout << " 📝 [LOG] " << dt << " Starting execution of: " << wrapped->getName() << endl;
    wrapped->execute();

    time_t end = time(nullptr);
    dt = ctime(&end);
    dt[strlen(dt) - 1] = '\0';

    cout << " 📝 [LOG] " << dt << " Completed execution of: " << wrapped->getName() << endl;
}

#endif // TASKDECORATOR_CPP