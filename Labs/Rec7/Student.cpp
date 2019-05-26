//
//  Student.cpp
//  Rec7
//
//  Created by David Slakter on 3/9/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include "Student.hpp"
#include <iostream>

using namespace std;

namespace BrooklynPoly {
    
        Student::Student(const string& aName): name(aName){}
    
        void Student::addCourse(Course* course){
            coursesTaken.push_back(course);
        }
    
        void Student::removeCourse(Course* course){
            for (size_t i = 0; i < coursesTaken.size(); ++i){
                if (course == coursesTaken[i]){
                    for (size_t j = i; j < coursesTaken.size(); ++j){
                        coursesTaken[j] = coursesTaken[j+1];
                    }
                    coursesTaken.pop_back();
                }
            }
        }
    
        string Student::getName() const{
            return name;
        }
    
        ostream& operator<<(ostream& os, const Student& student){
            os << student.name << endl;
            return os;
        }
}
