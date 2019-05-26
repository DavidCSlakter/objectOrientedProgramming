//
//  Registrar.hpp
//  Rec7
//
//  Created by David Slakter on 3/9/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#ifndef Registrar_hpp
#define Registrar_hpp

#include <stdio.h>
#include <string>
#include <vector>


namespace BrooklynPoly {
    class Course;
    class Student;
    
    class Registrar{
        public:
        
        size_t findCourse(const std::string& courseName);
        size_t findStudent(const std::string& stuName);

        void enrollStudentInCourse(const std::string& stuName, const std::string& courseName);
        
        void cancelCourse(const std::string& courseName);
        void addCourse(const std::string& courseName);
        void addStudent(const std::string& stuName);
        void purge();
        
        friend std::ostream& operator<<(std::ostream& os, const Registrar& reg);
        
        private:
            std::vector<Course*> courses;
            std::vector<Student*> students;
        };

}

#endif /* Registrar_hpp */
