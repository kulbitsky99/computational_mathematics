#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//LU-разложение
void LU(double **A, double **L, double **U, int n)
{
    for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				U[i][j] = A[i][j];

        for (int j = 0; j < n; j++)
			for (int i = 0; i < n; i++)
			{
                if(i > j)
                {
                    L[i][j] = U[i][j] / U[j][j];
                    for (int k = 0; k < n; k++)
                    {
                    U[i][k] = U[i][k] - L[i][j] * U[j][k];
                    }
                }
                if(i == j)
                    L[i][j] = 1;
                if(i < j)
                    L[i][j] = 0;


			}
}

int main()
{

    setlocale(LC_ALL, "RUSSIAN");
    vector<double> a;
    vector<double> b;
    vector<double> c;
    vector<double> f;

    ifstream a_in("a_diag8.txt");
    ifstream b_in("b_diag8.txt");
    ifstream c_in("c_diag8.txt");
    ifstream f_in("r8.txt");
    ofstream out("output_progon.txt");

	double temp = 0;
    while (!a_in.eof())
    {
        a_in >> temp;
        a.push_back(temp);
    }
    while (!b_in.eof())
    {
        b_in >> temp;
        b.push_back(temp);
    }
    while (!c_in.eof())
    {
        c_in >> temp;
        c.push_back(temp);
    }



        a_in.close();
        b_in.close();
        c_in.close();

        cout << "dim a = " << a.size() - 1 << endl;
        cout << "dim b = " << b.size() - 1 << endl;
        cout << "dim c = " << c.size() - 1 << endl;
        //cout << "dim r = " << f.size() - 1 << endl;
        int n = 0;
        n = c.size() - 1;

        //Аллоцируем место для матриц
		double **A;
		A = new double*[n];
		for (int i = 0; i < n; i++)
            A[i] = new double[n];

        double **L;
		L = new double*[n];
		for (int i = 0; i < n; i++)
            L[i] = new double[n];

        double **U;
		U = new double*[n];
		for (int i = 0; i < n; i++)
            U[i] = new double[n];

		int k = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				A[i][j] = 0;

            }
        for (int i = 0; i < n; i++)
        {
            A[i][i] = c[i];
        }
        for (int i = 0; i < n - 1; i++)
        {
            A[i + 1][i] = a[i];
        }
        for (int i = 0; i < n - 1; i++)
        {
            A[i][i + 1] = b[i];
        }


		LU(A, L, U, n);


		//Выведем матрицы
		/*out << "-----A-----" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				out << A[i][j] << " ";
			out << "\n";
		}

        out << "-----L-----" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				out << L[i][j] << " ";
			out << "\n";
		}

        out << "-----U-----" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				out << U[i][j] << " ";
			out << "\n";
		}*/

		//Решение СЛАУ

        vector<double> x;
        vector<double> y;

        temp = 0;
        while (!f_in.eof())
        {
            f_in >> temp;
            f.push_back(temp);
            x.push_back(0);
            y.push_back(0);
        }
        f_in.close();
        /*cout << "dim f = " << f.size() << endl;*/
        out << "f = ( " << endl;
        for (int i = 0; i < n; i++)
            out << f[i] << endl;
        out << ")" << endl;
        double sum = 0;

        for (int i = 0; i < n; i++)
        {
			for (int j = 0; j < i; j++)
			{
                sum += L[i][j] * y[j];
			}
			y[i] = (f[i] - sum) / L[i][i];
			sum = 0;
        }
        /*out << "y = ( ";
        for (int i = 0; i < n; i++)
            out << y[i] << " ";
        out << ")" << endl; */

        sum = 0;

        for (int i = n - 1; i >= 0; i--)
        {
			for (int j = n - 1; j >= i + 1; j--)
			{
                sum += U[i][j] * x[j];
			}
			x[i] = (y[i] - sum) / U[i][i];
			sum = 0;
        }
        out << "x = ( " << endl;
        for (int i = 0; i < n; i++)
            out << x[i] << endl;
        out << ")" << endl;

        //Вычисляем невязку
        double e = 0, coeff_1 = 0, Ax = 0, coeff_2 = 0;
        for (int i = 0; i < n; i++)
        {
			for (int j = 0; j < n; j++)
			{
                Ax +=A[i][j] * x[j];
			}
			coeff_1 += abs(Ax - f[i]);
			Ax = 0;
        }
        for (int i = 0; i < n; i++)
            coeff_2 += abs(f[i]);
        e = coeff_1 / coeff_2;
        out << "e = " << e << endl;





        //Удаляем матрицы из памяти
		for (int i = 0; i < n; i++)
            delete[] A[i];
		delete[] A;

		for (int i = 0; i < n; i++)
            delete[] L[i];
		delete[] L;

		for (int i = 0; i < n; i++)
            delete[] U[i];
		delete[] U;


		a_in.close();
		b_in.close();
		c_in.close();
		//r_in.close();
		out.close();




	return 0;
}
