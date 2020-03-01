#include "ublas/matrix.hpp"
#include "ublas/io.hpp"
#include "ublas/vector.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace boost::numeric::ublas;

ofstream out_accuracy("accuracy_task3.txt");

#define alpha 			0.01
#define beta 			10
#define tau				1
#define matrix_size 	1000
#define accuracy		0.0001


vector<double> FindSolution(matrix<double> A, vector<double> b)
{
	const double EPS = accuracy;
	//Прибижённое решение
	vector<double> x = zero_vector<double>(A.size1());
	//Невязка
	vector<double> r = b - prec_prod(A , x);
	//Базисный вектор
	vector<double> p = r;
	double rSquare = inner_prod(r, r);
	int numIter = 0;
	out_accuracy << rSquare << endl;
	while (rSquare > EPS)
	{
		numIter++;
		vector<double> temp = prec_prod(A, p);
		double alpha = rSquare / inner_prod(temp, p);
		x = x + alpha * p;

		vector<double> rNew = r - alpha * temp;
		double rNewSquare = inner_prod(rNew, rNew);
		double beta = rNewSquare / rSquare;
		r = rNew;
		rSquare = rNewSquare;
		p = r + beta * p;
	}

	std::cout <<"Число итераций: " << numIter << std::endl;
	return x;
}

int main()
{
	ofstream out("result_task3.txt");
	matrix<double> A(matrix_size, matrix_size);
	vector<double> b(matrix_size, 0);

	for(int f_count = 495; f_count <= 505; f_count++)
    {
    	b[f_count] = tau;
    }
    for(int i = 0; i < matrix_size; i++)
    	for(int j = 0; j < matrix_size; j++)
    		A(i, j) = 0;
    A(0, 0) = 2 + beta;
    A(0, 1) = -1;
    A(999, 998) = -1;
    A(999, 999) = 2 + alpha;
    for(int i = 1; i < matrix_size - 1; i++)
    {
    	A(i, i - 1) = -1;
    	A(i, i) = 2 + alpha;
    	A(i, i + 1) = -1;
    }	
	
	vector<double> x = FindSolution(A, b);

	std::cout.precision(9);
	for(int elem = 0; elem < matrix_size; elem++)
    {
    	out << x[elem] << endl;
    }
    out.close();
    out_accuracy.close();


	return 0;
}