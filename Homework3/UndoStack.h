// Huseyin Eren YILDIZ - 31047

#ifndef HOMEWORK3_UNDOSTACK_H
#define HOMEWORK3_UNDOSTACK_H

#include <string>
#include <iostream>

using namespace std;

struct StackNode
{
    char operation;
    string employee_name;
    string project_name;
    int project_priority;
    StackNode * next;

    //Default constructor
    StackNode()
            : operation(), employee_name(""), project_name(""), project_priority(0), next(nullptr)

    {}

    // the constructor with parameters for StackNode struct
    StackNode(const char & struct_operation ,const string & struct_emp_name ,const string & struct_project_name , const int & struct_project_prio , StackNode* struct_next)
    {
        operation = struct_operation;
        employee_name = struct_emp_name;
        project_name = struct_project_name;
        project_priority = struct_project_prio;
        next = struct_next;
    }
};

class UndoStack {

private:

    StackNode * top;  // A StackNode points to top

public:

    UndoStack(); // Creates an empty stack
    void push(char, string, string, int);
    void pop(char &, string &, string &, int &);
    bool isEmpty();
    void clear();
};

#endif