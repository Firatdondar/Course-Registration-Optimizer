#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include "Course.hpp"
#include "CustomVector.hpp"

class Student {
public:
    int id;
    std::string name;
    int maxECTS;
    CustomVector<Course> enrolledCourses;

    Student() : id(0), maxECTS(0) {}
    
    void enrollCourse(const Course& course) {
        enrolledCourses.push_back(course);
    }
};

#endif