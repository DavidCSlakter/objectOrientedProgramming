//
//  main.cpp
//  lab13
//
//  Created by David Slakter on 4/27/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//
// rec13_test.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <set>         // task 20
#include <map>         // task 22

using namespace std;

void printList(const list<int>& theList) {
    for(list<int>::const_iterator it = theList.begin(); it != theList.end(); ++it){
        cout << ' ' << *it;
    }
}

void printList2(const list<int>& theList){
    for (int x: theList){
        cout << ' ' << x;
    }
}

void printListAuto(const list<int>& theList){
    for (auto it = theList.begin(); it != theList.end(); ++ ++it){
        cout << ' ' << *it;
    }
}


list<int>::const_iterator findVal(const list<int>& theList, int theVal){

    for (list<int>::const_iterator it = theList.begin(); it != theList.end(); ++it){
        if(*it == theVal){
            return it;
        }
    }
    return theList.end();
}

auto findVal2(const list<int>& theList, int theVal){
    for (auto it = theList.begin(); it != theList.end(); ++it){
        if (*it == theVal){
            return it;
        }
    }
    return theList.end();
}

bool isEven(int num){
    return (num % 2 == 0);
}

class IAmFunctor{
public:
    bool operator() (int num){
        return num % 2 == 0;
    }
};

list<int>::const_iterator ourFind(list<int>::iterator begin,
const list<int>::const_iterator end, int theVal){
    cout << "using my find: ";
    
    while (begin != end){
        if(*begin == theVal){
            return begin;
        }
        ++begin;
    }
    return end;
}

class animal{

    protected:
        void speak(){
            cout << "sdL";
        }
};
class dog: public animal{
    
};
class cat: public animal{
    
    void changespeak(const dog& d){
        d.speak();
    }
};




template <typename T, typename I>
T ourFindTemplate(T begin, T end, I theVal){
    cout << "using my find Template: ";
    
    while (begin != end){
        if(*begin == theVal){
            return begin;
        }
        ++begin;
    }
    return end;
}

int main() {

    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> v;
    v.push_back(4);
    v.push_back(3);
    v.push_back(2);
    v.push_back(1);
    for(int x: v){
        cout << x << ' ';
    }
    cout << endl;
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> myList(v.begin(), v.end());
    cout << "myList contains:";
    for (list<int>::iterator it = myList.begin(); it != myList.end(); ++it){
        cout << ' ' << *it;
    }
    cout << endl;
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v.begin(), v.end());
    
    cout << "my vector: ";
    for(int x: v){
        cout << x << ' ';
    }
    cout << endl;
    
    cout << "my list: ";
    for (list<int>::iterator it = myList.begin(); it != myList.end(); ++it){
        cout << ' ' << *it;
    }
    cout << endl;
    
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    cout << "every other element of vec: ";
    for (size_t i = 0; i < v.size(); i += 2){
        cout <<  ' ' << v[i];
    }
    cout << endl;
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    cout << "every other element of list: ";
    for (size_t i = 0; i < myList.size(); i += 2){
    //    cout <<  ' ' << myList[i];
    }
    cout << endl;
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    
    for (vector<int>::iterator it = v.begin(); it != v.end(); it += 2){
        cout << ' ' << *it;
    }
    cout << endl;

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    
    for (list<int>::iterator it = myList.begin(); it != myList.end(); ++ ++it){
    //it++, it++
        cout << ' ' << *it;
    }
    cout << endl;

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    
    myList.sort();
    for (list<int>::iterator it = myList.begin(); it != myList.end(); ++it){
        cout << ' ' << *it;
    }
    cout << endl;
    
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    
    printList(myList);
    cout << endl;
    
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printList2(myList);
    cout << endl;
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    
    printListAuto(myList);
    cout << endl;

    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    
    list<int>::const_iterator result = findVal(myList, 3);
    
    if (result != myList.end()){
        cout << "value found";
    }
    else{
        cout << "value not found";
    }

    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    
    auto result2 = findVal2(myList, 3);
    
    if(result2 != myList.end()){
        cout << "value found";
    }
    else{
        cout << "value not found";
    }

    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    auto result3 = find(myList.begin(), myList.end(), 3);
    
    if(result3 != myList.end()){
        cout << "value found";
    }
    else{
        cout << "value not found";
    }
    
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    
    auto result4 = find_if(myList.begin(), myList.end(), isEven);
    
    if(result4 != myList.end()){
        cout << "value found";
    }
    else{
        cout << "value not found";
    }

    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    IAmFunctor isEvenFunctor;
    auto result5 = find_if(myList.begin(), myList.end(), isEvenFunctor);
    
    if(result5 != myList.end()){
        cout << "value found";
    }
    else{
        cout << "value not found";
    }

    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    
    auto result10 = find_if(myList.begin(), myList.end(), [] (int theVal) { return theVal % 2 == 0; });
    if(result10 != myList.end()){
        cout << "value found";
    }
    else{
        cout << "value not found";
    }

    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int arr[4];
    
    copy(v.begin(), v.end(), arr);
    
    cout << "array: ";
    for(int x: arr){
        cout << ' ' << x;
    }
    cout << endl;
    
    auto result6 = find(arr, arr + 4, 3);
     if(result6 != (arr + 4)){
        cout << "value found"<< endl;
    }
    else{
        cout << "value not found" << endl;
    }
    
    
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    
    auto result7 = ourFind(myList.begin(), myList.end(), 6);
    if(result7 != myList.end()){
        cout << "value found" << endl;
    }
    else{
        cout << "value not found" << endl;
    }


    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    auto result8 = ourFindTemplate<list<int>::iterator, int>(myList.begin(), myList.end(), 4);
    
    if(result8 != myList.end()){
        cout << "value found" << endl;
    }
    else{
        cout << "value not found" << endl;
    }

    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing
    cout << "Task 21:\n";
    
    vector<string> seenWords;
    
    ifstream ifs("pooh.txt");
    if (!ifs) {
        cerr << "failed to open file\n";
        exit(1);
    }
    
    string word;
    
    
    while (ifs >> word) {
        bool found = false;
        
        for(const string& s: seenWords){
            if (word == s){
                found = true;
            }
        }
        if(!found){
            seenWords.push_back(word);
        }
    }
    
    ifs.close();
    
    
    cout << "vector size: " << seenWords.size() << endl;
    
    cout << "contents: ";
    for (const string& s: seenWords){
        cout << s << ' ';
    }
    cout << endl;

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    
    set<string> seenWords2;
    
    ifstream file2("pooh.txt");
    if (!file2) {
        cerr << "failed to open file\n";
        exit(1);
    }

    string word2;
    
    while (file2 >> word2) {
        seenWords2.insert(word2);
    }
    file2.close();
    cout << "set size: " << seenWords2.size() << endl;
    
    cout << "contents: ";
    for (const string& s: seenWords2){
        cout << s << ' ';
    }
    cout << endl;

    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    
    ifstream file3("pooh.txt");
    if (!file3) {
        cerr << "failed to open file\n";
        exit(1);
    }
    
    map<string, vector<int>> wordMap;
    string word3;
    int pos = 1;
    while (file3 >> word3) {
    
        wordMap[word3].push_back(pos);
        pos += 1;
    }
    file2.close();
    
    for (const auto& pair: wordMap){
    
        cout << pair.first << " : ";
        
        for (auto i: pair.second){
            cout << i << ' ';
        }
        
        cout << endl;
    }

    
    cout << "=======\n";
}
