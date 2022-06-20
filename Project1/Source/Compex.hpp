#pragma once

// Complex.hpp
// � ������ ����� ���������� ����� Complex ��� ������ � ������������ �������


#include <iostream>
#include <cmath>

// ����������� ����� ��

namespace cpx
{

constexpr double _pi = 3.14159265358979;
constexpr double _epsilon = 1.0e-10;

constexpr bool _IsZero(const double& value) noexcept // ������ ��������� ����� � ���������� �����
{
	return value < _epsilon && -value < _epsilon;
}

constexpr bool _IsEqual(const double& value1, const double& value2) noexcept // ������ ��������� ���� ����� � ���������� ����� ���������
{
	return (value1 - value2) < _epsilon && -(value1 - value2) < _epsilon;
}

// ��������� ������������������ ������� �� ��������, ����� � ���������� �� �������� � ���������
// � ������ ������ �������� ������������ inline, ����� ���������� ������� ��� ���������� � �� �������� �� ������ ���
inline double _AtanDeg(const double& value)
{ 
	return std::atan(value) / _pi * 180.0;
}

inline double _CosDeg(const double& angleDeg)
{
	return std::cos(angleDeg / 180.0 * _pi);
}

inline double _SinDeg(const double& angleDeg)
{
	return std::sin(angleDeg / 180.0 * _pi);
}


// ������������ ���� ����������, ����� �������� ������������ ����� �� ������� �� ������� (-180�; 180�]
inline void _NormalizeDeg(double& angleDeg)
{
	while (angleDeg > 180.0)
	{
		angleDeg -= 360.0;
	}
	
	while (angleDeg <= -180.0)
	{
		angleDeg += 360.0;
	}
}


// ������� ��������� ��������� ������������ ����� �� ��� �������������� ���������� 
// ����� ������� _AtanDeg() �� ����������, �.�. ��� ���������� �������� [-90; 90], � �������� ������������ ����� ��������� (-180�; 180�]
inline double _ArgDeg(double re, double im)
{
	if (re < 0.0)
	{
		if (im > 0.0) return _AtanDeg(im / re) + 180.0;
		else return _AtanDeg(im / re) - 180.0;
	}
	else if (_IsZero(re))
	{
		if (im > 0.0) return 90.0;
		else return -90.0;
	}
	return _AtanDeg(im / re);
}


// ������� ��������� ������ ������������ ����� �� ��� �������������� ���������� 
inline double _Mod(const double& re, const double& im)
{
	return std::sqrt(re * re + im * im);
}


// ���� ������������ ���������������� �����
enum ExpForm
{
	EXP_FORM
};


// ����� ����������� �����
class Complex
{
	double _re;		// �������������� �����
	double _im;		// ������ �����
	double _mod;	// ������
	double _arg;	// ��������

	// ���� ����� ������� ������������ �����
	static int _coutForm;

public:

	// ������������ �������������� �����
	Complex(double re = 0.0, double im = 0.0)
		: _re(re)
		, _im(im)
	{
		_mod = std::sqrt(_re * _re + _im * _im);
		_arg = _ArgDeg(_re, _im);
	}

	// ����������� ���������������� �����
	// ������ �������� ���� �������� ��������� ������������ ���������������� �����
	explicit Complex(double mod, double arg, ExpForm)
		: _mod(mod)
		, _arg(arg)
	{
		_re = _mod * _CosDeg(_arg);
		_im = _mod * _SinDeg(_arg);
	}

	// ��������� ������������� �������� �������� ������ �������������� �������� ��� ������������ �������
	// �� ���������� �������� �� ������������ � ��������������� ���� � ����� �������� ���������
	// �������� �������� ����������� ����� friend ������, ��� �������� ������ ��������� ����� �� ���������� �������� � ������������ �����

	// �������� ���������
	Complex operator-()
	{
		return Complex(-_re, -_im);
	}

	// �������� ����������� ������������
	Complex operator*()
	{
		return Complex(_re, -_im);
	}

	// �������� �����
	friend Complex operator+(const Complex& comlex1, const Complex& comlex2)
	{
		Complex result = comlex1; // ����������� ���������� ������ �������� � � ���� ���������� ������

		result._re += comlex2._re;
		result._im += comlex2._im;
		result._mod = std::sqrt(result._re * result._re + result._im * result._im);
		result._arg = _ArgDeg(result._re, result._im);

		return result;
	}

	// �������� ����� � �������������
	Complex& operator+=(const Complex& complex)
	{
		_re += complex._re;
		_im += complex._im;
		_mod = _Mod(_re, _im);
		_arg = _ArgDeg(_re, _im);

		return *this;
	}

	// �������� ��������
	friend Complex operator-(const Complex& comlex1, const Complex& comlex2)
	{
		Complex result = comlex1;

		result._re -= comlex2._re;
		result._im -= comlex2._im;
		result._mod = _Mod(result._re, result._im);
		result._arg = _ArgDeg(result._re, result._im);

		return result;
	}

	// �������� �������� � �������������
	Complex& operator-=(const Complex& complex)
	{
		_re -= complex._re;
		_im -= complex._im;
		_mod = _Mod(_re, _im);
		_arg = _ArgDeg(_re, _im);

		return *this;
	}

	// �������� ���������
	friend Complex operator*(const Complex& comlex1, const Complex& comlex2)
	{
		Complex result = comlex1;

		result._mod *= comlex2._mod;
		result._arg += comlex2._arg;
		_NormalizeDeg(result._arg); // ������������� ����
		result._re = result._mod * _CosDeg(result._arg);
		result._im = result._mod * _SinDeg(result._arg);

		return result;
	}


	// �������� ��������� � �������������
	Complex& operator*=(const Complex& complex)
	{
		_mod *= complex._mod;
		_arg += complex._arg;
		_NormalizeDeg(_arg); // ������������� ����
		_re = _mod * _CosDeg(_arg);
		_im = _mod * _SinDeg(_arg);

		return *this;
	}

	// �������� �������
	friend Complex operator/(const Complex& comlex1, const Complex& comlex2)
	{
		Complex result = comlex1;

		result._mod /= comlex2._mod;
		result._arg -= comlex2._arg;
		_NormalizeDeg(result._arg); // ������������� ����
		result._re = result._mod * _CosDeg(result._arg);
		result._im = result._mod * _SinDeg(result._arg);

		return result;
	}

	// �������� ������� � �������������
	Complex& operator/=(const Complex& complex)
	{
		_mod /= complex._mod;
		_arg -= complex._arg;
		_NormalizeDeg(_arg); // ������������� ����
		_re = _mod * _CosDeg(_arg);
		_im = _mod * _SinDeg(_arg);

		return *this;
	}

	// �������� ������������
	Complex& operator=(const Complex&) = default;

	// ������ ��������� �������
	inline double GetRe() const noexcept
	{ 
		return _re;
	}
	inline double GetIm() const noexcept
	{ 
		return _im;
	}
	inline double GetMod() const noexcept
	{ 
		return _mod;
	}
	inline double GetArg() const noexcept
	{ 
		return _arg;
	}

	// ������ ��������� �������
	inline void SetRe(const double& re)
	{
		_re = re;

		_mod = _Mod(_re, _im);
		_arg = _ArgDeg(_re, _im);
	}

	inline void SetIm(const double& im)
	{
		_im = im;

		_mod = _Mod(_re, _im);
		_arg = _ArgDeg(_re, _im);
	}
	
	inline void SetMod(const double& mod)
	{
		_mod = mod;

		_re = _mod * _CosDeg(_arg);
		_im = _mod * _SinDeg(_arg);
	}
	
	inline void SetArg(const double& arg)
	{
		_arg = arg;

		_re = _mod * _CosDeg(_arg);
		_im = _mod * _SinDeg(_arg);
	}
	
	friend std::ostream& alg(std::ostream& os)
	{
		Complex::_coutForm = 1;

		return os;
	}

	friend std::ostream& exp(std::ostream& os)
	{
		Complex::_coutForm = 0;

		return os;
	}

	// �������� ��������� � ����� ������
	friend std::ostream& operator<<(std::ostream& os, const Complex& complex)
	{
		// ����� ����� ������
		if (Complex::_coutForm)
		{
			// ��������� ��������� �� ������� �� ����, ����� �� �������� ������� ��������
			if (!_IsZero(complex._mod))
			{
				os << complex._mod;

				if (!_IsZero(complex._arg))
				{
					os << "e^";
					os << complex._arg << 'j';
				}
			}
			else os << "0";
		}
		else
		{
			if (_IsZero(complex._re)) os << complex._re;
			else os << "0";

			if (_IsZero(complex._im))
			{
				os.setf(std::ios::showpos);
				os << complex._im << 'j';
				os.unsetf(std::ios::showpos);
			}
			else os << "+0j";
		}

		return os;
	}
};

int Complex::_coutForm = 1; // ����������� ����������� ����������

}