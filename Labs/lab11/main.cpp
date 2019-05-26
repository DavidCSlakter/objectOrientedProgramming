//
//  main.cpp
//  lab11
//
//  Created by David Slakter on 4/13/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
#include <cstdlib> // To allow NULL if no other includes
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

struct Node {
    Node(int data = 0, Node* link = NULL) : data(data), next(link) {}
    int data;
    Node* next;
};

void printList(Node* head){
    if (!head){
        cout << "failed to match" << endl;
    }
    else{
        while(head){
            cout << head->data << ' ';
            head = head->next;
        }
        cout << endl;
    }
    
}

void listInsertHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
}

// Should free up your nodes, of course...
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// This might be useful for setting up test cases. Feel free to use it
// or not as you like. Example of using would be:
// Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listInsertHead(result, vals[index-1]);
    }
    return result;
}

/*
Params: include the number that you want to add after, the head of the original list and the head of the list
you want to splice inside it.
*/
void spliceListAfter(Node* listHead, Node* spliceHead){
    if (spliceHead){
        Node* nextNode = listHead->next;
        listHead->next = spliceHead;
        while (spliceHead->next != nullptr) {
            spliceHead = spliceHead->next;
        }
        spliceHead->next = nextNode;
    }
}

Node* isSublist(Node* outterHead, Node* innerHead){
    Node* startInner = innerHead;
    Node* substart = nullptr;
    while(outterHead && innerHead){
        if (outterHead->data == innerHead->data){
            substart = outterHead;
            outterHead = outterHead->next;
            innerHead = innerHead->next;
            while(innerHead && outterHead){
                if(innerHead->data == outterHead->data){
                    outterHead = outterHead->next;
                    innerHead = innerHead->next;
                }
                else{
                    innerHead = startInner;
                    substart = nullptr;
                    break;
                }
            }
        }
        if(outterHead){
            outterHead = outterHead->next;
        }
        else if (innerHead){
            return nullptr;
        }
    }
    return substart;
}

int main() {

    cout << "Part One: " << endl;

    Node* originalList = listBuild({5, 7, 9, 1});
    
    Node* spliceList = listBuild({6, 3, 2});
    
    cout << "L1: ";
    printList(originalList);
    
    cout << "L2: ";
    printList(spliceList);
    
    cout << "Target: ";
    printList(originalList->next);
    
    cout << "Splicing L2 at target L1" << endl;
    spliceListAfter(originalList->next, spliceList);
    
    cout << "L1: ";
    printList(originalList);
    cout << "L2: ";
    printList(spliceList);
    
    listClear(originalList);
    
    cout <<  "=====================" << endl;
    
    cout << "Part Two: " << endl;
    
    //test 1
    Node* mainList = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    cout << "Target: ";
    printList(mainList);
    
    
    cout << "Attempt match: ";
    Node* subList = listBuild({1});
    printList(subList);
    
    Node* subStart = isSublist(mainList, subList);
    
    printList(subStart);
    
    //test 2: prints null
    cout << "Attempt match: ";
    Node* subList2 = listBuild({3, 9});
    printList(subList2);
    
    Node* subStart2 = isSublist(mainList, subList2);
    
    printList(subStart2);
    
    //test 3:
    cout << "Attempt match: ";
    Node* subList3 = listBuild({2, 3});
    printList(subList3);
    Node* subStart3 = isSublist(mainList, subList3);
    
    printList(subStart3);
    
    
    //test 4:
    cout << "Attempt match: ";
    Node* subList4 = listBuild({2, 4 , 5, 6, 7});
    printList(subList4);
    Node* subStart4 = isSublist(mainList, subList4);
    
    printList(subStart4);
   
   listClear(subList3);
   listClear(subList2);
   listClear(mainList);
   listClear(subList);
    
}
