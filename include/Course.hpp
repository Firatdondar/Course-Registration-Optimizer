#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>

class Course {
public:
    int id;
    std::string name;
    std::string type; // "Z" for Mandatory, "S" for Elective
    int ects;
    int prerequisiteCourseId; 
    int classroomId;
    int prerequisiteCount; 
    int importanceScore;

    Course() : id(0), ects(0), prerequisiteCourseId(0), classroomId(0), prerequisiteCount(0), importanceScore(0) {}

    /**
     * @brief Calculates the importance score based on ECTS, course type, and prerequisites.
     */
    void calculateImportanceScore() {
        importanceScore = ects;
        importanceScore += (type == "Z" || type == "Zorunlu") ? 20 : 10;
        importanceScore += (prerequisiteCount * 5);
    }
};

#endif