#include <iostream>
#include "Complex.hpp" // ���������� ���� "Complex.hpp" ��� ������ � ������������ �������

using namespace std;
using namespace cpx;

int main()
{
    // ������������� ����� �������
    setlocale(LC_ALL, "ru");
    cout.precision(4);
    cout.setf(ios::fixed);

    Complex::SetOutForm(OUT_ALG);
    cout << Complex(1.0, 1.0) << endl;

    return 0;
}