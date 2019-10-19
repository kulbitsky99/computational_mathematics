#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//LU-����������
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

	ifstream in("A8.txt");
	ofstream out("output.txt");

	vector<double> array;
	double temp;
	while (!in.eof())
    {
        in >> temp;
        array.push_back(temp);
    }

		int n = sqrt(array.size());
		//cout << "n = " << n << endl;



		//������� ��������� ������� � ������ � ������ �����
		in.seekg(0, ios::beg);
		in.clear();
		in.close();


        //���������� ����� ��� ������
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

        ifstream input("A8.txt");
		//������� ������� �� �����
		int k = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				input >> A[i][j];

            }

		LU(A, L, U, n);


		//������� �������
		out << "-----A-----" << endl;
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
		}

		//������� ����
		ifstream f_in("f8.txt");

        vector<double> f;
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
        //cout << "dim f = " << f.size() << endl;
        out << "f = ( ";
        for (int i = 0; i < n; i++)
            out << f[i] << " ";
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
        out << "y = ( ";
        for (int i = 0; i < n; i++)
            out << y[i] << " ";
        out << ")" << endl;

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
        out << "x = ( ";
        for (int i = 0; i < n; i++)
            out << x[i] << " ";
        out << ")" << endl;

        //��������� �������
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





        //������� ������� �� ������
		for (int i = 0; i < n; i++)
            delete[] A[i];
		delete[] A;

		for (int i = 0; i < n; i++)
            delete[] L[i];
		delete[] L;

		for (int i = 0; i < n; i++)
            delete[] U[i];
		delete[] U;


		input.close();
		out.close();




	return 0;
}
