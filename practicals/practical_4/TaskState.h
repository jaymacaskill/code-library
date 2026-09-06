// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// TaskState.h

#ifndef TASKSTATE_H
#define TASKSTATE_H

#include <iostream>

using namespace std;

class WorkItem; // here we only forward declare otherwise we will have circular references

/**
 * @brief The abstract state class
 */
class TaskState
{
    public:

        /**
         * @brief Destructor for a TaskState object
         */
        virtual ~TaskState() { }

        /**
         * @brief Performs an action appropriate to the state
         * Used during execute, each state does something different
         * @param task The item currently needing to be handled
         */
        virtual void handle(WorkItem* task) = 0;

        /**
         * @brief Used to move through different states, e.g. from Todo to InProgress
         * Meaningfully handles rejection of state change
         * @param task The item moving through states
         * @return Whether we successfully moved to the next state
         */
        virtual bool next(WorkItem* task) = 0;

        /**
         * @brief The getter for the name of the object
         * @return The name of this object
         */
        virtual string getName() const = 0;
};

/**
 * @brief The state a work component is in when it still needs to be started
 */
class TodoState : public TaskState
{
    public:
    
        /// @copydoc TaskState::handle
        void handle(WorkItem* task) override;

        /**
         * @brief Todo -> InProgress transition
         * @param task The item that will undergo state change
         */
        bool next(WorkItem* task) override;

        /// @copydoc TaskState::getName
        string getName() const override;
};

/**
 * @brief The state a work component is in when it is currently in progress
 */
class InProgressState : public TaskState
{
    public:
    
        /// @copydoc TaskState::handle
        void handle(WorkItem* task) override;
        // Adds progress in, if the progress is completed et the state to done

        /**
         * @brief InProgress -> Done (or Blocked, but not in this function) transition
         * @param task The item that will undergo state change
         * @return Whether we successfully moved to the next state
         */
        bool next(WorkItem* task) override;

        /// @copydoc TaskState::getName
        string getName() const override;
};

/**
 * @brief The state a work component is in when it is blocked and cannot make progress
 */
class BlockedState : public TaskState
{
    public:
    
        /// @copydoc TaskState::handle
        void handle(WorkItem* task) override;
        // does not add progress, but increments blocked time

        /**
         * @brief Blocked -> InProgress transition
         * @param task The item that will undergo state change
         * @return Whether we successfully moved to the next state
         */
        bool next(WorkItem* task) override;

        /// @copydoc TaskState::getName
        string getName() const override;
};

/**
 * @brief The state of a completed work component
 */
class DoneState : public TaskState
{
    public:
    
        /// @copydoc TaskState::handle
        void handle(WorkItem* task) override;
        // does nothing

        /**
         * @brief Invalid, done is a terminal state
         * @param task The item that will undergo state change
         * @return Whether we successfully moved to the next state (false here)
         */
        bool next(WorkItem* task) override;

        /// @copydoc TaskState::getName
        string getName() const override;
};

#endif // TASKSTATE_H
