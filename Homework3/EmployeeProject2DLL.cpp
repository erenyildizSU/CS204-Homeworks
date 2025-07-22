// Huseyin Eren YILDIZ, 31047
// Homework 3

/******************************************************************************
Purpose: This program implements a two-dimensional hybrid linked list (2DHLL)
structure that will be used to store information about employees and their assigned projects.
Author: HUSEYIN EREN YILDIZ - 31047
Date: 3/04/2024
******************************************************************************/

#include "EmployeeProject2DLL.h"

using namespace std;

EmployeeNode * EmployeeProject2DLL::findEmployeeW_Name (string name) {
// This function takes string as a parameter
// This function finds an employee by name

    EmployeeNode * location = headOfProject2DLL;
    while (location != nullptr) {
        if (location -> employee_name == name) {  // Check whether the employee's name in the location equals the given name
            return location;  // if it is true, return the location employee node.
        }
        location = location -> down; // Move to the next employee in the list. (vertical traversal in a 2D list structure)
    }
    return nullptr;  // If there is no such name
}

ProjectNode *EmployeeProject2DLL::findProjectW_Name(const EmployeeNode * emp, string name) {
// This function takes string and EmployeeNode as parameters
// This function finds a project by its name within an employee's project list

    ProjectNode * location = emp -> head;
    while (location != nullptr) {
        if (location -> project_name == name) {  // Check whether the project's name in the location equals the given name
            return location;  // if it is true, return the location project node
        }
        location = location -> next;  // Move to the next project in the list
    }
    return nullptr;  // If there is no such name, return nullptr
}

bool EmployeeProject2DLL::Prio_check(string employee_name, int priority) {
// This function takes string and int as a parameter
// If the employee has a project with the given priority, it will return true. Otherwise, it will return false

    if (findEmployeeW_Name(employee_name) != nullptr) { // It will try to find employee by name with "findEmployeeW_Name" function.
                                                              // If name is found, it will continue. Otherwise, it will return false
        // Access the head of the linked list of the employee's projects
        ProjectNode * project_head = findEmployeeW_Name(employee_name) -> head;

        while ( project_head != nullptr) { // Iterate through the list of projects.
            if (project_head -> project_priority == priority) { // If the current project's priority matches the searched  priority
                return true; // If there is a matching, it will return true
            }

            project_head = project_head -> next; // Move to next node in the list
        }
        return false; // After checking all projects, no match was found; return false
    }

    return false; // If the employee was not found to begin with, return false
}

void EmployeeProject2DLL::sort_projects (string employee_name) {  //I used "insertion algorithm" to sort projects

    EmployeeNode * temp_headOfemp;
    ProjectNode * location, * compare;

    string temp_name;
    int temp_priority;
    temp_headOfemp = headOfProject2DLL;

    while (temp_headOfemp != nullptr) {  // Iterates through the entire list of employees

        if (temp_headOfemp -> employee_name == employee_name) {
            // Start with the second project in the list, because the first project is already "sorted".
            location = temp_headOfemp -> head -> next;

            while (location != nullptr) { // Continues sorting until the end of the project list is reached
                temp_name = location -> project_name;
                temp_priority = location -> project_priority;
                compare = location -> prev; // Star comparing with the previous item

                // Move through the list, comparing backwards
                while (compare != nullptr && compare -> project_priority > temp_priority) {
                    // Moves projects forward by one spot to create space for placing the current project in its appropriate location
                    compare -> next -> project_name = compare -> project_name;
                    compare -> next -> project_priority = compare -> project_priority;
                    compare = compare -> prev;
                }

                // Places the current project into the identified location
                if (compare == nullptr) {  // If compare has moved past the first project, insert at the head

                    temp_headOfemp -> head -> project_name = temp_name;
                    temp_headOfemp -> head -> project_priority = temp_priority;
                }

                else {  // If not, place the project right after the point where the compare stopped

                    compare -> next -> project_name = temp_name;
                    compare -> next -> project_priority = temp_priority;
                }

                location = location -> next;  // Move to the next element to sort
            }
        }
        temp_headOfemp = temp_headOfemp -> down;  // Move to the next employee
    }
}

EmployeeProject2DLL::EmployeeProject2DLL() {  // default constructor for creating an empty 2DLL list
    headOfProject2DLL = nullptr;
}

bool EmployeeProject2DLL::isEmployeeAssignedToProject (string employee_name, string project_name)  {
// This function takes 2 strings as parameters
// It determines if a project has previously been allocated to a certain employee or not

    if (headOfProject2DLL == nullptr) {  // If list is empty, return false
        return false;
    }

    else {  // If list is not empty

        if (findEmployeeW_Name(employee_name) != nullptr) {  // It tries to find an employee with the given name by "findEmployeeW_Name" function
                                                                    // If the returned value is not nullptr, it indicates that the employee exists
            if (findProjectW_Name(findEmployeeW_Name(employee_name),project_name) != nullptr ) {  // If there is a project associated with the employee,
                                                                                                                       // it will return true
                return true;
            }
        }

        return false;  // If either no employee is found with the given name or the employee is found but not assigned to the specified project, it will return "false"
    }
}

bool EmployeeProject2DLL::updateProjectPriority(string employee_name, string project_name, int & proj_priority) {
// This function takes 2 strings and int as parameters
// This function operates under the assumption that the employee has already been allocated the project,
// with its primary goal being to update the project's priority level.

    int temp2 = proj_priority;

    if (findEmployeeW_Name(employee_name) != nullptr) {  // If there is an employee with the given name (found by "findEmployeeW_Name" function), progress will continue
        if (findProjectW_Name(findEmployeeW_Name(employee_name),project_name) != nullptr ) {  // If there is a project associated with the employee

            ProjectNode * temp = findProjectW_Name(findEmployeeW_Name(employee_name),project_name);

            if ( temp -> project_priority == proj_priority) { // It compares the existing project priority with the new priority value

                if (temp->project_name == project_name) {  //If they are the same, it prints a message and returns false

                    cout << "The project priority is already the same as the new priority." << endl;
                    return false;
                }
                else {  // If there's another project with the same priority but a different project name, it prints a message and returns false.

                    cout << "The project priority has not been updated because there is another project with the same priority." << endl;
                    return false;
                }
            }
            else {  // If the existing and new priority values different, the project's priority will be updated with the new value (temp2)
                    // Then, it will sort the projects through "sort_projects" function and will return true

                proj_priority = temp -> project_priority;
                temp -> project_priority = temp2;
                sort_projects (employee_name);
                return true;
            }
        }
    }

    return false;  //if no update occurs, either due to the employee or project not being found,
                   // or if the priority does not need updating or cannot be updated due to conflicts.
}

bool EmployeeProject2DLL::assignEmployeeToProject(string employee_name, string project_name , int project_priority ) {
// This function takes 2 string and int as parameters
// If it is possible, the aim of this function is to assign the project to the employee

    if (findEmployeeW_Name(employee_name) != nullptr) { // If there is an employee with the given name (found by "findEmployeeW_Name" function), progress will continue
        if (findProjectW_Name(findEmployeeW_Name(employee_name),project_name) == nullptr ) { // If there is no project associated with the employee

            ProjectNode * temp = findProjectW_Name(findEmployeeW_Name(employee_name),project_name);
            EmployeeNode * employee  = findEmployeeW_Name(employee_name);
            ProjectNode * traverse = employee -> head;

            if (Prio_check(employee_name,project_priority)) { // It checks for priority conflicts with Prio_check() function.
                                                                      // If there is another project with the same priority, it prints a message and returns false

                cout << "The project has not been added because there is another project with the same priority." << endl;
                return false;
            }

            else {

            // If there is no priority conflict, it tries to assign the project to the employee's project list.
            // If the employee has no projects, it directly assigns the project as both the head and tail.
            // If the employee has existing projects, it appends the new project to the end of the list and updates the tail pointer. Then it sorts the list.

                while ( traverse != nullptr ) {
                    if (traverse -> next == nullptr ) {

                        traverse -> next = new ProjectNode(project_name, project_priority, nullptr, nullptr);
                        traverse -> next -> prev = traverse;
                        employee -> tail = traverse -> next;
                        sort_projects(employee_name); // After adding project, it sorts the projects with this function
                        return true;
                    }
                    traverse = traverse -> next;
                }

                employee -> head = new ProjectNode(project_name, project_priority, nullptr, nullptr);
                employee -> tail = employee -> head;

                return true;
            }
        }
    }

    else { // If the employee doesn't exist (findEmployeeW_Name returns nullptr), it creates new node and add it to employee list
           // It then directly assigns the new project as the head and tail of the employee's project list.
           // If this is the very first employee or if the new employee's name comes before the current head in alphabetical order,
           // the new employee is added at the beginning of the list.
           // Otherwise, it finds the correct spot based on alphabetical order and inserts the new employee accordingly.

        EmployeeNode * newEmployee = new EmployeeNode(employee_name); // Create a new "EmployeeNode"

        if (!headOfProject2DLL || employee_name < headOfProject2DLL -> employee_name) {
            newEmployee -> down = headOfProject2DLL;
            headOfProject2DLL = newEmployee;
        }

        else { // If the added employee are not in the beginning, program iterates through the list to find the correct insertion point
               // Once the correct spot is found, newEmployee is inserted into the list by updating the down pointers, ensuring the list remains sorted.
            EmployeeNode * temp_emp = headOfProject2DLL;

            while ( temp_emp -> down && temp_emp -> down -> employee_name < employee_name) {
                temp_emp = temp_emp -> down;
            }
            newEmployee -> down = temp_emp -> down;
            temp_emp -> down = newEmployee;
        }

        // A new ProjectNode is dynamically allocated with the specified project_name and project_priority.
        // Then, this node is assigned as both the head and tail of the new employee's project list, signifying that it is presently the sole project attributed to this employee.
        newEmployee -> head = new ProjectNode (project_name, project_priority, nullptr, nullptr);
        newEmployee -> tail = newEmployee -> head;

        return true;
    }
    return false;
}

void EmployeeProject2DLL::withdrawEmployeeFromProject (string employee_name, string project_name , int & project_priority ) {
// This function takes 2 string and int as parameters
//  It merely removes the specified project node from the employee's list, while also providing the project's priority back via a reference parameter.

    if (findEmployeeW_Name(employee_name) != nullptr) {   // If there is an employee with the given name (found by "findEmployeeW_Name" function), progress will continue
        if (findProjectW_Name(findEmployeeW_Name(employee_name),project_name) != nullptr ) {  // If there is a project associated with the employee

            // Once the project node (toBeDeleted) is found, its priority is stored in project_priority
            ProjectNode * toBeDeleted = findProjectW_Name(findEmployeeW_Name(employee_name),project_name);
            project_priority = toBeDeleted -> project_priority;

            EmployeeNode * emp = findEmployeeW_Name(employee_name);

            if (toBeDeleted == emp -> head) { //If toBeDeleted is the first project (emp->head)
            // it updates the head pointer to the next project and sets the new head's previous pointer to nullptr. It then deletes the toBeDeleted node.

                emp -> head = toBeDeleted->next;
                delete toBeDeleted;
                if (emp -> head != nullptr) {  // If there is a new head, update its prev pointer
                    emp -> head -> prev = nullptr;
                }
            }

            else if (toBeDeleted -> next == nullptr) {  // If toBeDeleted is last project  it updates the tail pointer to the previous project and
            // sets the new tail's next pointer to nullptr. It then deletes the toBeDeleted node.

                emp -> tail = toBeDeleted -> prev;
                emp -> tail -> next = nullptr;
                delete toBeDeleted;
            }

            else { // If the project is neither the first nor the last, it connects the previous
                   // and next projects directly, effectively removing toBeDeleted from the chain, and then deletes the node

                ProjectNode * previous = toBeDeleted -> prev;
                ProjectNode * next1 = toBeDeleted -> next;

                previous -> next = toBeDeleted -> next;
                next1 -> prev = toBeDeleted -> prev;
                delete toBeDeleted;
            }

            if ( findEmployeeW_Name(employee_name) -> head == nullptr ) {  // Check whether employee has any project or not
                // If employee has no project, delete employee
                // If the project to be deleted is the only project that employee has, then the employee node has to be deleted as well

                EmployeeNode * temp = headOfProject2DLL;
                EmployeeNode * prev;

                if (temp != nullptr && temp -> employee_name == employee_name) {  // If the head node itself holds the name to be deleted
                    headOfProject2DLL = temp -> down; // Update the head
                    delete temp;       // Free old head
                    return;
                }

                while (temp != nullptr && temp -> employee_name != employee_name) {  // Search for the name to be deleted, keep track of the previous node
                    prev = temp;
                    temp = temp -> down;
                }

                if (temp == nullptr) { // If name is not present in the linked list
                    return;
                }

                prev -> down = temp -> down;  // Unlink the node from the linked list

                delete temp;  // Delete the employee node
            }
        }
    }
}

void EmployeeProject2DLL::clear() {
// This function responsible for deallocating the dynamically-allocated memory of the entire 2DHLL structure.

    while (headOfProject2DLL != nullptr) { // Iterate through each employee node
        EmployeeNode* last_Emp = headOfProject2DLL; // Keep the present employee on board until the projects are completed before proceeding with deletion.

        while (last_Emp -> head != nullptr) {  // Iterate over each project node of present employee

            ProjectNode * last_Proj = last_Emp -> head;  // Keep the present project to delete
            last_Emp -> head = last_Proj -> next;  // Move to the next project
            delete last_Proj;  // delete the current employee
        }

        headOfProject2DLL = last_Emp -> down;  // Move to the next employee
        delete last_Emp;  // delete the present employee
    }
    headOfProject2DLL = nullptr; // Terminate the cleanup by setting head to nullptr
}

void EmployeeProject2DLL::printTheEntireList() {
// This function prints the content of the entire 2DHLL structure in a predefined format

    if (headOfProject2DLL == nullptr) { // Directly check if the list is empty and print a message if so
        cout << "The list is empty." << endl;
        return;
    }

    else {
        for (EmployeeNode * employee = headOfProject2DLL; employee != nullptr; employee = employee -> down) {  // Iterate over the employee linked list with a "for" loop like a vector or an array
            cout << employee -> employee_name << ":";

            for (ProjectNode * project = employee -> head; project != nullptr; project = project -> next) {  // Iterate over the project linked list with a "for" loop
                cout << " (" << project -> project_name << ", " << project ->project_priority << ")";
            }
            cout << endl;  // New line after listing all projects for an employee
        }
    }
}

void EmployeeProject2DLL::print_forward (ProjectNode * ptr) {
// This function takes ProjectNode pointer
// It can print linked list desired form

    if (ptr != nullptr) {
        cout << "(" << ptr -> project_name << ", " << ptr -> project_priority << ") ";
        print_forward (ptr -> next); //I used recursive method
    }
}

void EmployeeProject2DLL::print_reverse (ProjectNode * ptr) {
// This function takes ProjectNode pointer
// It can print whole linked list desired form

    if (ptr != nullptr) {
        print_reverse(ptr -> next);  // I used recursive method
        cout << "(" << ptr -> project_name << ", " << ptr -> project_priority << ") ";

    }
}

void EmployeeProject2DLL::printEmployeeProjects (string name,  int sequence) {
// This function takes string and int as parameters
// It prints the projects of that employee in an ascending (1) or descending (0) order according to the priorities of the projects

    EmployeeNode * employee = findEmployeeW_Name(name);  // Attempt to find the employee by name

    if ( headOfProject2DLL == nullptr) {  // Check if the employee list is empty
        cout << "There are no employees in the list." << endl;
        return;
    }

    else {   // If the employee doesn't exist in the list
        if(employee == nullptr) {
            cout << "The employee is not in the list."<< endl;
            return;
        }
    }

    if (sequence == 1) {  // If sequence is 1, print projects in ascending order based on their priorities
        print_forward (employee->head);  // print from head to tail
    }

    else if (sequence == 0) {  // If sequence is 0, print projects in descending order based on their priorities
        // Find the tail to reverse printing
        print_reverse (employee -> head);  // print from tail to head
    }

    cout << endl;
}

void EmployeeProject2DLL::undo(char operation, string name, string project, int priority) {
// This function takes char, 2 string and an int as parameters.
// It recognizes the operation type and based on that, it performs an action that reverses that operation.
// It also displays a message indicating

    if (operation == 'a')
    {
        cout<< "Undoing the assignment of a project." << endl;
        withdrawEmployeeFromProject(name,project,priority); // Calls the function to remove the employee from the specified project
    }

    else if (operation == 'w')
    {
        cout<< "Undoing the withdrawal of a project." << endl;
        assignEmployeeToProject(name,project,priority);  // Calls the function to assign the employee back to the specified project
    }

    else if (operation == 'u')
    {
        cout<< "Undoing the update of a project priority." << endl;
        updateProjectPriority(name,project,priority); // Calls the function to revert the project's priority to its previous state
    }
}