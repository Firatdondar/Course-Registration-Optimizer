cmake_minimum_required(VERSION 3.10)
project(CourseRegistrationOptimizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Başlık dosyalarının yolunu göster
include_directories(include)

# Kaynak kodları derle
add_executable(CourseRegistrationOptimizer src/main.cpp)