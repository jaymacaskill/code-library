// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// TaskDecorator.cpp

#ifndef TASKDECORATOR_CPP
#define TASKDECORATOR_CPP

#include "WorkComponent.h"
#include "WorkIterator.h"
#include "TaskDecorator.h"

#include <iostream>

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
    // TODO
    throw "Not yet implemented";
}

string TaskDecorator::getName() const
{
    return wrapped->getName();
}

void TaskDecorator::execute()
{
    // TODO
    throw "Not yet implemented";
}

WorkIterator* TaskDecorator::createIterator()
{
    // TODO
    throw "Not yet implemented";
}

void TaskDecorator::appendTo(vector<WorkComponent*>& out)
{
    out.push_back(this);
}

// === PRIORITY DECORATOR === //

PriorityDecorator::PriorityDecorator(WorkComponent* wrapped, int priority) : TaskDecorator(wrapped)
{
    this->priority = priority;
}

void PriorityDecorator::execute()
{
    // TODO
    throw "Not yet implemented";
}

void PriorityDecorator::display(int depth = 0) const
{
    // TODO
    throw "Not yet implemented";
}

// === LOGGING DECORATOR === //

LoggingDecorator::LoggingDecorator(WorkComponent* wrapped) : TaskDecorator(wrapped) { }

void LoggingDecorator::execute()
{
    // TODO
    throw "Not yet implemented";
}

#endif // TASKDECORATOR_CPP