// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// main.cpp

// Domain: software delivery. A Project has Epics, Epics have Stories and Tasks, and Tasks move through a lifecycle as work gets done.

#include "WorkComponent.h"
#include "WorkGroup.h"
#include "WorkItem.h"
#include "TaskState.h"
#include "TaskDecorator.h"
#include "WorkIterator.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    //A WorkGroup deletes its direct children when it's destroyed.
    //But a decorator never deletes what it wraps. 
    //So if we wrap a WorkItem in a decorator and only add the OUTER decorator to a group, the inner layers won't get deleted automatically. 
    //Here we keep track of them here so we can delete them ourselves at the end and avoid memory leaks.
    vector<WorkComponent*> thingsToDeleteManually;

    cout << "===================================" << endl;
    cout << " TaskForge Demo - Website Redesign" << endl;
    cout << "===================================" << endl << endl;

    //Project -> Epic -> Story -> Task, three levels deep below the root, with some tasks living directly inside an Epic too.

    WorkGroup* project = new WorkGroup("Website Redesign");

    WorkGroup* frontend = new WorkGroup("Epic: Frontend");
    WorkGroup* landingPage = new WorkGroup("Story: Landing Page");

    //"Build homepage" gets two decorators stacked on it: Priority(Logging(the actual task)).
    WorkItem* homepageItem = new WorkItem("Build homepage");
    TaskDecorator* homepageWithLogging = new LoggingDecorator(homepageItem);
    TaskDecorator* homepageFinal = new PriorityDecorator(homepageWithLogging, 5);

    //Only homepageFinal goes into the group, so only that gets deleted automatically. We need to remember to delete the other two layers.
    thingsToDeleteManually.push_back(homepageWithLogging);
    thingsToDeleteManually.push_back(homepageItem);

    WorkItem* navbarTask = new WorkItem("Style navbar");

    landingPage->add(homepageFinal);
    landingPage->add(navbarTask);

    WorkItem* headerBugTask = new WorkItem("Fix header bug");

    frontend->add(landingPage);
    frontend->add(headerBugTask); //a task can sit right in an Epic too

    WorkGroup* backend = new WorkGroup("Epic: Backend");
    WorkItem* dbTask = new WorkItem("Setup database");

    WorkItem* apiItem = new WorkItem("Build API");
    TaskDecorator* apiWithLogging = new LoggingDecorator(apiItem);
    thingsToDeleteManually.push_back(apiItem);

    backend->add(dbTask);
    backend->add(apiWithLogging);

    project->add(frontend);
    project->add(backend);

    cout << "Here's the project right now:" << endl;
    project->display();
    cout << endl;

    //Shows: two iterators running independently, valid and invalid state changes, and a decorated task actually being used.

    cout << "--- Doing some work ---" << endl << endl;

    //Make two iterators from the same tree, before using either one, to prove they don't interfere with each other.
    WorkIterator* everything = project->createIterator();
    WorkIterator* onlyActive = new ActiveOnlyIterator(project);

    cout << "Everything in the project (depth-first):" << endl;
    while (everything->hasNext())
    {
        cout << "  " << everything->next()->getName() << endl;
    }
    cout << endl;

    cout << "Only the active tasks:" << endl;
    while (onlyActive->hasNext())
    {
        cout << "  " << onlyActive->next()->getName() << endl;
    }
    cout << endl;

    delete everything;
    delete onlyActive;

    //Move "Build homepage" through its lifecycle.
    cout << "Working on 'Build homepage':" << endl;
    homepageFinal->execute(); //still Todo, just reports it's waiting
    homepageItem->getState()->next(homepageItem); //Todo -> InProgress
    homepageFinal->execute(); //here we add progress, log it, and flag priority
    homepageFinal->execute();
    homepageFinal->execute();
    homepageFinal->execute(); //we have hit 100%, moves itself to Done
    cout << endl;

    //Trying to see how the system reacts to invalid work
    cout << "Trying to move a finished task forward again:" << endl;
    bool didItWork = homepageItem->getState()->next(homepageItem);
    cout << "  allowed? " << (didItWork ? "yes" : "no") << " (expected: no)" << endl;
    cout << endl;

    //Show that the priority decorator correctly stays quiet once done.
    cout << "Running the decorated task again now that it's Done:" << endl;
    homepageFinal->execute();
    cout << endl;

    //Here we block a plain task and then unblock it.
    cout << "'Fix header bug' just got blocked by something external:" << endl;
    headerBugTask->setState(new BlockedState());
    headerBugTask->execute();
    headerBugTask->execute();
    headerBugTask->getState()->next(headerBugTask); //back to InProgress
    cout << endl;

    //Changes made while program runs
    //Shows an actual structural change at runtime, and what happens to an iterator that was already built before that change.

    cout << "--- Reorganising the project (runtime changes) ---" << endl << endl;

    //Newly built iterator before any changes
    WorkIterator* snapshotBeforeMove = new ActiveOnlyIterator(project);

    cout << "Moving 'Fix header bug' over to the Backend team..." << endl;
    frontend->remove(headerBugTask);
    backend->add(headerBugTask);
    cout << endl;

    //The iterators take a snapshot when they're built so this one still shows the OLD structure even though we just moved things.
    cout << "The iterator built earlier still shows the old setup:" << endl;
    while (snapshotBeforeMove->hasNext())
    {
        cout << "  " << snapshotBeforeMove->next()->getName() << endl;
    }
    cout << endl;
    delete snapshotBeforeMove;

    //A brand new iterator that picks up the change
    WorkIterator* freshOne = new ActiveOnlyIterator(project);
    cout << "A new iterator built after the move sees the update:" << endl;
    while (freshOne->hasNext())
    {
        cout << "  " << freshOne->next()->getName() << endl;
    }
    cout << endl;
    delete freshOne;

    cout << "Final layout:" << endl;
    project->display();
    cout << endl;

    //Cleanup. Deleting project takes care of every group and every outer decorator automatically. 
    //Anything that wasn't a direct child of a group will cleaned manually.
    // --------------------------------------------------------------
    delete project;

    for (WorkComponent* thing : thingsToDeleteManually)
    {
        delete thing;
    }

    cout << "Done, program exited cleanly. YAYY :)" << endl;
    return 0;
}