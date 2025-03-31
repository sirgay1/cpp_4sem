#include "funcs.hpp"


void parse_task(Quadratic_equations* equation, Coefficients* cefs) {
	if (equation->task.find("x^2") == std::string::npos) {
		cefs->a = 0;
		if (equation->task.find("x") == std::string::npos) {
			cefs->b = 0;
			cefs->c = std::stod(equation->task.substr(0, equation->task.find("=") - 1));
		}
		else {
			cefs->b = std::stod(equation->task.substr(0, equation->task.find("x")));
			if (equation->task.find("x") - equation->task.find("=") == 2) {
				cefs->c = 0;
			}
			else {
				cefs->c = std::stod(equation->task.substr(equation->task.find("x") + 1, equation->task.find("=") - equation->task.find("x") - 2));
			}
		}
	}
	else {
		cefs->a = std::stod(equation->task.substr(0, equation->task.find("x^2")));
		if (equation->task.find_first_of("x") == equation->task.find_last_of("x")) {
			cefs->b = 0;
			if (equation->task.find("=") - equation->task.find("x") == 4) {
				cefs->c = 0;
			}
			else {
				cefs->c = std::stod(equation->task.substr(equation->task.find("x^2") + 3, equation->task.find("=") - equation->task.find("x^2") - 4));
			}
		}
		else {
			cefs->b = std::stod(equation->task.substr(equation->task.find("x^2") + 3, equation->task.find_last_of("x") - equation->task.find("x^2") - 3));
			if (equation->task.find("=") - equation->task.find_last_of("x") == 2) {
				cefs->c = 0;
			}
			else {
				cefs->c = std::stod(equation->task.substr(equation->task.find_last_of("x") + 1, equation->task.find("=") - equation->task.find_last_of("x") - 2));
			}
		}
	}
	return;
}

double discriminant(Coefficients* cefs) {
	double D = pow(cefs->b, 2) - 4 * cefs->a * cefs->c;

	return D;
}

void find_roots(double D, Coefficients* cefs, Roots* roots) {
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

Roots solving(Quadratic_equations* equation, Type type) {
	Coefficients coefficients;
	parse_task(equation, &coefficients);
	if (type == good) {
		Roots roots;
		double D = discriminant(&coefficients);
		find_roots(D, &coefficients, &roots);
		return roots;
	}
	else if (type == bad) {
		Roots roots;
		roots.im1 = roots.im2 = roots.re1 = roots.re2 = 0.0;
		return roots;
	}
	else {
		std::mt19937 rng(std::random_device{}());
		std::uniform_real_distribution<double> dis(40.0, 60.0);
		double odds_mid_student = dis(rng);
		//double odds_mid_student = 40;
		double probability = odds_mid_student / 100;

		std::uniform_real_distribution<double> dist(0.0, 1.0);

		if (dist(rng) <= probability) {
			Roots roots;
			double D = discriminant(&coefficients);
			find_roots(D, &coefficients, &roots);
			return roots;
		}
		else {
			Roots roots;
			double D = discriminant(&coefficients) + 4;
			find_roots(D, &coefficients, &roots);
			return roots;
		}
	}
}
