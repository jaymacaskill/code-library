// Amira Ajanaku
// Senzo Lukhele
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 4 September 2026

// TaskDecorator.h

#ifndef TASKDECORATOR_H
#define TASKDECORATOR_H

#include "WorkComponent.h"
#include "WorkIterator.h"

#include <iostream>

using namespace std;

class WorkComponent;
class WorkIterator;

/**
 * @brief The decorator in the decorator design pattern
 * Wraps a WorkComponent and forwards calls to it while remaining usable
 * anywhere a plain WorkComponent is expected
 */
class TaskDecorator : public WorkComponent
{
    public:

        /**
         * @brief The constructor for a TaskDecorator
         * @param wrapped The component to be wrapped
         */
        explicit TaskDecorator(WorkComponent* wrapped);

        /**
         * @brief The destructor for a task decorator object
         */
        virtual ~TaskDecorator();

        /// @copydoc WorkComponent::getName
        string getName() const override;

        /// @copydoc WorkComponent::execute
        void execute() override;

        /// @copydoc WorkComponent::createIterator 
        WorkIterator* createIterator() override;

        /// @copydoc WorkComponent::appendTo
        void appendTo(vector<WorkComponent*>& out) override;

    protected:
        WorkComponent* wrapped; /**< The component to be wrapped */
};

/**
 * @brief Adds a priority level to a task, execute() reflects the extra priority
 */
class PriorityDecorator : public TaskDecorator
{
    public:

        /**
         * @brief The constructor for a priority decorator
         * @param wrapped The WorkComponent to be wrapped
         * @param priority The priority level of the component
         */
        PriorityDecorator(WorkComponent* wrapped, int priority);
        
        /// @copydoc WorkComponent::execute
        void execute() override;
        // Here we refuse to add priority on a DoneState task

        /// @copydoc WorkComponent::display
        void display(int depth = 0) const override;

    private:
        int priority; /**< The priority level of tje task */
};

/**
 * @brief Adds a log entry each time the wrapped component executes
 */
class LoggingDecorator : public TaskDecorator
{
    public:

        /**
         * @brief The constructor for a logging decorator
         * @param wrapped The WorkComponent to be wrapped
         */
        explicit LoggingDecorator(WorkComponent* wrapped);

        /// @copydoc WorkComponent::execute
        void execute() override;
};

#endif // TASKDECORATOR_H