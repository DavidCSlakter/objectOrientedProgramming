//
//  Student.hpp
//  Rec7
//
//  Created by David Slakter on 3/9/18.
//  Copyright © 2018 David Slakter. All rights reserved.
//

#ifndef Student_hpp
#define Student_hpp

#include <stdio.h>
#include <string>
#include <vector>

namespace BrooklynPoly {

class Course;


 class Student{
        friend std::ostream& operator<<(std::ostream& os, const Student& student);
        public:
     
        Student(const std::string& aName);
     
        void addCourse(Course* course);
        void removeCourse(Course* course);
        std::string getName() const;

    private:
        std::string name;
        std::vector<Course*> coursesTaken;
     
    };
}   

#endif /* Student_hpp */
