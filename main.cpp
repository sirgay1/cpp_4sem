#include "input_n_output.hpp"
#include "structs.hpp"
#include "find_roots.hpp"
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Russian");

	Coefficients coefficients;
	input(&coefficients);

	double D = discriminant(&coefficients);

	Roots roots;

	find_roots(D, &coefficients, &roots);

	output(&roots, D);

	return 0;
}