//
//  Course.hpp
//  Rec7
//
//  Created by David Slakter on 3/9/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#ifndef Course_hpp
#define Course_hpp

#include <stdio.h>
#include <string>
#include <vector>

namespace BrooklynPoly {

    class Student;

    class Course{
        public:
            Course(const std::string& cName);
        
            
            friend std::ostream& operator<<(std::ostream& os, const Course& course);
        
        
            void addStudent(Student* student);
        
            void removeCourseFromStudents();
        

            std::string getName() const;

        private:
            std::string courseName;
            std::vector<Student*> enrolledStudents;
        };
}

#endif /* Course_hpp */
