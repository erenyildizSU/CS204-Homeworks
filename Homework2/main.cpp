// Huseyin Eren YILDIZ, 31047
// Homework 2

/******************************************************************************
Purpose: This program reads a file line by line. Then, it adds elements to linked lists according to some rules
Author: HUSEYIN EREN YILDIZ - 31047
Date: 19/03/2024
******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// A structure for the "likes"
struct NodeLike {
    string subject;
    string object;
    NodeLike *next;     // pointer for the next node

    //Default constructor
    NodeLike ()
            :subject(" "), object(" "), next(nullptr)
    {}

    //constructor with 3 parameters
    NodeLike(string struct_subject, string struct_object, NodeLike* struct_next = nullptr){
        subject = struct_subject;
        object = struct_object;
        next = struct_next;
    }
};


// A structure for the "taken"
struct NodeTaken {
    string name;
    NodeTaken *next;    // pointer for the next node

    //Default constructor
    NodeTaken ()
            :name(" "), next(nullptr)
    {}

    //constructor with 2 parameters
    NodeTaken(string struct_name, NodeTaken* struct_next = nullptr){
        name = struct_name;
        next = struct_next;
    }
};


bool IsItInTakenList(NodeTaken *taken, const string& cons_name) {
// This function takes NodeTaken pointer and a string as a parameter
// It checks if the name is in the taken list. If there is a match, it will return true. Otherwise, it will return false
    for (NodeTaken* loc = taken; loc != nullptr; loc = loc->next) { // Iterate over the list with a "for" loop
        if (loc-> name == cons_name) {
            return true;
        }
    }
    return false;
}

bool BothInLikeList (NodeLike *likes, const string & cons_subject, const string & cons_object) {
// This function takes NodeLike pointer and two string as parameters
// It checks if the both string is in the like list. If there is a match, it will return true. Otherwise, it will return false
    for (NodeLike* loc = likes; loc != nullptr; loc = loc->next) { // Iterate over the linked list with a "for" loop like a vector or an array
        if (loc -> subject == cons_subject && loc->object == cons_object ) {
            return true;
        }
    }
    return false;
}

bool SubjectInLikeList (NodeLike *likes, const string & cons_subject) {
// This function takes NodeLike pointer and a string as parameters
// It checks if the string is in the like list as a subject. If there is a match, it will return true. Otherwise, it will return false
    while (likes != nullptr) {
        if (likes->subject == cons_subject) {
            return true;
        }
        likes = likes->next;
    }
    return false;
}

void addLikesList (NodeLike* & likeList, const string & cons_subject, const string & cons_object) {
// This function takes NodeLike pointer and two string as parameters.
// It adds the node at the end of the list or between two nodes
    NodeLike *ptr = likeList;   // loop variable
    NodeLike *LastIndex = nullptr;  // To find last index of specific node
    NodeLike *LastIndexnext = nullptr;

    // If list is empty, it will create new node and assign subject and object on it to the list.
    if (likeList == nullptr)
    {
        likeList = new NodeLike(cons_subject,cons_object, nullptr);
    }
    else {   // If list is not empty, program has 2 possibilities.
             // It may add the node at the end of the list or,
             // It may add the node between two nodes in the list
        while (ptr != nullptr) {  // This part adds the node at the end of the list
            if (ptr->subject == cons_subject) {
                LastIndex = ptr;
            }
            ptr = ptr->next; // iterate over list
        }
        if (LastIndex != nullptr) {
            LastIndexnext = LastIndex->next;
            LastIndex->next = new NodeLike(cons_subject, cons_object, LastIndexnext);
        }

        else {  // This part adds the node between node according to the rules
            ptr = likeList;
            while (ptr->next != nullptr) {
                ptr = ptr->next; // iterate over list
            } // post-condition: new node to be inserted just after the node ptr points
            ptr->next = new NodeLike(cons_subject, cons_object, nullptr);
        }
    }
}

void addTakenList (NodeTaken* & takenList , const string & cons_name) {
// This function takes NodeTaken pointer and a string as parameters.
// It adds the node to the "taken" linked list in ascending alphabetical order

    // If the list is empty or the new node should be first, it will handle with this case
    // It will add new node to the beginning of the taken list

    /* Begin: code taken from week3-PowerPoint (2.2-pointers-linked lists page-7) */
    if (takenList == nullptr || cons_name <= takenList->name) {
        NodeTaken* Node = new NodeTaken(cons_name); // Updated these part according to program flow
        Node->next = takenList;
        takenList = Node;
        /* End: code taken from week3-PowerPoint (2.2-pointers-linked lists page-7) */

        cout << "Added to taken list: " << cons_name << endl;
        return;
    }

    NodeTaken* last = nullptr;  // to point to previous node
    NodeTaken* head = takenList;

    /* Begin: code taken from week3-PowerPoint (2.2-pointers-linked lists page-7) */
    // It will find the position that fits the rule (ascending alphabetical order) to add the new node
    while (head != nullptr && head->name < cons_name) {
        last = head;   //hold onto previous node, so we do not pass too far
        head = head -> next;
    } // post-condition: new node to be inserted between prev and ptr
    /* End: code taken from week3-PowerPoint (2.2-pointers-linked lists page-7) */

    // Add the new node
    NodeTaken* Node = new NodeTaken(cons_name);
    last -> next = Node;
    Node -> next = head;

    cout << "Added to taken list: " << cons_name << endl;
}

void deleteInLikesList(NodeLike*& likes, const string& sub_obj) {
    NodeLike* location = likes;
    NodeLike* last = nullptr;

    while (location != nullptr) {
        if (location->subject == sub_obj || location->object == sub_obj) {
            NodeLike* temp = location;
            if (location == likes) {
                likes = location->next;
            } else {
                last->next = location->next;
            }
            delete temp;
            location = likes;
        } else {
            if (location->subject == sub_obj) {
                NodeLike* temp = location;
                if (location == likes) {
                    likes = location->next;
                } else {
                    last->next = location->next;
                }
                delete temp;
                location = likes;
            } else if (location->object == sub_obj) {
                NodeLike* temp = location;
                if (location == likes) {
                    likes = location->next;
                } else {
                    last->next = location->next;
                }
                delete temp;
                location = likes;
            } else {
                last = location;
                location = location->next;
            }
        }
    }
}

void printTaken (NodeTaken *ptr, bool isFirst = true) {
// This function takes NodeTaken pointer and a bool as a parameter
// It can print whole linked list desired form
    if (isFirst)  // If it is first call of function then print this statement
        cout << "Taken list:";

    if (ptr != nullptr) {
        cout << " " << ptr->name;
        printTaken(ptr->next, false); //I used recursive method
    }
}

void printLikes (NodeLike *ptr, bool isFirst = true) {
// This function takes NodeLike pointer and a bool as a parameter
// It can print whole linked list desired form
    if (isFirst)  // If it is first call of function then print this statement
        cout << "Likes list:";

    if (ptr != nullptr) {
        cout << " (" << ptr->subject << ", " << ptr->object << ")";
        printLikes(ptr->next, false);  //I used recursive method
    }
}

void DeleteLikesList (NodeLike *likes) {
// This function takes NodeLike pointer as parameter
// Delete "likes" linked list
/* This code taken from "linkedlist.cpp" and updated according to this program */
    NodeLike * ptr;
    while (likes != nullptr) {
        ptr = likes;
        likes = likes -> next;
        delete ptr;
    }
}

void DeleteTakenList (NodeTaken *taken) {
// This function takes NodeLike pointer as parameter
// Delete "taken" linked list
/* This code taken from "linkedlist.cpp" and updated according to this program */

    NodeTaken * ptr;
    while (taken != nullptr) {
        ptr = taken;
        taken = taken -> next;
        delete ptr;
    }
}


int main() {
    string fileName,line,subject,object;
    ifstream inputFile;
    int line_number = 1;
    NodeLike *LikesHead = nullptr;
    NodeTaken *TakenHead = nullptr;

    cout << "Please enter the file name: " << endl; // It asks the user for the file name
    cin >> fileName;

    inputFile.open(fileName);  // Opens the file where the user entered the name

    while(!inputFile.is_open()) {    //eski odevden aldigini belirt
        cout << "Could not open the file. Please enter a valid file name:" << endl;
        cin >> fileName;
        inputFile.open(fileName);
    }

    while(getline(inputFile,line)) {
        int index = line.find("likes");  // To find object and subject in the list, index of "likes" should be found
        subject = line.substr(0,(index-1));  // until " likes"
        object = line.substr(index+6);      // index+6 means length of "likes" + space(" ")
        cout << "Read line number (" << line_number << "): " << line << endl;

        if (line_number == 1){  //In the beginning, linked lists are empty. So it will be added to the likes list without any conditions
            LikesHead = new NodeLike (subject,object);
            cout << line << " relation has been added to the likes list."<<endl;
        }
        else {  // After the first line:
            if (IsItInTakenList(TakenHead,subject) || IsItInTakenList(TakenHead,object)) {
                // If subject or object or both are already in taken list
                cout << "Either "<< subject <<" or "<< object <<" or both is/are already taken, so the like relation is not added."<< endl;
            }
            else {  // If subject or object or both are not in taken list
                if ( (BothInLikeList(LikesHead,subject,object)) ) {
                    // If (Subject, Object) pair is in the likes list
                    cout << line <<" relation already exists in the likes list, so it is not added to it."<<endl;
                }
                else {   // If (Subject, Object) pair is not in the likes list

                    if (BothInLikeList(LikesHead,object,subject)){  // It will check the reverse relationship of this pair (Object, Subject)
                        // If it is in the likes list, then there is a match between this subject and the object
                        // (Subject, Object) pair will not be added to the likes linked list
                        // Delete each node in the likes linked list that contains either the subject or the object of that matched relationship
                        // Add names to the "taken" linked list in ascending alphabetical order
                        cout << "Match found: "<<subject<<" likes " << object <<" and "<< object<<" likes " << subject << "."<<endl;
                        deleteInLikesList(LikesHead,object);
                        deleteInLikesList(LikesHead,subject);
                        addTakenList(TakenHead,subject);
                        addTakenList(TakenHead,object);
                        cout << "Any node that has "<< subject <<" or "<< object <<" or both in it is removed from the likes list."<< endl;
                    }
                    else { // reverse relationship is not in the likes linked list
                        if (SubjectInLikeList(LikesHead,subject)) {
                            addLikesList(LikesHead,subject,object);
                            cout << line << " relation has been added to the likes list." << endl;
                        }
                        else {
                            addLikesList(LikesHead,subject,object);
                            cout << line << " relation has been added to the likes list." << endl;
                        }
                    }
                }
            }
        }
        // After the every line, it will print both linked lists
        printLikes(LikesHead);
        cout << endl;
        printTaken(TakenHead);
        cout << endl << endl;
        line_number++;  // it will increase the line number
    }

    // Since I used dynamic memory allocation in this homework, it is very crucial to properly manage the allocated area.
    // at the end of the program, delete both lists
    DeleteLikesList(LikesHead);
    DeleteTakenList(TakenHead);
    cout << "Lists are deleted and the program ends successfully." << endl;
    return 0;
}
