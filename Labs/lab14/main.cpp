//
//  main.cpp
//  lab14
//
//  Created by David Slakter on 5/4/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

bool evenBinary(int n){
    int bin = n % 2;
    if (n == 0){
        return true;
    }
    if(bin == 0){
        return evenBinary(n/2);
    }
    else{
        return !evenBinary(n/2);
    }
}

 struct Node {
    Node(int data = 0, Node* next = nullptr, Node* prev = nullptr)
    : data(data), next(next), prev(prev) {}
    
    int data;
    Node* next;
    Node* prev;
};

struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

int max(TNode* root) {
    
    if (root == nullptr){
        throw invalid_argument("root is null");
    }
    
    if(root->right && root->left){
        return std::max(std::max(max(root->right), max(root->left)), root->data);
    }
    else if (root->right){
        return std::max(max(root->right), root->data);
    }
    else if (root->left){
        return std::max(max(root->left), root->data);
    }
    else{
        return root->data;
    }
    
    
    

}



Node* addLists(Node* l1, Node* l2){
   
   if (l1 && l2){
        return new Node(l1->data + l2->data, addLists(l1->next, l2->next));
   }
   if (l1){
        return new Node(l1->data, l1->next);
   }
   if (l2){
        return new Node(l2->data, l2->next);
   }
   return nullptr;
   
}

int towers(int numDisks, char start, char target, char spare){
    if (numDisks == 0) return 0;
    else{
        int moves = 0;
        moves += (towers(numDisks - 1, start, spare, target));
        moves += (towers(numDisks - 1, spare, target, start));
    
        return ++moves;
    }
}

bool palindrome(char arr[], int len){
    if (len == 1){
        return true;
    }
    if (*arr == *(arr + len - 1)) {
        return palindrome(arr + 1, len - 2);
    }
    else{
        return false;
    }

}

//n = 0; return c
//n = 1; return c
//n = 2; return acbcc
//n = 3; return acbcc
//n = 4; return aacbacbccc
//n = 5; return aacbacbccc
//n = 6; return aacbacbccc
//n = 7; return aacbacbccc
//n = 8; return aaacbccbacbcccbaacbccbacbcccc
//n = 9; return aaacbccbacbcccbaacbccbacbcccc
//n = 10; return aaacbccbacbcccbaacbccbacbcccc
void mystery(int n) {
   if (n > 1) {
      cout << 'a';
      mystery(n/2);
      cout << 'b';
      mystery(n/2);
   }
   cout << 'c';
}



int main() {

    cout << evenBinary(3) << endl;
    cout << evenBinary(4) << endl;
    cout << evenBinary(5) << endl;
    cout << evenBinary(6) << endl;
    cout << evenBinary(7) << endl;

    char s[] = "racecar";
    if (palindrome(s, 7)) {
        cout << "racecar is palindrome!\n";
    }
    else{
        cout << "not palindrome\n";
    }
    
    Node* list1 = new Node(3, new Node(2));
    Node* list2 = new Node(4, new Node(5));
    
    Node* sumList = addLists(list1, list2);

    cout << sumList->data << ' ' << sumList->next->data << endl;
    
     TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    cout << max(&f) << endl;
    
    cout << "testing error handling:" << endl;
    try {
        TNode* t = nullptr;
        max(t);
    }
    catch (const exception& e){
        cout << e.what() << endl;
    }
    
    
    // Testing towers
    cout << towers(1, 'a', 'b', 'c') << endl;
    cout << towers(2, 'a', 'b', 'c') << endl;
    cout << towers(3, 'a', 'b', 'c') << endl;
    cout << towers(4, 'a', 'b', 'c') << endl;
    cout << towers(5, 'a', 'b', 'c') << endl;
    cout << towers(6, 'a', 'b', 'c') << endl;
    cout << towers(7, 'a', 'b', 'c') << endl;
    cout << towers(8, 'a', 'b', 'c') << endl;
    cout << towers(9, 'a', 'b', 'c') << endl;
    cout << towers(10, 'a', 'b', 'c') << endl;
    
    
    //mystery
    for(int i = 0; i < 11; ++i){
        mystery(i);
        cout << endl;
    }
    
    string test = "3232";
    test[0] = '2';
    test[2] = '2';
    
    map<int, char> m1;
    m1[0] = 'a';
    m1[1] = 'b';
    for (map<int,char>::iterator it = m1.begin(); it != m1.end(); ++it){
        cout << it->second;
    }
    
    cout << "test: " << test << endl;
}
