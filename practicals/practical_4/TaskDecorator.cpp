// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// TaskDecorator.cpp

#include "WorkComponent.h"
#include "WorkIterator.h"
#include "TaskDecorator.h"

#include "WorkItem.h"

#include <iostream>

using namespace std;

class WorkComponent;
class WorkIterator;

// === TASK DECORATOR === //

TaskDecorator::TaskDecorator(WorkComponent* wrapped)
{
    this->wrapped = wrapped;
}

//Does not the wrapped object, no ownership
TaskDecorator::~TaskDecorator()
{ }

string TaskDecorator::getName() const
{
    return wrapped->getName();
}

void TaskDecorator::execute()
{
    wrapped->execute();
}

WorkIterator* TaskDecorator::createIterator()
{
    return wrapped->createIterator();
}

void TaskDecorator::appendTo(vector<WorkComponent*>& out)
{
    wrapped->appendTo(out);
}

void TaskDecorator::display(int depth) const 
{
    wrapped->display(depth);
}

// === PRIORITY DECORATOR === //

PriorityDecorator::PriorityDecorator(WorkComponent* wrapped, int priority) 
 : TaskDecorator(wrapped)
{
    this->priority = priority;
}

void PriorityDecorator::execute()
{
   wrapped->execute();
   WorkItem* item = dynamic_cast<WorkItem*>(wrapped);
   if (item != nullptr && item->getState()->getName() == "Done") {
    return;
    //since we don't add priority handling to a completed task
   }
   cout << "[Priority " << priority << "] " << wrapped->getName() << " flagged." << endl;
}

void PriorityDecorator::display(int depth) const
{
    cout << string(depth*2, ' ') << "- [P" << priority << "] " << wrapped->getName();
    WorkItem* item = dynamic_cast<WorkItem*>(wrapped);
    if (item != nullptr) {
        cout << " [" << item->getState()->getName() << ", " << item->getProgress() << "%]";
    }
    cout << endl;
}

// === LOGGING DECORATOR === //

LoggingDecorator::LoggingDecorator(WorkComponent* wrapped) 
: TaskDecorator(wrapped) { }

void LoggingDecorator::execute()
{
    cout << "[LOG] Executing " << wrapped->getName() << "..." << endl;
   wrapped->execute();
   cout << "[LOG] Finsihing executing " << wrapped->getName() << "." << endl;
}