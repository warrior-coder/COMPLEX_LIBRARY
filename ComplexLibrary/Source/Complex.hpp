// Complex.hpp
// � ������ ����� ������ ����� Complex ��� ������ � ������������ �������

#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>


namespace cpx
{

constexpr double _pi{ 3.14159265358979 }; // ����� ��


class CompareDouble // ����������� ����� ��������� ����� double � ��������� epsilon
{
private:
	CompareDouble(); // ��������� �������� �����������, ����� ��������� �������� ����������� ������

	static double _epsilon; // ���������� ����� ����� ��� double

public:
	template<typename T>
	static bool IsZero(const T& value) noexcept; // ������ ��������� ����� � ���������� �����

	template<typename T>
	static bool AreEqual(const T& value1, const T& value2) noexcept; // ������ ��������� ���� ����� � ���������� ����� ���������

	static void SetEpsilon(const double& epsilon) noexcept; // ����� ��������� �������
	static double GetEpsilon(const double& epsilon) noexcept; // ����� ��������� �������
};


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


class Complex // ����� ����������� �����
{
private:
	double _re;						// �������������� ����� (Real)
	double _im;						// ������ ����� (Imaginary)
	double _mod;					// ������ (Module)
	double _arg;					// �������� (Argument)

	static OutForm _outForm;		// ���� ����� ������ ������������ �����
	static size_t _outPrecision;	// ���� ���������� ������ ����� ������� ��� ������ ������������ �����

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
			if (!CompareDouble::IsZero(complex._re)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
			{
				os << complex._re;
			}
			else
			{
				os << '0';
			}

			if (!CompareDouble::IsZero(complex._im)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
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
			if (!CompareDouble::IsZero(complex._mod)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
			{
				os << complex._mod;

				if (!CompareDouble::IsZero(complex._arg)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
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