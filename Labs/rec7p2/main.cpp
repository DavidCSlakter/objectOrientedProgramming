//
//  main.cpp
//  Rec7
//
//  Created by David Slakter on 3/9/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

//#include "Registrar.h"
#include <iostream>
#include <vector>

using namespace std;

namespace BrooklynPoly {
       class Course;
  
       class Student{
        public:
    
        Student(const string& aName): name(aName){}
        
        friend ostream& operator<<(ostream& os, const Student& student){
            os << student.name << endl;
            return os;
        }
        
        void addCourse(Course* course){
            coursesTaken.push_back(course);
        }
        void removeCourse(Course* course){
            for (size_t i = 0; i < coursesTaken.size(); ++i){
                if (course == coursesTaken[i]){
                    for (size_t j = i; j < coursesTaken.size(); ++j){
                        coursesTaken[j] = coursesTaken[j+1];
                    }
                    coursesTaken.pop_back();
                }
            }
        }
        string getName() const{
            return name;
        }

    private:
        string name;
        vector<Course*> coursesTaken;
        
    };


    class Course{
    public:
        Course(const string& cName): courseName(cName){
        
        }
        
        friend ostream& operator<<(ostream& os, const Course& course){
            os << course.courseName << endl << "Students: " << endl;
            if (course.enrolledStudents.size() == 0){
                cout << "None" << endl;
            }
            else{
                for (size_t i = 0; i < course.enrolledStudents.size(); ++i){
                    os << *(course.enrolledStudents[i]);
                }
            }
            return os;
        }
        
        void addStudent(Student* student){
            enrolledStudents.push_back(student);
        }
        
        void removeCourseFromStudents(){
            for (size_t i = 0; i < enrolledStudents.size(); ++i){
                enrolledStudents[i]->removeCourse(this);
            }
        }

        string getName() const{
            return courseName;
        }

    private:
        string courseName;
        vector<Student*> enrolledStudents;
    };

 
    class Registrar{
    public:
    
    size_t findCourse(const string& courseName){
        for(size_t i = 0; i < courses.size(); ++i){
            if(courseName == courses[i]->getName()){
                return i;
            }
        }
        return courses.size();
    }
    size_t findStudent(const string& stuName){
        for(size_t i = 0; i < students.size(); ++i){
            if(stuName == students[i]->getName()){
                return i;
            }
        }
        return students.size();
    }

    void enrollStudentInCourse(const string& stuName, const string& courseName){
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
    
    void cancelCourse(const string& courseName){
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
    void addCourse(const string& courseName){
        if (findCourse(courseName) != courses.size()){
            cout << "unable to add course: course already exists" << endl;
        }
        else{
            Course* course = new Course(courseName);
            courses.push_back(course);
        }
       
    }
    void addStudent(const string& stuName){
        if (findStudent(stuName) != students.size()){
            cout << "unable to add student: student already exists" << endl;
        }
        else{
            Student* student = new Student(stuName);
            students.push_back(student);
        }
    }
    void purge(){
        for (size_t i = 0; i < courses.size(); ++i){
            delete courses[i];
        }
        for (size_t j = 0; j < students.size(); ++j){
            delete students[j];
        }
    }
    
    friend ostream& operator<<(ostream& os, const Registrar& reg){
        //print the courses and the students in each course
        for (size_t i = 0; i < reg.courses.size(); ++i){
            os << "Courses: " << endl << *(reg.courses[i]);
        }
        return os;
    }
        
    private:
        vector<Course*> courses;
        vector<Student*> students;
    };

}

using namespace BrooklynPoly;

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;  // or registrar.printReport()
    
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout <<  "Should fail, i.e. do nothing, since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;  // or registrar.printReport()
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  // or registrar.printReport()
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;  // or registrar.printReport()
}

