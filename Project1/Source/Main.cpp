#include <iostream>
#include "Complex.hpp" // подключаем файл "Complex.hpp" для работы с комплексными числами

using namespace std;
using namespace cpx;

int main()
{
    // устанавливаем режим консоли
    setlocale(LC_ALL, "ru");
    cout.precision(4);
    cout.setf(ios::fixed);

    auto c1 = Complex(10, 9) + Complex(1, 90, EXP_FORM);

    cout << c1.GetRe() << endl;
    cout << c1.GetIm() << endl;
    cout << c1.GetMod() << endl;
    cout << c1.GetArg() << endl;

    cout << (c1 == Complex(10, 10)) << endl;
    cout << (c1 == Complex(11, 10)) << endl;
    cout << (c1 == Complex(11, 11)) << endl;
    cout << (c1 == Complex(10, 11)) << endl;

    return 0;
}