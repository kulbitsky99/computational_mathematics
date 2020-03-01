/*The task is to solve Laplas equation on the plato X*Y = (0;1)*(0;1),
using finite difference method with the certain step. This program
makes matrix A in (A*u(x,y)=B), right part is known from the task condition.
Then you can take matrix A and B from "output.txt" and easily solve this system -> find u(x;y).*/
#include <iostream>
#include <fstream>
#include <cmath>

enum Const
{
	STEPS = 20
};

void print_matrix(int** A, int size)
{
	std::ofstream A_out("A.txt");
	A_out << "[";
	for(int i = 0; i < size; i++)
	{
		A_out << "[";
		for(int j = 0; j < size - 1; j++)
		{
			A_out << A[i][j] << ", ";
		}
		A_out << A[i][size - 1] << "],\n";
	}
	A_out << "]";
	A_out.close();
}


int main()
{
	int** A;
	A = new int* [(STEPS - 1) * (STEPS - 1) + 1];
	for (int i = 0; i < (STEPS - 1) * (STEPS - 1) + 1; i++)
        A[i] = (int*)calloc((STEPS - 1) * (STEPS - 1) + 1, sizeof(int));
    double* B = (double*)calloc((STEPS - 1) * (STEPS - 1) + 1, sizeof(double));
    B[180] = 1 / static_cast<double>(STEPS * STEPS); //central knot 180
    for(int i = 0; i < (STEPS - 1) * (STEPS - 1); i++)
    {
    	A[i][i] = 4;
    	if((i + 1) % (STEPS - 1) != 0)
    		A[i][i + 1] = -1;
    	if(i % (STEPS - 1) != 0 && (i - 1) >= 0)
	    	A[i][i - 1] = -1;
	    if((i + (STEPS - 1)) < ((STEPS - 1) * (STEPS - 1)))
	    	A[i][i + (STEPS - 1)] = -1;
	    if((i - (STEPS - 1)) >= 0)
	    	A[i][i - (STEPS - 1)] = -1;
    }
    print_matrix(A, (STEPS - 1) * (STEPS - 1));

    std::ofstream B_out("B.txt");
    B_out << "[";
    for(int i = 0; i < (STEPS - 1) * (STEPS - 1); i++)
    	B_out << B[i] << ", ";
    B_out << "]\n";
    B_out.close();

    for (int i = 0; i < (STEPS - 1) * (STEPS - 1); i++)
        delete[] A[i];
	delete[] A;
	delete[] B;

	return 0;
}