#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;
ofstream out_accuracy("accuracy_task2.txt");

#define alpha 			0.01
#define beta 			10
#define tau				1
#define matrix_size 	1000
#define accuracy		0.0001

double norm(vector<double> & r)
{
	double res = 0;
	for(int i = 0; i < matrix_size; i++)
	{
		res += r[i] * r[i];
	}
	res = sqrt(res);
	return res;
}

void Matvec(	vector<double> & y,
				vector<double> & x) //y = tau*Ax
{
	y[0] = tau * (x[0] - (x[1] / (2 + beta)));
	y[999] = tau * ((- x[998] / (2 + alpha)) + x[999]);
	for(int i = 1; i < matrix_size - 1; i++)
		y[i] = tau * ((- x[i - 1] / (2 + alpha)) + x[i] - x[i + 1] / (2 + alpha));
}

int SI_Solver(	vector<double> & result, 
				vector<double> & tau_f,
				vector<double> & x0)
{
	int iteracy_counter = 0;
	vector<double> x(matrix_size, 0);
	vector<double> y(matrix_size, 0);
	vector<double> r(matrix_size, 0);
	vector<double> r0(matrix_size, 0);
	Matvec(y, x0);
	for(int elem = 0; elem < matrix_size; elem++)
	{
		r0[elem] = tau_f[elem] - y[elem];
		r[elem] = r0[elem];
		x[elem] = tau_f[elem] - y[elem] + x0[elem];
	}
	while((norm(r) / norm(r0)) > accuracy)
	{
		iteracy_counter++;
		Matvec(y, x);
		for(int elem = 0; elem < matrix_size; elem++)
		{
			r[elem] = tau_f[elem] - y[elem];
			x[elem] = tau_f[elem] - y[elem] + x[elem];
		}
		out_accuracy << norm(r) / norm(r0) << endl;

	}
	for(int elem = 0; elem < matrix_size; elem++)
	{
		result[elem] = x[elem];
	}

	return iteracy_counter;

}

int main()
{
	ofstream out("result_task2.txt");
	vector<double> result(matrix_size, 0);
    vector<double> tau_f(matrix_size, 0);
    vector<double> x0(matrix_size, 0);

    for(int f_count = 495; f_count <= 505; f_count++)
    {
    	tau_f[f_count] = 1 / (2 + alpha);
    }

    int iteracy_counter = SI_Solver(result, tau_f, x0);
    cout << "iteracy_counter = " << iteracy_counter << endl;
    for(int elem = 0; elem <= matrix_size; elem++)
    {
    	out << result[elem] << endl;
    }
    out.close();
    out_accuracy.close();
	return 0;
}