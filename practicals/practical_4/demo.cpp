// Amira Ajanaku (25111699)
// Senzo Lukhele (24691497)
// Jay Macaskill (25198387)

// COS 214 (Software Modelling) Practical 4
// Last Modified: 6 September 2026

// demo.cpp

#include "TaskState.h"

#include "TaskDecorator.h"

#include "WorkComponent.h"
#include "WorkGroup.h"
#include "WorkItem.h"

#include "WorkIterator.h"

#include <iostream>

using namespace std;

WorkGroup* project = nullptr;
string name = "";

void pressEnterToContinue()
{
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void buildProject()
{
    cout << "\n🪆 COMPOSITE 🪆\n";
    cout << "\n Using composite to build the project...\n";
    project = new WorkGroup("Project X");

    WorkGroup* frontend = new WorkGroup("frontend");
    WorkGroup* backend = new WorkGroup("backend");

    frontend->add(new WorkItem("UI Design"));
    frontend->add(new WorkItem("API Integration"));
    backend->add(new WorkItem("Database Design"));
    backend->add(new WorkItem("Security Audit"));

    project->add(frontend);
    project->add(backend);

    cout << "\nProject built! 📁\n";
}

void demoHierarchy()
{
    cout << "\n📁 PROJECT COMPOSITE HIERARCHY:\n";
    project->display();
}

void demoIterator()
{
    cout << "\n🧮 ITERATOR 🧮\n";
    cout << "\n🤔 How do you want to traverse the hierarchy?\n";
    int choice = 0;
    cout << "1. Active projects only" << endl;
    cout << "2. Everything" << endl;
    cout << "\n";
    cin >> choice;

    int tries = 1;

    while (choice != 1 && choice != 2 && tries < 4)
    {
        cout << "Choice invalid! Try again.\n";
        cin >> choice;
        tries ++;
    }

    if (tries >= 4)
    {
        cout << "You have failed to make a valid choice. Showing everything.🔎\n";
        WorkIterator* it = project->createIterator();
        while (it->hasNext())
        {
        cout << "  - " << it->next()->getName() << endl;
        }
        delete it;
        pressEnterToContinue();
        return;
    }

    if (choice == 1)
    {
        WorkIterator* it = project->createActiveIterator();
        while (it->hasNext())
        {
            cout << "  - " << it->next()->getName() << endl;
        }
        delete it;
        pressEnterToContinue();
        return;
    }

    else if (choice == 2)
    {
        WorkIterator* it = project->createIterator();
        while (it->hasNext())
        {
            cout << "  - " << it->next()->getName() << endl;
        }
        delete it;
        pressEnterToContinue();
        return;
    }
}

void demoState()
{
    cout << "\n 🎯 STATE 🎯\n";
    cout << "\n💻A DAY IN THE LIFE OF A TASK\n";

    vector<WorkComponent*> items;
    project->appendTo(items);
    WorkItem* task = dynamic_cast<WorkItem*>(items[2]);

    cout << "\n🧔🏻: " << name << ", your job today is " << task->getName() << ". Here are the stats:\n";
    cout << " Task: " << task->getName() << "\n";
    cout << " State: " << task->getState()->getName() << "\n";

    task->execute();
    cout << "\n🧔🏻: I see you have started on your task. Your progress is slow. I am going to talk to my supervisors.\n";
    cout << "\n🚨 Chris has blocked your task!\n";
    task->block();
    cout << "\n" << task->getName() << ": " << task->getState()->getName() << "\n";

    cout << "\n🧔🏻: They are happy for you to continue. Carry on immediately.\n";
    task->getState()->next(task);
    cout << "\n" << task->getName() << ": " << task->getState()->getName() << "\n";
    task->execute();

    cout << "\n👤: This task is so boring, can't I just send it to the done state anyway?\n";
    task->getState()->next(task);
    cout << "\n📚: No you cannot.\n";
    cout << "\n" << task->getName() << ": " << task->getState()->getName() << "\n";

    task->execute();
    task->execute();
    task->getState()->next(task);

    cout << "\n👤: FINALLY! I finished my task!!\n";
    cout << "\n" << task->getName() << ": " << task->getState()->getName() << "\n";
}

void demoDecorator()
{
    cout << "\n🎀 DECORATOR 🎀\n";
    cout << "\nDecorating with a LoggingDecorator and a PriorityDecorator\n";

    WorkItem* item = new WorkItem("Security Scan");
    WorkGroup* frontend = new WorkGroup("Frontend");
    frontend->add(item);

    WorkComponent* decorated = new PriorityDecorator(new LoggingDecorator(item), 1);
    frontend->decorate(item, decorated);

    decorated->execute();

    delete frontend;
}

void removingComposite()
{
    cout << "\n📦 COMPOSITE REMOVAL 📦\n";

    vector<WorkComponent*> items;
    project->appendTo(items);

    WorkItem* task = dynamic_cast<WorkItem*>(items[2]);

    cout << "Moving: " << task->getName() << "\n";

    WorkComponent* removed = project->remove(task);
   // since this is a short demo, instead of deleting removed, we add it back
   if (removed != nullptr) {
     project->add(removed);
    } else {
        cout << "Could not move the task - it wasn't a direct child of this group.\n";
    }
}

void status()
{
    cout << "\n📊 PROJECT STATUS 📊\n";

    vector<WorkComponent*> items;
    project->appendTo(items); // flattening using appendTo

    int todo = 0;
    int progress = 0;
    int blocked = 0;
    int done = 0;

    for (size_t i = 0; i < items.size(); i ++)
    {
        WorkItem* item = dynamic_cast<WorkItem*>(items[i]);
        if (item)
        {
            if (item->getState()->getName() == "In Progress") progress ++;
            else if (item->getState()->getName() == "Todo") todo ++;
            else if (item->getState()->getName() == "Blocked") blocked ++;
            else done ++;
        }
    }

    cout << "  Todo: " << todo << "\n";
    cout << "  In Progress: " << progress << "\n";
    cout << "  Blocked: " << blocked << "\n";
    cout << "  Done: " << done << "\n";
    cout << "  Overall: " << project->calculateState() << "\n";
}

int main()
{
cout << "  ___                     ___  \n" <<
        " (o o)                   (o o) \n" <<
        "(  V  ) Task Forge Demo (  V  )\n" <<
        "--m-m---------------------m-m--\n\n";

    cout << "What is your name?\n";
    cin >> name;

    buildProject();

    if (name == "demo")
    {
        cout << "\n🎬 QUICK DEMO MODE 🎬\n";
        cout << "Running all demonstrations automatically...\n";
        demoHierarchy();
        demoState();

        cout << "\n🧮 ITERATOR 🧮\n";

        cout << "\n📋 All tasks (DepthFirstIterator):\n";
        WorkIterator* it = project->createIterator();
        while (it->hasNext())
        {
            cout << "  - " << it->next()->getName() << endl;
        }
        delete it;

        cout << "\n🔄 Active tasks only (ActiveOnlyIterator):\n";
        WorkIterator* it2 = project->createActiveIterator();
        while (it2->hasNext())
        {
            cout << "  - " << it2->next()->getName() << endl;
        }
        delete it2;

        demoDecorator();
        removingComposite();
        status();
    }

    else
    {
        pressEnterToContinue();
        int choice;

        do
        {
            cout << "1. Show Hierarchy\n" <<
                    "2. Traverse Tasks\n" <<
                    "3. State\n" <<
                    "4. Decorator\n" <<
                    "5. Composite Removal\n" <<
                    "6. Project Status\n" <<
                    "7. Everything At Once\n" <<
                    "0. Exit\n\n";
            cout << "Choice: ";
            cin >> choice;

            switch(choice)
            {
                case 1: demoHierarchy(); pressEnterToContinue(); break;
                case 2: demoIterator(); break;
                case 3: demoState(); pressEnterToContinue(); break;
                case 4: demoDecorator(); pressEnterToContinue(); break;
                case 5: removingComposite(); pressEnterToContinue(); break;
                case 6: status(); pressEnterToContinue(); break;
                case 7: demoHierarchy(); demoIterator(); demoState(); demoDecorator(); removingComposite(); status(); break;
                case 0: cout << "Goodbye, " << name << "! 👋\n"; break;
                default: cout << "⚠️ Invalid choice!\n";
            }
        } while (choice != 0);
    }

    delete project;
    return 0;
}