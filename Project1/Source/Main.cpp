#include <iostream>
#include "Complex.hpp" // подключаем файл "Complex.hpp" для работы с комплексными числами

using namespace std;
using namespace cpx;

int main()
{
    auto c1 = Complex(1.0, 1.0);

    Complex::SetOutForm(OutForm::OUT_EXP);
    cout << c1 << endl;

    return 0;
}