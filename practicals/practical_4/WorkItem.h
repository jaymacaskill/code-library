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
        bool isActive() const; // return progressPercent < 100
        // check the progress percent

        /**
         * @brief Adds progress to the total progress percent member
         * @param amount The amount of progress to add
         */
        void addProgress(int amount);

        /**
         * @brief Increments the duration for which the work component has been blocked
         * @param hours How much longer the work has been blocked for
         */
        void incrementBlockedTime(int hours);

        /**
         * @brief Returns the progress percent member
         * @return The progress percent member
         */
        int getProgress() const;

        /**
         * @brief Returns the blocked hours
         * @return The blocked hours member
         */
        int getBlockedHours() const;

    private:
        string name; /**< The name of this object */
        TaskState* state; /**< The state of this object */
        int progressPercent; /**< The progress of the work component */
        int blockedHours; /**< How long the work has been blocked */
};


#endif // WORKITEM_H