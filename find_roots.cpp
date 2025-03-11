#include "find_roots.hpp"


double discriminant(Coefficients* cefs)
{
	double D = pow(cefs->b, 2) - 4 * cefs->a * cefs->c;

	return D;
}

void find_roots(double D, Coefficients* cefs, Roots* roots)
{
	if (D > 0)
	{
		roots->im1 = ((-1) * cefs->b + sqrt(D)) / (2 * cefs->a);
		roots->im2 = ((-1) * cefs->b - sqrt(D)) / (2 * cefs->a);
	}
	else if (D == 0)
	{
		roots->im1 = ((-1) * cefs->b) / (2 * cefs->a);
	}
	else
	{
		roots->im1 = ((-1) * cefs->b) / 2 * cefs->a;
		roots->re1 = sqrt(D * (-1)) / 2 * cefs->a;

		roots->im2 = ((-1) * cefs->b) / 2 * cefs->a;
		roots->re2 = (-1) * (sqrt(D * (-1)) / 2 * cefs->a);
	}

	return;
}