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

    ifstream a_in("a_diag.txt");
    ifstream b_in("b_diag.txt");
    ifstream c_in("c_diag.txt");
    ifstream r_in("r.txt");
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
    double coeff_1 = c[0] / b[0];
    alpha.push_back(coeff_1);
    for(int i = 1; i < c.size() - 1; i++)
    {
            coeff_1 = c[i] / (b[i] - alpha[i - 1] * a[i - 1]);
            alpha.push_back(coeff_1);
    }
    coeff_1 = r[0] / b[0];
    beta.push_back(coeff_1);
    for(int i = 1; i < c.size(); i++)
    {
        coeff_1 = (r[i] - beta[i - 1] * a[i - 1]) / (b[i] - alpha[i - 1] * a[i - 1]);
        beta.push_back(coeff_1);
    }

    vector<double> x(b.size() - 1);
    int n = b.size() - 2;
    x[n] = beta[n];

    for(int i = n - 1; i >= 0; i--)
    {
        x[i] = beta[i] - alpha[i] * x[i + 1];
    }

    /*out << "dim alpha = " << alpha.size() << endl;
    out << "alpha = ( ";
    for (int i = 0; i < alpha.size(); i++)
        out << alpha[i] << " ";
    out << ")" << endl;

    out << "dim beta = " << beta.size() << endl;
    out << "beta = ( ";
    for (int i = 0; i < beta.size(); i++)
        out << beta[i] << " ";
    out << ")" << endl;*/

    out << "x; approximate_desicion[i]; precise_desicion[i] = ( " << endl;
    for (int i = 0; i < x.size(); i++)
    {
        out << 0.05 * i << "; "; // x
        out << x[i] << "; "; // approximate desicion
        out << (0.05 * i) * exp(0.05 * i) << endl; //precise desicion: y = x*e^x 
    }
    out << ")" << endl;

    //Cubical error computation
    double error = fabs(x[0]); // |x[0] - y[0]|
    for (int i = 0; i < x.size(); i++)
    {
        if(fabs(x[i] - (0.05 * i) * exp(0.05 * i)) > error)
            error = fabs(x[i] - (0.05 * i) * exp(0.05 * i));
    }
    out << "Cubical error = " << error << endl;
    out << "h^2 = " << 0.05 * 0.05 <<"; => Cubical error = O(h^2) = C * h^2." << endl;
    out.close();



    return 0;
}
