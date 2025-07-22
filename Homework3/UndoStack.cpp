// Huseyin Eren YILDIZ - 31047

#include "UndoStack.h"

UndoStack::UndoStack() { // Creates an empty stack.

    top = nullptr;
}

void UndoStack::push(char operation, string name, string project, int priority) {
// Member function "push" pushes the argument onto the stack.
/* Begin: code taken from week5-PowerPoint (3-stacksqueues page-23)
 * And updated according to this program */

    StackNode* node;  // Declares a pointer to a new stack node.

    if (isEmpty()) { // If the stack is empty

        // Creates a new StackNode with the given operation, name, project, and priority to top. Since the stack is empty, the next node pointer is nullptr
        top = new StackNode(operation,name,project,priority, nullptr);
    }

    else { // The stack is not empty.

        // Creates a StackNode with the given data and sets its next node pointer to the current top of the stack
        node = new StackNode(operation,name,project,priority,top);
        top = node;  // Updates the top pointer to point to the newly created node, effectively making it the new top of the stack
    }
}
/* End: code taken from week5-PowerPoint (3-stacksqueues page-23) */

bool UndoStack::isEmpty() {
// Member function isEmpty returns true if the stack is empty, or false otherwise.
/* Begin: code taken from week5-PowerPoint (3-stacksqueues page-25)
 * And updated by updated according to this program */

    bool status;

    if (top == nullptr) {  // If stack is empty
        status = true;
    }

    else {    // If the 'top' pointer points to a node, then the stack is not empty
        status = false;
    }

    return status;

/* End: code taken from week5-PowerPoint (3-stacksqueues page-25) */
}


void UndoStack::pop(char & operation, string & name, string & project, int & priority) {
//this function deletes the last entered node from the stack
//at the same time it returns the values of the node as reference parameters

    StackNode* toBeDeleted = top; //  Hold the top node of the stack that is going to be deleted
    top = top -> next;  // Moves the top pointer to the next node

    /* Begin: code taken from week5-PowerPoint (3-stacksqueues page-24)
     * And updated by updated according to this program  */

    operation = toBeDeleted -> operation; // Takes the operation character
    name = toBeDeleted -> employee_name;  // Takes the employee's name
    project = toBeDeleted -> project_name;  // Takes the project name
    priority = toBeDeleted -> project_priority;  // Takes the project priority

    /* End: code taken from week5-PowerPoint (3-stacksqueues page-24) */

    delete toBeDeleted;  // Free the memory of the node that's been popped off.
}

void UndoStack::clear() {
// This function takes no parameters, and is responsible for deallocating the dynamically-allocated memory of the stack

    while (top != nullptr) {  // Loops until the stack is empty (i.e., top is nullptr).

        // Temporarily stores the node to delete, allowing the top pointer to advance to the next node.
        StackNode* temp = top;
        top = top->next; // Moves the top pointer down the stack before deleting the node.

        delete temp; // Deletes the node, freeing up its memory.
    }
}

