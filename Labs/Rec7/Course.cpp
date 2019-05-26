//
//  Course.cpp
//  Rec7
//
//  Created by David Slakter on 3/9/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include "Course.hpp"
#include "Student.hpp"
#include <iostream>

using namespace std;

namespace BrooklynPoly {

        Course::Course(const string& cName): courseName(cName){
        
        }
    
        void Course::addStudent(Student* student){
            enrolledStudents.push_back(student);
        }
    
        void Course::removeCourseFromStudents(){
            for (size_t i = 0; i < enrolledStudents.size(); ++i){
                enrolledStudents[i]->removeCourse(this);
            }
        }

        string Course::getName() const{
            return courseName;
        }
    
        ostream& operator<<(ostream& os, const Course& course){
            os << course.courseName << endl << "Students: " << endl;
            if (course.enrolledStudents.size() == 0){
                os << "None" << endl;
            }
            else{
                for (size_t i = 0; i < course.enrolledStudents.size(); ++i){
                    os << *(course.enrolledStudents[i]);
                }
            }
            return os;
        }

}


