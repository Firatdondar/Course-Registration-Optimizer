# 🎓 Course Registration Optimizer

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.10%2B-064F8C?logo=cmake&logoColor=white)
![Algorithms](https://img.shields.io/badge/Algorithms-Knapsack%20DP%20%26%20Dijkstra-purple)
![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)

An algorithmic university course selection and campus logistics simulator built in **C++17**. It maximizes academic credit utility using **0/1 Knapsack Dynamic Programming** and verifies inter-building transition feasibility between consecutive lectures using **Dijkstra's Shortest Path Algorithm**.

---

## 📌 Problem Overview

During university course registration, students face two coupled optimization challenges:
1. **Academic Value Maximization:** Selecting a subset of courses that maximizes total academic importance without exceeding the student's maximum ECTS credit limit.
2. **Campus Transit Feasibility:** Navigating between lecture halls across campus within the 10-minute break between 50-minute class sessions (walking at $80\text{ m/min}$ starting from `07:45`).

---

## ✨ Key Features

- **0/1 Knapsack Course Optimizer:** Computes dynamic course importance weights based on mandatory/elective status and prerequisite chains, solving the credit-constrained optimization problem in $O(N \cdot W)$ time.
- **Dijkstra Shortest Path Router:** Models campus buildings as a weighted graph (`data/classrooms.txt`) and computes shortest walking paths and travel durations between consecutive lectures.
- **Custom STL-Free Data Structures:** Built from scratch using a custom templated dynamic array (`CustomVector<T>`) with manual memory management and zero STL container dependencies.
- **Automated Schedule & Attendance Audit:** Outputs `course_registration.txt` and `report.txt` detailing enrolled courses, total ECTS, walking distances, arrival timestamps, and tardiness warnings.

---

## 🗂️ Project Structure

```text
Course-Registration-Optimizer/
├── data/
│   ├── classrooms.txt       # Campus building distance matrix
│   ├── courses.txt          # Course catalog, ECTS credits, and prerequisites
│   └── students.txt         # Student profiles and ECTS capacity limits
├── include/
│   ├── Course.hpp           # Course entity & importance score model
│   ├── CustomVector.hpp     # Custom dynamic array template (STL-free)
│   ├── Graph.hpp            # Campus graph & Dijkstra shortest path solver
│   └── Student.hpp          # Student schedule & 0/1 Knapsack DP solver
├── src/
│   └── main.cpp             # Simulation entry point & report generator
├── CMakeLists.txt           # Cross-platform CMake build configuration
├── LICENSE                  # MIT License
└── README.md                # Project documentation
```

---

## 🚀 Build & Run Instructions

### Prerequisites
- **CMake** ($\ge 3.10$)
- **C++17 Compiler** (GCC, Clang, or MSVC)

### Build with CMake
```bash
git clone https://github.com/Firatdondar/Course-Registration-Optimizer.git
cd Course-Registration-Optimizer
mkdir build && cd build
cmake ..
cmake --build .
```

### Run the Optimizer
```bash
./CourseRegistrationOptimizer
```

---

## 📄 License

Distributed under the **MIT License**. See [`LICENSE`](LICENSE) for details.
