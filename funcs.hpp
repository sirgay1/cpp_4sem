#ifndef FUNCS_HPP
#define FUNCS_HPP

#include "structs.hpp"

#include <iostream>
#include <sstream>
#include <random>


void parse_task(Quadratic_equations* equation, Coefficients* cefs);
double discriminant(Coefficients* cefs);
void find_roots(double D, Coefficients* cefs, Roots* roots);
Roots solving(Quadratic_equations* equation, Type type);


#endif