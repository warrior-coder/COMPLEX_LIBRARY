#include <iostream>
#include "Complex.hpp" // ���������� ���������� "Complex.hpp" ��� ������ � ������������ �������

using namespace std;

int main()
{
    auto c1 = cpx::Complex(1.0, 1.0);

    cpx::Complex::SetOutForm(cpx::OutForm::OUT_EXP);
    cout << c1 << endl;


    return 0;
}