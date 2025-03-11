#ifndef FIND_ROOTS_H
#define FIND_ROOTS_H

#include "structs.hpp"
#include <math.h>

double discriminant(Coefficients* cefs);
void find_roots(double D, Coefficients* cefs, Roots* roots);

#endif