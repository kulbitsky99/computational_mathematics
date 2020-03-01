#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    vector<double> a;
    vector<double> b;
    vector<double> c;
    vector<double> r;
    vector<double> A;

    ifstream a_in("a_diag8.txt");
    ifstream b_in("b_diag8.txt");
    ifstream c_in("c_diag8.txt");
    ifstream r_in("r8.txt");
    ifstream A_in("A8.txt");
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
    while (!r_in.eof())
    {
        r_in >> temp;
        r.push_back(temp);
    }
    while (!A_in.eof())
    {
        A_in >> temp;
        A.push_back(temp);
    }



        a_in.close();
        b_in.close();
        c_in.close();
        r_in.close();
        A_in.close();

        cout << "dim a = " << a.size() - 1 << endl;
        cout << "dim b = " << b.size() - 1 << endl;
        cout << "dim c = " << c.size() - 1 << endl;
        cout << "dim r = " << r.size() - 1 << endl;
        cout << "dim A = " << A.size() - 1 << endl;



        vector<double> alpha;
        vector<double> beta;
        double coeff_1 = b[0] / c[0];
        alpha.push_back(coeff_1);
        for(int i = 1; i < b.size(); i++)
        {
                coeff_1 = b[i] / (c[i] - alpha[i-1] * a[i]);
                alpha.push_back(coeff_1);
        }
        coeff_1 = r[0] / c[0];
        beta.push_back(coeff_1);
        for(int i = 1; i < c.size(); i++)
        {
            coeff_1 = (r[i] - beta[i-1] * a[i]) / (c[i] - alpha[i-1] * a[i]);
            beta.push_back(coeff_1);
        }

        vector<double> x(c.size());
        int n = c.size() - 1;
        x[n] = beta[n];

        for(int i = n - 1; i >= 0; i--)
        {
            x[i] = beta[i] - alpha[i] * x[i + 1];
        }

        out << "dim alpha = " << alpha.size() - 1 << endl;
        out << "alpha = ( ";
        for (int i = 0; i < alpha.size() - 1; i++)
            out << alpha[i] << " ";
        out << ")" << endl;

        out << "dim beta = " << beta.size() - 1 << endl;
        out << "beta = ( ";
        for (int i = 0; i < beta.size() - 1; i++)
            out << beta[i] << " ";
        out << ")" << endl;

        out << "dim x = " << x.size() - 1 << endl;
        out << "x = ( " << endl;
        for (int i = 0; i < x.size() - 1; i++)
            out << x[i] << endl;
        out << ")" << endl;

        //Вычисляем невязку
        double e = 0, coeff_2 = 0, Ax = 0, coeff_3 = 0;
        for (int i = 0; i < n - 1; i++)
        {
            Ax = x[i] + alpha[i] * x[i+1] ;
			coeff_2 += abs(Ax - beta[i]);
			Ax = 0;
        }
        coeff_2 += abs(x[n - 1] - beta[n - 1]);
        for (int i = 0; i < n; i++)
            coeff_3 += abs(beta[i]);
        e = coeff_2 / coeff_3;
        out << "e = " << e << endl;
        out.close();



    return 0;
}
