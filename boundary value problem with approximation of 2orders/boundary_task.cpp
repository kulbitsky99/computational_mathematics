/*Task: -(g(x)y'(x))' + p(x)y(x) = f(x),
		y'(0) = A, y'(1) = B;
		N - number of intervals of [0; 1]; h = 1 / N;
		Approximate solution is found from (_A * y = r),
		where _A is a 3-diagonal matrix(diagonals a(n), b(n + 1), c(n)).
		Check the results for y(x) = (2 / pi) * sin(pi * x / 2).*/
#include <iostream>
#include <fstream>
#include <vector> 
#include <cmath>

std::ofstream a_out("a_diag.txt");
std::ofstream b_out("b_diag.txt");
std::ofstream c_out("c_diag.txt");
std::ofstream r_out("r.txt");

enum Const
{
	A = 1,
	N = 20
};

#define B (2 * exp(1.0))

//oh yes, you should set g_derivative by hands
double g(double x)
{
	return 1;
}
double g_derivative(double x)
{
	return 0;
}

double p(double x)
{
	return 1;
}

double f(double x)
{
	return ((-2) * exp(x));
}



int main()
{
	double h = 1 / double(N);
	std::cout << "h(step) = " << h << std::endl;
	std::vector <double> a(N);
	std::vector <double> b(N + 1);
	std::vector <double> c(N);
	std::vector <double> r(N + 1);

	//Setting (n - 1) equations
	for(int k = 1; k <= N - 1; k++)
	{
		a[k - 1] = - g((double(k) - 0.5) * h) / (h * h);
		b[k] = 	g((double(k) - 0.5) * h) / (h * h) + 
				g((double(k) + 0.5) * h) / (h * h) +
				p(double(k) * h);
		c[k] = - g((double(k) + 0.5) * h) / (h * h);
		r[k] = f(double(k) * h);
	}
	r[0] = f(0) + g_derivative(0) * A - 2 * g(0) * A / h;
	r[N] = f(1) + g_derivative(1) * B + 2 * g(1) * B / h;
	//for y0 = y(0)
	b[0] = 2 * g(0) / (h * h) + p(0);
	c[0] = - 2 * g(0) / (h * h);
	//for yn = y(1)
	a[N - 1] = - 2 * g(1) / (h * h);
	b[N] = 2 * g(1) / (h * h) + p(1);

	//writing _A and r to files, then progonka method will use it
	for(int i = 0; i < N; i++)
	{
		a_out << a[i] << "\n";
		b_out << b[i] << "\n";
		c_out << c[i] << "\n";
		r_out << r[i] << "\n ";
	}
	b_out << b[N] << "\n";
	r_out << r[N] << "\n";

	a_out.close();
	b_out.close();
	c_out.close();
	r_out.close();
	return 0;
}





