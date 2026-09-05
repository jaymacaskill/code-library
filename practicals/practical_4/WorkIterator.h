// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 5 September 2026

// WorkIterator.h

#ifndef WORKITERATOR_H
#define WORKITERATOR_H

#include <iostream>
#include <vector>

using namespace std;

class WorkComponent; // also only forward declare

/**
 * @brief The abstract iterator of the Iterator design pattern
 */
class WorkIterator
{
    public:

        /**
         * @brief The destructor for a WorkIterator object
         */
        virtual ~WorkIterator() { }

        /**
         * @brief Tells us whether the current WorkComponent has one following it
         * @return True if the component has next, false if not
         */
        virtual bool hasNext() = 0;

        /**
         * @brief Provides the next WorkComponent
         * @return The next WorkComponent
         */
        virtual WorkComponent* next() = 0;
};

/**
 * @brief Visits every node in the hierarchy (both groups and items)
 * in a depth-first manner. Serves as the concrete iterator of the Iterator
 * design pattern.
 * Makes use of a snapshot, the tree is flattened once so later structural
 * changes are not reflected in an iterator already built.
 */
class DepthFirstIterator : public WorkIterator
{
    public:

        /**
         * @brief The constructor for a depth-first iterator
         * @param root The root of the tree
         */
        explicit DepthFirstIterator(WorkComponent* root);

        /// @copydoc WorkIterator::hasNext
        bool hasNext() override;

        /// @copydoc WorkIterator::next
        WorkComponent* next() override;

    private:
        vector<WorkComponent*> flattened; /**< The flattened tree */
        size_t position; /**< The current position of the iterator */
};

/**
 * @brief Another concrete iterator of the Iterator design pattern.
 * Visits only WorkItems that are active. Can run at the same time as
 * DepthFirstIterator over the same tree without interference
 */
class ActiveOnlyIterator : public WorkIterator
{
    public:

        /**
         * @brief The constructor for an active only iterator
         * @param root The root of the tree
         */
        explicit ActiveOnlyIterator(WorkComponent* root);
        
        /// @copydoc WorkIterator::hasNext
        bool hasNext() override;

        /// @copydoc WorkIterator::next
        WorkComponent* next() override;

    private:
        vector<WorkComponent*> flattened; /**< The flattened tree */
        size_t position; /**< The current position of the iterator */
};

#endif // WORKITERATOR_H