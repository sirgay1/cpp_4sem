#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>


enum Type { good, mid, bad };

struct Coefficients {
    double a;
    double b;
    double c;
};

struct Roots {
    double im1 = 0.0;
    double re1 = 0.0;
    double im2 = 0.0;
    double re2 = 0.0;
};

struct Quadratic_equations {
	std::string task;
};

struct Student {
	std::string name;
	Type type;
};

struct Letter {
	Student student;
	Quadratic_equations task;
    Roots roots;
};

struct Answer {
    Quadratic_equations task;
    Roots roots;
};

struct Progress_table {
    Student student;
    int count_right_task = 0;
};
#endif