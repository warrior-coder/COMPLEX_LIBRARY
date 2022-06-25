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

    Complex::SetOutForm(OUT_ALG);
    cout << Complex(1.0, 1.0) << endl;

    return 0;
}