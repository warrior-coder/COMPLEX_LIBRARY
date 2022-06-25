#pragma once

// Complex.hpp
// � ������ ����� ������ ����� Complex ��� ������ � ������������ �������


#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

namespace cpx
{

constexpr double _pi = 3.14159265358979;
constexpr double _epsilon = 1e-10; // ���������� ����� ����� ��� double

constexpr bool _IsZero(const double& value) noexcept // ������ ��������� ����� � ���������� �����
{
	return value < _epsilon && -value < _epsilon;
}

constexpr bool _IsEqual(const double& value1, const double& value2) noexcept // ������ ��������� ���� ����� � ���������� ����� ���������
{
	return (value1 - value2) < _epsilon && -(value1 - value2) < _epsilon;
}

inline double _AtanDeg(const double& value); // ������������������ ������� �� ��������
inline double _CosDeg(const double& angleDeg);
inline double _SinDeg(const double& angleDeg);

inline void _NormalizeDeg(double& angleDeg); // ������������ ����
inline double _ArgDeg(const double& re, const double& im); // ��������� ��������� � ������� ������������ ����� �� ��� �������������� ����������
inline double _Mod(const double& re, const double& im); // ��������� ������ ������������ ����� �� ��� �������������� ���������� 

enum ConstructForm // ���� ������������ ���������������� �����
{
	EXP
};

enum class OutForm // ����� ����� ������
{
	OUT_ALG,
	OUT_EXP
};


// ����� ����������� �����
class Complex
{
private:
	double _re;		// �������������� ����� (Real)
	double _im;		// ������ ����� (Imaginary)
	double _mod;	// ������ (Module)
	double _arg;	// �������� (Argument)

	static OutForm _outForm; // ���� ����� ������ ������������ �����
	static size_t _outPrecision; // ���� ���������� ������ ����� ������� ��� ������ ������������ �����

public:
	Complex(double re = 0.0, double im = 0.0); // ������������ �������������� �����
	
	explicit Complex(double mod, double arg, const ConstructForm&); // ����������� ���������������� �����

	~Complex() = default; // ����������

	Complex operator-() const; // �������� ���������
	Complex operator*() const; // �������� ����������� ������������
	
	friend Complex operator+(const Complex& comlex1, const Complex& comlex2); // �������� �����
	friend Complex operator-(const Complex& comlex1, const Complex& comlex2); // �������� ��������
	friend Complex operator*(const Complex& comlex1, const Complex& comlex2); // �������� ���������
	friend Complex operator/(const Complex& comlex1, const Complex& comlex2); // �������� �������

	Complex& operator+=(const Complex& comlex2); // �������� ����� � �������������
	Complex& operator-=(const Complex& comlex2); // �������� �������� � �������������
	Complex& operator*=(const Complex& comlex2); // �������� ��������� � �������������
	Complex& operator/=(const Complex& comlex2); // �������� ������� � �������������

	Complex& operator=(const Complex&) = default; // �������� ������������
	
	bool operator==(const Complex& comlex2) const; // �������� ���������
	bool operator!=(const Complex& comlex2) const; // �������� �����������

	double GetRe() const noexcept; // ������ ��������� �������
	double GetIm() const noexcept;
	double GetMod() const noexcept;
	double GetArg() const noexcept;

	void SetRe(const double& re); // ������ ��������� �������
	void SetIm(const double& im);
	void SetMod(const double& mod);
	void SetArg(const double& arg);
	
	static void SetOutForm(const OutForm& outForm); // ����� ��������� ����� ������
	static void SetOutPrecision(const size_t& outPrecision); // ����� ��������� ���������� ������ ����� ������� ��� ������ ������������ �����

	friend std::ostream& operator<<(std::ostream& os, const Complex& complex) // �������� ��������� � ����� ������
	{
		os.setf(std::ios::fixed);
		os.precision(Complex::_outPrecision);

		if (Complex::_outForm == OutForm::OUT_ALG) // ����� ����� ������
		{
			if (!_IsZero(complex._re)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
			{
				os << complex._re;
			}
			else
			{
				os << '0';
			}

			if (!_IsZero(complex._im)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
			{
				os.setf(std::ios::showpos);
				os << complex._im << 'j';
				os.unsetf(std::ios::showpos);
			}
			else
			{
				os << "+0j";
			}
		}
		else
		{
			if (!_IsZero(complex._mod)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
			{
				os << complex._mod;

				if (!_IsZero(complex._arg)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
				{
					os << "e^" << complex._arg << 'j';
				}
			}
			else
			{
				os << '0';
			}
		}

		return os;
	}

	std::string ToString() const; // ����� �������������� � ������
	operator double() const noexcept; // �������� ���������� Complex � double
};

}