#include "input_n_output.hpp"

void input(Coefficients* cefs)
{
	cout << "Введите коэффициент a" << endl;
	cin >> cefs->a;
	cout << "Введите коэффициент b" << endl;
	cin >> cefs->b;
	cout << "Введите коэффициент c" << endl;
	cin >> cefs->c;

	return;
}

void output(Roots* roots, double D)
{
	cout << "Корни уравнения:" << endl;

	if (D > 0)
	{
		cout << roots->im1 << endl;
		cout << roots->im2 << endl;
	}
	else if (D == 0)
	{
		cout << roots->im1 << endl;
	}
	else
	{
		if (roots->re1 > 0)
		{
			cout << roots->im1 << "+" << roots->re1 << "i" << endl;
		}
		else
		{
			cout << roots->im1 << roots->re1 << "i" << endl;
		}
		
		if (roots->re2 > 0)
		{
			cout << roots->im2 << "+" << roots->re2 << "i" << endl;
		}
		else
		{
			cout << roots->im2 << roots->re2 << "i" << endl;
		}
	}

	return;
}