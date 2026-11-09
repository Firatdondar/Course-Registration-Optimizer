# Course Registration Optimizer

An intelligent university course registration system built with C++ that maximizes academic value within credit limits and simulates daily campus logistics using advanced pathfinding.

## 📌 Project Overview
During the course registration period, students must select courses that offer the highest academic contribution without exceeding their maximum ECTS limit. Additionally, they need to physically navigate between different classrooms spread across a large campus. 

This project solves both problems by implementing:
1. **0/1 Knapsack Algorithm (Dynamic Programming):** Optimizes course selection by maximizing the "Importance Score" against the student's ECTS capacity limit.
2. **Dijkstra's Shortest Path Algorithm:** Calculates the optimal walking routes between campus buildings to verify if a student can attend their selected courses on time.

## ⚙️ Features
* **Smart Course Selection:** Calculates dynamic importance scores based on course type (Mandatory/Elective) and prerequisite weight.
* **Campus Routing:** Uses a distance matrix to represent the campus layout and finds the shortest walking paths.
* **Time Simulation:** Simulates a student's day starting at 07:45, accounting for 50-minute lectures, 10-minute breaks, and varying walking speeds (80 meters/minute).
* **Comprehensive Reporting:** Generates detailed text reports (`report.txt` and `course_registration.txt`) showing enrolled courses, scores, arrival times, and missed classes due to distance.

## 🛠️ Technologies & Principles
* **Language:** C++ (Standard 17)
* **Build System:** CMake
* **Architecture:** Object-Oriented Programming (OOP)
* **Data Structures:** Custom Dynamic Arrays (Standard Template Library (STL) was strictly avoided by design requirements).

## 🚀 Installation & Build Instructions

This project uses CMake for building, making it cross-platform and compiler-independent.

### Prerequisites
* CMake (>= 3.10)
* A C++ compiler (GCC, Clang, or MSVC)

### Build Steps (Terminal)
1. Clone the repository:
   ```bash
   git clone https://github.com/Firatdondar/CourseRegistrationOptimizer.git
   cd CourseRegistrationOptimizer
   ```
2. Configure and build with CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
3. Run the executable:
   ```bash
   ./CourseRegistrationOptimizer
   ```
