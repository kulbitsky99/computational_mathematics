#include <iostream>
#include <fstream>
#include <cmath>

std::ofstream fout("output.txt");

enum INIT_VALUES{
	U0 = 0,
	V0 = 1,
	G = 10,
	LAMBDA = 1,
	L = 1,
	N = 20,
	PERIOD_NUMBER = 3
};

// counting second derivative
double second_derivative(double tau, double coord, double velocity)
{
	double der = (-G * sin(coord) - 2 * LAMBDA * velocity) / (L);
	// std::cout << "second_der = " << der << "\t";
	return der;
}


// 
void EulerSolution(double tau, double * coord1, double * velocity1){
	coord1[0]    = U0;
	velocity1[0] = V0;
	for(int i(0); i < PERIOD_NUMBER * N; ++i)
	{
		velocity1[i + 1] = velocity1[i] + tau * second_derivative(tau, coord1[i], velocity1[i]);
		coord1[i + 1] = coord1[i] + tau * velocity1[i];
	}
}

void RungeKutta(double tau, double * coord2, double * velocity2){
	coord2[0]    = U0;
	velocity2[0] = V0;
	for(int i(0); i < PERIOD_NUMBER * N; ++i)
	{
		double k1 = tau * second_derivative(tau, coord2[i], velocity2[i]);
		double k2 = tau * second_derivative(tau, coord2[i] + tau / 2.0, velocity2[i] + k1 / 2.0);
		double k3 = tau * second_derivative(tau, coord2[i] + tau / 2.0, velocity2[i] + k2 / 2.0);
		double k4 = tau * second_derivative(tau, coord2[i] + tau, velocity2[i] + k3);
		velocity2[i + 1] = velocity2[i] + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
		coord2[i + 1] = coord2[i] + tau * velocity2[i];
	}
	
}

void Print_data(double tau, double * coord1, double * coord2, double * coord3, 
				double * velocity1, double * velocity2, double * velocity3)
{
	std::cout << "t; u_euler; u_runge; u_precise" << std::endl;
	for(int i(0); i <= PERIOD_NUMBER * N; ++i)
	{
		std::cout << i * tau << "; " << coord1[i] << "; " << coord2[i] << "; " << coord3[i] << std::endl;
	}
}

void Simple_solution(double tau, double * coord3, double * velocity3)
{
	double OMEGA = sqrt(double(G) / double(L) - (double(LAMBDA) / double(L)) * (double(LAMBDA) / double(L)));
	for(int i(0); i <= PERIOD_NUMBER * N; ++i)
	{
		double A = double(V0) / double(OMEGA);
		coord3[i] = A * exp(double(-LAMBDA * i * tau) / double(L)) * sin(double(OMEGA * i * tau));
	}
}




int main()
{


	// tau init
	std::cout << "Hello!\n";
	double Period_T = 2.0 * M_PI * sqrt((double(L) / double(G)));
	std::cout << "Period_T = " <<  Period_T << std::endl;
	
	double tau = Period_T / N;
	std::cout << "tau = " <<  tau << std::endl;

	// array mem alloc for PERIOD_NUMBER * N + 1 points from PERIOD_NUMBER period for N tau
	double* coord1 =    new double[PERIOD_NUMBER * N + 1];
	double* coord2 =    new double[PERIOD_NUMBER * N + 1];
	double* coord3 =    new double[PERIOD_NUMBER * N + 1];

	double* velocity1 = new double[PERIOD_NUMBER * N + 1];
	double* velocity2 = new double[PERIOD_NUMBER * N + 1];
	double* velocity3 = new double[PERIOD_NUMBER * N + 1];


	EulerSolution(tau, coord1, velocity1);
	RungeKutta(tau, coord2, velocity2);
	Simple_solution(tau, coord3, velocity3);
	Print_data(tau, coord1, coord2, coord3, velocity1, velocity2, velocity3);

	delete [] coord1;
	delete [] velocity1;
	delete [] coord2;
	delete [] velocity2;
	delete [] coord3;
	delete [] velocity3;
}