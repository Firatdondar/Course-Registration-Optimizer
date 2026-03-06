#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

#include "../include/CustomVector.hpp"
#include "../include/Course.hpp"
#include "../include/Student.hpp"
#include "../include/Graph.hpp"

CustomVector<Course> globalCourses;
CustomVector<Student> globalStudents;
CampusGraph campusMap;

void splitString(const std::string &s, char delimiter, CustomVector<std::string> &tokens) {
    tokens.clear();
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
}

void loadCourses() {
    std::ifstream file("data/courses.txt");
    if (!file.is_open()) { 
        std::cerr << "ERROR: Cannot open data/courses.txt" << std::endl; 
        return; 
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        CustomVector<std::string> cols;
        splitString(line, '\t', cols);

        if (cols.size() >= 6) {
            Course c;
            c.id = parseInt(cols[0]);
            c.name = cols[1];
            c.type = cols[2];
            c.ects = parseInt(cols[3]);
            c.prerequisiteCourseId = (cols[4].empty() || cols[4] == " ") ? 0 : parseInt(cols[4]);
            c.classroomId = parseInt(cols[5]);
            globalCourses.push_back(c);
        }
    }
    file.close();

    // Calculate dependencies and importance scores
    for (int i = 0; i < globalCourses.size(); i++) {
        int count = 0;
        for (int j = 0; j < globalCourses.size(); j++) {
            if (globalCourses[j].prerequisiteCourseId == globalCourses[i].id) {
                count++;
            }
        }
        globalCourses[i].prerequisiteCount = count;
        globalCourses[i].calculateImportanceScore();
    }
}

void loadClassrooms() {
    std::ifstream file("data/classrooms.txt");
    if (!file.is_open()) { 
        std::cerr << "ERROR: Cannot open data/classrooms.txt" << std::endl; 
        return; 
    }
    
    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        CustomVector<std::string> cols;
        splitString(line, '\t', cols);
        
        if (cols.size() > 0) {
            int currentNode = parseInt(cols[0]);
            for (int i = 1; i < cols.size(); i++) {
                int targetNode = 100 + (i - 1);
                if (cols[i] != "*") {
                    int dist = parseInt(cols[i]);
                    campusMap.addEdge(currentNode, targetNode, dist);
                }
            }
        }
    }
    file.close();
}

void loadStudents() {
    std::ifstream file("data/students.txt");
    if (!file.is_open()) { 
        std::cerr << "ERROR: Cannot open data/students.txt" << std::endl; 
        return; 
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        if(line.empty()) continue;
        CustomVector<std::string> cols;
        splitString(line, '\t', cols);
        
        if (cols.size() >= 3) {
            Student s;
            s.id = parseInt(cols[0]);
            s.name = cols[1];
            s.maxECTS = parseInt(cols[2]);
            globalStudents.push_back(s);
        }
    }
    file.close();
}

/**
 * @brief Optimizes course selection using 0/1 Knapsack DP Algorithm.
 */
void optimizeCourseSelection(Student &student) {
    int n = globalCourses.size();
    int W = student.maxECTS;
    
    int** dp = new int*[n + 1];
    for(int i = 0; i <= n; ++i) dp[i] = new int[W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (globalCourses[i - 1].ects <= w) {
                int valInclude = globalCourses[i - 1].importanceScore + dp[i - 1][w - globalCourses[i - 1].ects];
                int valExclude = dp[i - 1][w];
                dp[i][w] = (valInclude > valExclude) ? valInclude : valExclude;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int res = dp[n][W];
    int w = W;
    for (int i = n; i > 0 && res > 0; i--) {
        if (res == dp[i - 1][w]) continue;
        else {
            student.enrollCourse(globalCourses[i - 1]);
            res -= globalCourses[i - 1].importanceScore;
            w -= globalCourses[i - 1].ects;
        }
    }

    for(int i = 0; i <= n; ++i) delete[] dp[i];
    delete[] dp;
}

void runSimulationAndReport() {
    std::ofstream out("report.txt");
    std::ofstream courseLog("course_registration.txt");

    out << "Simulation Report\n----------------\n";

    for (int i = 0; i < globalStudents.size(); i++) {
        Student &student = globalStudents[i];
        optimizeCourseSelection(student);

        courseLog << student.id << " " << student.name << " Enrolled Courses:\n";
        for(int k = 0; k < student.enrolledCourses.size(); k++) {
            courseLog << " - " << student.enrolledCourses[k].name 
                      << " (Score: " << student.enrolledCourses[k].importanceScore << ")\n";
        }
        courseLog << "--------------------------------\n";

        int currentLocation = 100; 
        int currentMinute = 465; // 07:45 in minutes

        out << "Student: " << student.name << "\n";
        
        CustomVector<Course> remainingCourses = student.enrolledCourses; 
        
        while(remainingCourses.size() > 0) {
            int shortestDist = 999999;
            int closestIndex = -1;

            for(int j = 0; j < remainingCourses.size(); j++) {
                int dist = campusMap.getShortestPath(currentLocation, remainingCourses[j].classroomId);
                if(dist < shortestDist) {
                    shortestDist = dist;
                    closestIndex = j;
                }
            }

            if(closestIndex != -1) {
                Course target = remainingCourses[closestIndex];
                
                int walkingTime = (shortestDist + 79) / 80;
                currentMinute += walkingTime;
                
                int nextHour = (currentMinute + 59) / 60 * 60; 
                if (nextHour < currentMinute) nextHour += 60; 
                
                if (nextHour >= 18 * 60) {
                     out << " - Failed to attend: " << target.name << " (Out of time)\n";
                } else {
                    int arrHour = currentMinute / 60;
                    int arrMin = currentMinute % 60;
                    int startHour = nextHour / 60;

                    out << " - Attended: " << target.name << " | Classroom: " << target.classroomId 
                        << " | Arrival: " << arrHour << ":" << (arrMin < 10 ? "0" : "") << arrMin
                        << " | Starts at: " << startHour << ":00\n";
                    
                    currentMinute = nextHour + 50; 
                    currentLocation = target.classroomId;
                }
                
                CustomVector<Course> newList;
                for(int x = 0; x < remainingCourses.size(); x++) {
                    if(x != closestIndex) newList.push_back(remainingCourses[x]);
                }
                remainingCourses = newList;

            } else {
                break;
            }
        }
        out << "--------------------------------\n";
    }
    out.close();
    courseLog.close();
}

int main() {
    std::cout << "Initializing System..." << std::endl;
    loadCourses();
    loadClassrooms();
    loadStudents();
    
    std::cout << "Running Optimization and Simulation..." << std::endl;
    runSimulationAndReport();
    
    std::cout << "Execution complete. Check 'report.txt' and 'course_registration.txt'." << std::endl;
    return 0;
}