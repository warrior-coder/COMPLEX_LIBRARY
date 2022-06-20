#include <iostream>
#include "Compex.hpp"

using namespace std;
using namespace cpx;

int main()
{
    setlocale(LC_ALL, "ru");
    cout.precision(4);
    cout.setf(ios::fixed);

    auto c1 = Complex(10, 9) + Complex(1, 90, EXP_FORM);


    cout << c1.GetRe() << endl;
    cout << c1.GetIm() << endl;
    cout << c1.GetMod() << endl;
    cout << c1.GetArg() << endl;

    cout << c1 << endl;


    return 0;
}