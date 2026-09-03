// Amira Ajanaku
// Senzo Lukhele
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 4 September 2026

// TaskDecorator.h

#ifndef TASKDECORATOR_H
#define TASKDECORATOR_H

#include "WorkComponent.h"

#include <iostream>

using namespace std;

class WorkComponent;

class TaskDecorator : public WorkComponent
{ };

class PriorityDecorator : public TaskDecorator
{ };

class LoggingDecorator : public TaskDecorator
{ };

#endif // TASKDECORATOR_H