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

    ifstream a_in("a_diag8.txt");
    ifstream b_in("b_diag8.txt");
    ifstream c_in("c_diag8.txt");
    ifstream r_in("r8.txt");

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


        a_in.close();
        b_in.close();
        c_in.close();
        r_in.close();

        cout << "dim a = " << a.size() - 1 << endl;
        cout << "dim b = " << b.size() - 1 << endl;
        cout << "dim c = " << c.size() - 1 << endl;
        cout << "dim r = " << r.size() - 1 << endl;


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
        cout << "dim x = " << x.size() - 1 << endl;
        cout << "x = ( ";
        for (int i = 0; i < x.size() - 1; i++)
            cout << x[i] << " ";
        cout << ")" << endl;

    return 0;
}
