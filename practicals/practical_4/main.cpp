// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 6 September 2026

// main.cpp

#include "TaskDecorator.h"

#include "TaskState.h"

#include "WorkComponent.h"
#include "WorkGroup.h"
#include "WorkItem.h"

#include "WorkIterator.h"

#include <iostream>
#include <vector>

using namespace std;

void tests()
{
    cout << "\n🧪 CONDUCTING TESTS 🧪\n";

    WorkItem* item = new WorkItem("Core Task");
    item->display(0);
    item->execute();
    item->getState()->next(item);
    item->execute();
    cout << "  Progress: " << item->getProgress() << "%\n";
    cout << "  Is active? " << (item->isActive() ? "Yes" : "No") << "\n";
    item->addProgress(50);
    cout << "  After addProgress: " << item->getProgress() << "%\n";
    item->incrementBlockedTime(2);
    cout << "  Blocked hours: " << item->getBlockedHours() << "\n";

    WorkGroup* group = new WorkGroup("Test Group");
    group->add(item);
    group->display(0);
    cout << "  Group state: " << group->calculateState() << "\n";
    group->remove(item);
    cout << "  After removing item, state: " << group->calculateState() << "\n";

    WorkComponent* decorated = new PriorityDecorator(new LoggingDecorator(new WorkItem("Decorated Task")), 12);
    decorated->execute();
    decorated->display(0);
    delete decorated;

    vector<WorkComponent*> flat;
    group->add(item);
    group->appendTo(flat);
    cout << "  flatten size: " << flat.size() << "\n";

    delete group;

    cout << "\n🧪 TESTS CONCLUDED 🧪\n";
}

// main.cpp works well for the workflow
int main()
{
    tests();

    cout << "=====👨‍💻 STATIC MAIN (WEBSITE REDESIGN) 👨‍💻=====\n";

    cout << "\n📁 [COMPOSITE] BUILDING THE HIERARCHY 📁\n";

    // Project
    WorkGroup* project = new WorkGroup("Project: Website Redesign");
    
    // Epics
    WorkGroup* frontend = new WorkGroup("Epic: Frontend");
    WorkGroup* backend = new WorkGroup("Epic: Backend");

    // Stories
    WorkGroup* landing = new WorkGroup("Story: Landing Page");
    WorkGroup* checkout = new WorkGroup("Story: Checkout Flow");

    // Tasks
    WorkItem* homepage = new WorkItem("Build Homepage");
    WorkItem* navbar = new WorkItem("Style Navbar");
    WorkItem* cart = new WorkItem("Implement Cart");
    WorkItem* payment = new WorkItem("Payment Integration");
    WorkItem* database = new WorkItem("Setup Database");
    WorkItem* api = new WorkItem("Build API");
    WorkItem* security = new WorkItem("Security Audit");

    cout << "\n🌳 BUILDING THE TREE 🌳\n";

    landing->add(homepage);
    landing->add(navbar);

    checkout->add(cart);
    checkout->add(payment);

    frontend->add(landing);
    frontend->add(checkout);

    backend->add(database);
    backend->add(api);
    backend->add(security);

    project->add(frontend);
    project->add(backend);

    cout << "\n✅ Project built successfully!\n";
    project->display();

    // === This segment works well for an activity diagram on traversal === //
    cout << "\n🧮 [ITERATOR] TWO INDEPENDENT TRAVERSALS 🧮\n";

    cout << "\n📋 ALL TASKS 📋\n";

    WorkIterator* all = project->createIterator();
    int count = 0;
    while (all->hasNext())
    {
        cout << "   " << ++ count << ". " << all->next()->getName() << endl;
    } delete all;
    cout << "   ➡️  " << count << " components visited\n";
    count = 0;

    cout << "\nStarting work on the database...\n";
    database->execute();
    database->execute();

    cout << "\n📋 ACTIVE TASKS 📋\n";
    
    WorkIterator* active = project->createActiveIterator();
    while (active->hasNext())
    {
        cout << "   " << ++ count << ". " << active->next()->getName() << endl;
    } delete active;
    cout << "   ➡️  " << count << " active components visited\n";

    cout << "\n🎀 [DECORATOR] STACKED DECORATORS AT RUNTIME 🎀\n";
    WorkItem* scan = new WorkItem("Security Scan");
    WorkComponent* decorated = new PriorityDecorator(new LoggingDecorator(scan), 1);

    cout << "   Decorated task " << decorated->getName() << " with Logging and Priority decorators. Executing decorated task...\n";
    decorated->execute();
    delete decorated; // Decorator owns the task it wraps

    // === This segment works well for a state diagram
    // and for an activity diagram with state/configuration workflow === //
    cout << "\n🎯 [STATE] TASK LIFECYCLE 🎯\n";
    WorkItem* task = new WorkItem("Crunching Numbers");

    // Initial state: Todo

    cout << "   Task: " << task->getName() << "\n";
    cout << "       Initial: " << task->getState()->getName() << "\n";
    cout << "       Display: ";
            task->display();
    cout << "\n";

    // Todo ➡️ Blocked
    task->block();
    task->display();

    task->getState()->next(task);

    // Todo ➡️ InProgress
    task->getState()->next(task);
    cout << "       After next(): " << task->getState()->getName() << "\n";
    
    task->execute(); // adds progress
    cout << "       After execute: " << task->getState()->getName();
    task->display();

    // InProgress ➡️ Blocked
    task->block();
    task->display();

    // Blocked ➡️ InProgress
    task->getState()->next(task);

    // Once progress >= 100, InProgress ➡️ Done
    for (int i = 0; i < 3; i ++) { task->execute(); task->display(); }

    // Invalid transition, Done state is terminal
    cout << "       Invalid transition: Done ➡️ Next\n";
    task->getState()->next(task);
    task->display();

    delete task; // Owned by main, not in composite hierarchy nor is it decorated

    cout << "\n🤓 EXECUTING TASKS 🤓\n";
    navbar->execute();
    navbar->execute();
    security->execute();
    payment->execute();
    payment->execute();

    cout << "\n📦 [RUNTIME CHANGE] MOVING A TASK BETWEEN GROUPS 📦\n";
    cout << "   Before moving 'Build API':\n";
    cout << "       Backend has: ";
    WorkIterator* before = project->createIterator();
    while (before->hasNext())
    {
        cout << before->next()->getName() << " ";
    } delete before;
    cout << "\n";

    cout << "\n    🔄 Moving 'Build API' from Backend to Frontend...\n";
    WorkComponent* moved = backend->remove(api);
    if (moved)
    {
        frontend->add(moved);
        cout << "   ✅ Task moved!\n";
    }

    cout << "\n     Hierarchy after moving:\n";
    project->display();

    cout << "\n📸 [TRAVERSAL] ITERATORS HANDLING RUNTIME CHANGES 📸\n";
    cout << "   Building snapshot iterator before moving...\n";

    WorkIterator* snapshot = project->createActiveIterator();
    WorkComponent* bug = landing->remove(navbar);
    if (bug)
    {
        backend->add(bug);
        cout << "   ✅" << bug->getName() << " moved from Frontend to Backend\n";
    }

    cout << "Old snapshot showing old structure:\n";
    while (snapshot->hasNext())
    {
        cout << "   - " << snapshot->next()->getName() << endl;
    } delete snapshot;

    cout << "\nEach time you use an iterator, delete it 🗑️\n";
    cout << "Each time you need an iterator, make a new one ✨" << endl << "\n";

    WorkIterator* clean = project->createActiveIterator();
    while (clean->hasNext())
    {
        cout << "   - " << clean->next()->getName() << endl;
    } delete clean;

    cout << "\n📁 FINAL PROJECT HIERARCHY 📁\n";
    project->display();

    cout << "\n🧹 [OWNERSHIP AND CLEANUP] 🧹\n";
    delete project; // deletes whole hierarchy

    return 0;
}