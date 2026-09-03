// Amira Ajanaku
// Senzo Lukhele
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 4 September 2026

// WorkItem.h

#ifndef WORKITEM_H
#define WORKITEM_H

#include <iostream>
#include <vector>

#include "WorkComponent.h"
#include "WorkIterator.h"
#include "TaskState.h"

using namespace std;

class WorkComponent;
class WorkIterator;
class TaskState;

/**
 * @brief The Leaf of the Composite design pattern
 * A single unit of work such as a Task
 * Holds a current TaskState which controls the lifecycle behaviour
 */
class WorkItem : public WorkComponent
{
    public:

        /**
         * @brief The constructor for a WorkItem object
         * @param name The name of the object
         */
        explicit WorkItem(const string& name);

        /**
         * @brief The destructor for a WorkItem object
         * Virtual to improve code extensibility
         */
        virtual ~WorkItem();

        /// @copydoc WorkComponent::getName
        string getName() const override;

        /// @copydoc WorkComponent::display
        void display(int depth = 0) const override;

        /// @copydoc WorkComponent::execute
        void execute() override;

        /// @copydoc WorkComponent::createIterator
        WorkIterator* createIterator() override;

        /// @copydoc WorkComponent::appendTo
        void appendTo(vector <WorkComponent*>& out) override;

        void setState(TaskState* newState);

        /**
         * @brief Returns the state of this object (getter)
         * @return The state member of the object
         */
        TaskState* getState() const;

        /**
         * @brief Returns true if the state is not DoneState
         * @return Whether the object is active or not
         */
        bool isActive() const; // return !(state == DoneState)

    private:
        string name; /**< The name of this object */
        TaskState* state; /**< The state of this object */
};


#endif // WORKITEM_H