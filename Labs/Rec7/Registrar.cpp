//
//  Registrar.cpp
//  Rec7
//
//  Created by David Slakter on 3/9/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include "Registrar.hpp"
#include "Student.hpp"
#include "Course.hpp"
#include <iostream>

using namespace std;

namespace BrooklynPoly {
    
    size_t Registrar::findCourse(const string& courseName){
        for(size_t i = 0; i < courses.size(); ++i){
            if(courseName == courses[i]->getName()){
                return i;
            }
        }
        return courses.size();
    }
    
    size_t Registrar::findStudent(const string& stuName){
        for(size_t i = 0; i < students.size(); ++i){
            if(stuName == students[i]->getName()){
                return i;
            }
        }
        return students.size();
    }

    void Registrar::enrollStudentInCourse(const string& stuName, const string& courseName){
        size_t cInd = findCourse(courseName);
        size_t sInd = findStudent(stuName);
        
        if (sInd == students.size() || cInd == courses.size()){
            cout << "could not find student or course to complete enrollment" << endl;
        }
        else{
            courses[cInd]->addStudent(students[sInd]);
            students[sInd]->addCourse(courses[cInd]);
        }
    }
    
    void Registrar::cancelCourse(const string& courseName){
        size_t ind = findCourse(courseName);
        if(ind != courses.size()){
            //
            courses[ind]->removeCourseFromStudents();
        
        
            //remove course from heap
            delete courses[ind];
            
            //remove course from vectors
            for (size_t j = ind; j < courses.size(); ++j){
                courses[j] = courses[j+1];
            }
            courses.pop_back();
    
           
        }
        else{
            cout << "Unable to cancel course: course not found" << endl;
        }
    }
    void Registrar::addCourse(const string& courseName){
        if (findCourse(courseName) != courses.size()){
            cout << "unable to add course: course already exists" << endl;
        }
        else{
            Course* course = new Course(courseName);
            courses.push_back(course);
        }
       
    }
    void Registrar::addStudent(const string& stuName){
        if (findStudent(stuName) != students.size()){
            cout << "unable to add student: student already exists" << endl;
        }
        else{
            Student* student = new Student(stuName);
            students.push_back(student);
        }
    }
    void Registrar::purge(){
        for (size_t i = 0; i < courses.size(); ++i){
            delete courses[i];
        }
        for (size_t j = 0; j < students.size(); ++j){
            delete students[j];
        }
    }
    
  ostream& operator<<(ostream& os, const Registrar& reg){
        //print the courses and the students in each course
        for (size_t i = 0; i < reg.courses.size(); ++i){
            os << "Courses: " << endl << *(reg.courses[i]);
        }
        return os;
    }

}
