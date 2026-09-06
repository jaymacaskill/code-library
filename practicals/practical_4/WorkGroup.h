// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 6 September 2026

// WorkGroup.h

#ifndef WORKGROUP_H
#define WORKGROUP_H

#include "WorkComponent.h"
#include "WorkIterator.h"

#include <iostream>
#include <vector>

using namespace std;

class WorkComponent;
class WorkIterator;

/**
* @brief The Composite in the Composite design pattern
* A group of work which may contain other groups or items
*/
class WorkGroup : public WorkComponent
{
    public:

        /**
         * @brief The constructor for a WorkGroup object
         * @param name The name of the object
         */
        explicit WorkGroup(const string& name);

        /**
         * @brief The destructor for a WorkGroup object
         * Virtual to allow easier extension of classes
         */
        virtual ~WorkGroup();

        /// @copydoc WorkComponent::getName
        string getName() const override;

        /// @copydoc WorkComponent::display
        void display(int depth = 0) const override;

        /// @copydoc WorkComponent::execute
        void execute() override;
        // Here we count and print how many children made progress versus how many were blocked in addition to typical behaviour

        /// @copydoc WorkComponent::createIterator
        WorkIterator* createIterator() override;

        /// @copydoc WorkComponent::createActiveIterator
        WorkIterator* createActiveIterator() override;

        /// @copydoc WorkComponent::add
        void add(WorkComponent* child) override;

        /// @copydoc WorkComponent::remove
        WorkComponent* remove(WorkComponent* child) override;

        /// @copydoc WorkComponent::appendTo
        void appendTo(vector<WorkComponent*>& out) override;

        /**
         * @brief Prints out the aggregate state for the group
         */
        string calculateState() const;

        /**
         * @brief A function to help with ownership transferral for decorating a child
         *
         * @param target The componenent to be decorated
         * @param decorator The decorator to use
         */
        void decorate(WorkComponent* target, WorkComponent* decorator);

    private:
       string name; /**< The name of this object */
       vector<WorkComponent*> children; /**< The children of this object (may be EventItems or other EventGroups) */
};

#endif // WORKGROUP_H