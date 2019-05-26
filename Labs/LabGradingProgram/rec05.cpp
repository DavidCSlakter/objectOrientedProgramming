//
//  main.cpp
//  LabGradingProgram
//
//  Created by David Slakter on 2/23/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class LabSection{
public:
    
    LabSection(const string& secName, const string& secDay, unsigned int secTime):
    sectionName(secName), timeSlot(secDay, secTime) {}
    
    LabSection(const LabSection& section): sectionName(section.sectionName), timeSlot(section.timeSlot) {
        for (const Student* student: section.students){
            Student* newStudent;
            newStudent = new Student(student->getName());
            students.push_back(newStudent);
        }
    }
    
    ~LabSection(){
        cout << "Section " << sectionName << " is being deleted" << endl;
        for (const Student* student: students){
            cout << "Deleting " << student->getName() << endl;
            delete student;
        }
    }
    
    void display() const{
       cout << *this;
    }
    
    void addStudent(const string& studentName){
        Student* student;
        student = new Student(studentName);
        students.push_back(student);
    }
    
    void changeGrade(const string& studentName, int grade, int week){
    
        //find the student
        for(size_t i = 0; i < students.size(); ++i){
            if (students[i]->getName() == studentName){
                students[i]->changeGrade(grade, week);
            }
        }
    }
    
    friend ostream& operator<<(ostream& os, const LabSection& section){
            os << "Section: " << section.sectionName << ", Time slot: "
            << section.timeSlot << ", students: " << endl;
        
            if (section.students.size() == 0){
                os << "None";
            }
            else{
        
                for(const Student* student: section.students){
                    os << *student << endl;
                }
            }
            return os;
    }
    
private:

    class Student{
    
    public:
    
        Student(const string& Sname): name(Sname) {
            for(size_t i = 1; i < 14; ++i){
                grades.push_back(-1);
            }
        }
        
        string getName() const{
            return name;
        }
        
        void changeGrade(int grade, int week){
            for(size_t i = 1; i < grades.size(); ++i){
                if (i == week){
                    grades[i - 1] = grade;
                }
            }
        }
        
       friend ostream& operator<<(ostream& os, const Student& student){
           os << student.getName() << ", Grades: ";
           for (int grade: student.grades){
            os << grade << " ";
           }
         return os;
        }
        
    private:
        string name;
        vector<int> grades;
    };
    
    
    class TimeSlot{
    public:
        TimeSlot(const string& secDay, unsigned int secTime): sectionDay(secDay) {
            if (secTime < 12){
                sectionTimePeriod = "am";
                sectionTime = secTime;
            }
            else{
                sectionTimePeriod = "pm";
                sectionTime = secTime - 12;
            }
        }
        
        
      friend ostream& operator<<(ostream& os, const TimeSlot& ts){
         os << '[' << "Day: " << ts.sectionDay <<
            ", Start time: " << ts.sectionTime << ts.sectionTimePeriod << ']';
         return os;
      }
    
    private:
    
        string sectionDay;
        unsigned int sectionTime;
        string sectionTimePeriod;
    };

    //Section member variables
    TimeSlot timeSlot;
    string sectionName;
    vector<Student*> students;
};

class LabWorker{
public:
    LabWorker(const string& Lname): name(Lname), section(nullptr) {}
    
    void display() const {
        if (section == nullptr){
            cout << name << " does not have a section";
        }
        else{
            cout << *section;
        }
    }
    
    void addSection(LabSection& aSection) {
        section = &aSection;
    }
    
    void addGrade(const string& studentName, int grade, int week){
        section->changeGrade(studentName, grade, week);
    }
    
private:
    LabSection* section;
    string name;
};

// Test code
void doNothing(LabSection sec) { sec.display(); }

int main() {

    cout << "Test 1: Defining a section\n";
    LabSection secA2("A2", "Tuesday", 16);
    secA2.display();

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    secA2.display();

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    moe.display();

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    moe.display();

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    LabSection secB3( "B3", "Thursday", 11);
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    jane.display();

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    moe.display();

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    moe.display();

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, then make sure the following call works\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
