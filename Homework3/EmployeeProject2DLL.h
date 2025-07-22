// Huseyin Eren YILDIZ - 31047

#ifndef HOMEWORK3_EMPLOYEEPROJECT2DLL_H
#define HOMEWORK3_EMPLOYEEPROJECT2DLL_H

#include <iostream>
#include <string>

using namespace std;

struct ProjectNode
{
    string project_name;
    int project_priority;
    ProjectNode * next;
    ProjectNode * prev;

    //Default constructor
    ProjectNode ()
            :project_name(""), project_priority(0), next(nullptr), prev(nullptr)
    {}

    // the constructor with parameters for ProjectNode struct
    ProjectNode(string struct_project_name, int struct_project_priority, ProjectNode * struct_next = nullptr, ProjectNode * struct_prev = nullptr) {
        project_name = struct_project_name;
        project_priority = struct_project_priority;
        next = struct_next;
        prev = struct_prev;
    }
};

struct EmployeeNode
{
    string employee_name;
    ProjectNode * head;
    ProjectNode * tail;
    EmployeeNode * down;

    //Default constructor
    EmployeeNode ()
            :employee_name(""), head(nullptr), tail(nullptr), down(nullptr)
    {}

    // the constructor with parameters for EmployeeNode struct
    EmployeeNode(string struct_employee_name, ProjectNode * struct_head = nullptr, ProjectNode * struct_tail = nullptr, EmployeeNode * struct_down= nullptr)
    {
        employee_name = struct_employee_name;
        head = struct_head;
        tail = struct_tail;
        down = struct_down;
    }
};

class EmployeeProject2DLL {

private:

    EmployeeNode * headOfProject2DLL;
    void print_forward (ProjectNode *);
    void print_reverse (ProjectNode *);
    void sort_projects (string);
    EmployeeNode * findEmployeeW_Name (string);
    ProjectNode * findProjectW_Name (const EmployeeNode *, string);
    bool Prio_check (string, int);

public:

    EmployeeProject2DLL();
    bool isEmployeeAssignedToProject(string, string);
    bool updateProjectPriority (string, string, int&);
    bool assignEmployeeToProject(string, string, int);
    void withdrawEmployeeFromProject(string, string, int&);
    void printTheEntireList();
    void printEmployeeProjects(string, int);
    void undo (char, string, string, int);
    void clear();
};

#endif //HOMEWORK3_EMPLOYEEPROJECT2DLL_H
