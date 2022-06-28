// Complex.hpp
// � ������ ����� ���������� ����� Complex ��� ������ � ������������ �������

#include "Complex.hpp"


namespace cpx
{

// ���������� �������� ���������
double CompareDouble::_epsilon{ 1.0e-10 };


// ������ ��������� ����� � ���������� �����
bool CompareDouble::IsZero(const double& value) noexcept
{
	return value < _epsilon && -value < _epsilon;
}

// ������ ��������� ���� ����� � ���������� ����� ���������
bool CompareDouble::AreEqual(const double& value1, const double& value2) noexcept
{
	return (value1 - value2) < _epsilon && -(value1 - value2) < _epsilon;
}

// ����� ��������� �������
void CompareDouble::SetEpsilon(const double& epsilon) noexcept
{
	_epsilon = epsilon;
}

// ����� ��������� �������
double CompareDouble::GetEpsilon(const double& epsilon) noexcept
{
	return _epsilon;
}


// ���������� �����
OutForm Complex::_outForm{ OutForm::OUT_ALG };
size_t Complex::_outPrecision{ 3u };


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

// ��������� ��������� ������������ ����� �� ��� �������������� ���������� 
// ����� ������� _AtanDeg() �� ����������, ��� ���������� �������� [-90; 90], � �������� ������������ ����� ��������� (-180�; 180�]
inline double _ArgDeg(const double& re, const double& im)
{
	if (re < 0.0)
	{
		if (im > 0.0) return _AtanDeg(im / re) + 180.0;
		else return _AtanDeg(im / re) - 180.0;
	}
	else if (CompareDouble::IsZero(re))
	{
		if (im > 0.0) return 90.0;
		else return -90.0;
	}
	return _AtanDeg(im / re);
}

// ��������� ������ ������������ ����� �� ��� �������������� ���������� 
inline double _Mod(const double& re, const double& im)
{
	return std::sqrt(re * re + im * im);
}


// ������������ �������������� �����
Complex::Complex(double re, double im)
	: _re(re)
	, _im(im)
{
	_mod = std::sqrt(_re * _re + _im * _im);
	_arg = _ArgDeg(_re, _im);
}

// ����������� ���������������� ����� (������ �������� �������� ���� ��������� ������������ ���������������� �����)
Complex::Complex(double mod, double arg, const ConstructForm&)
	: _mod(mod)
	, _arg(arg)
{
	_NormalizeDeg(_arg);

	_re = _mod * _CosDeg(_arg);
	_im = _mod * _SinDeg(_arg);
}

// �������� ���������
Complex Complex::operator-() const
{
	return Complex(-_re, -_im);
}

// �������� ����������� ������������
Complex Complex::operator*() const
{
	return Complex(_re, -_im);
}

// �������� �����
Complex operator+(const Complex& complex1, const Complex& complex2)
{
	Complex result(complex1); // ����������� ���������� ������ �������� � � ���� ���������� ������

	result._re += complex2._re;
	result._im += complex2._im;
	result._mod = std::sqrt(result._re * result._re + result._im * result._im);
	result._arg = _ArgDeg(result._re, result._im);

	return result;
}

// �������� ��������
Complex operator-(const Complex& complex1, const Complex& complex2)
{
	Complex result(complex1);

	result._re -= complex2._re;
	result._im -= complex2._im;
	result._mod = _Mod(result._re, result._im);
	result._arg = _ArgDeg(result._re, result._im);

	return result;
}

// �������� ���������
Complex operator*(const Complex& complex1, const Complex& complex2)
{
	Complex result(complex1);

	result._mod *= complex2._mod;
	result._arg += complex2._arg;
	_NormalizeDeg(result._arg); // ������������� ����
	result._re = result._mod * _CosDeg(result._arg);
	result._im = result._mod * _SinDeg(result._arg);

	return result;
}

// �������� �������
Complex operator/(const Complex& complex1, const Complex& complex2)
{
	Complex result(complex1);

	result._mod /= complex2._mod;
	result._arg -= complex2._arg;
	_NormalizeDeg(result._arg); // ������������� ����
	result._re = result._mod * _CosDeg(result._arg);
	result._im = result._mod * _SinDeg(result._arg);

	return result;
}

// �������� ����� � �������������
Complex& Complex::operator+=(const Complex& complex2)
{
	_re += complex2._re;
	_im += complex2._im;
	_mod = _Mod(_re, _im);
	_arg = _ArgDeg(_re, _im);

	return *this;
}

// �������� �������� � �������������
Complex& Complex::operator-=(const Complex& complex2)
{
	_re -= complex2._re;
	_im -= complex2._im;
	_mod = _Mod(_re, _im);
	_arg = _ArgDeg(_re, _im);

	return *this;
}

// �������� ��������� � �������������
Complex& Complex::operator*=(const Complex& complex2)
{
	_mod *= complex2._mod;
	_arg += complex2._arg;
	_NormalizeDeg(_arg); // ������������� ����
	_re = _mod * _CosDeg(_arg);
	_im = _mod * _SinDeg(_arg);

	return *this;
}

// �������� ������� � �������������
Complex& Complex::operator/=(const Complex& complex2)
{
	_mod /= complex2._mod;
	_arg -= complex2._arg;
	_NormalizeDeg(_arg); // ������������� ����
	_re = _mod * _CosDeg(_arg);
	_im = _mod * _SinDeg(_arg);

	return *this;
}

// ������ ��������� �������
double Complex::GetRe() const noexcept
{ 
	return _re;
}

double Complex::GetIm() const noexcept
{ 
	return _im;
}

double Complex::GetMod() const noexcept
{ 
	return _mod;
}

double Complex::GetArg() const noexcept
{ 
	return _arg;
}

// ������ ��������� �������
void Complex::SetRe(const double& re)
{
	_re = re;

	_mod = _Mod(_re, _im);
	_arg = _ArgDeg(_re, _im);
}

void Complex::SetIm(const double& im)
{
	_im = im;

	_mod = _Mod(_re, _im);
	_arg = _ArgDeg(_re, _im);
}
	
void Complex::SetMod(const double& mod)
{
	_mod = mod;

	_re = _mod * _CosDeg(_arg);
	_im = _mod * _SinDeg(_arg);
}
	
void Complex::SetArg(const double& arg)
{
	_arg = arg;

	_re = _mod * _CosDeg(_arg);
	_im = _mod * _SinDeg(_arg);
}

// ����� ��������� ����� ����� ������ ������������ �����
void Complex::SetOutForm(const OutForm& outForm)
{
	Complex::_outForm = outForm;
}

// ����� ��������� ���������� ������ ����� ������� ��� ������
void Complex::SetOutPrecision(const size_t& outPrecision)
{
	Complex::_outPrecision = outPrecision;
}

// �������� ���������
bool Complex::operator==(const Complex& complex2) const
{
	return CompareDouble::AreEqual(_re, complex2._re) && CompareDouble::AreEqual(_im, complex2._im);
}

// �������� �����������
bool Complex::operator!=(const Complex& complex2) const
{
	return !CompareDouble::AreEqual(_re, complex2._re) || !CompareDouble::AreEqual(_im, complex2._im);
}

// ����� �������������� � ������ (���������� ��������� � ����� ������ ostream)
std::string Complex::ToString() const
{
	std::ostringstream oss;

	oss.setf(std::ios::fixed);
	oss.precision(Complex::_outPrecision);

	if (Complex::_outForm == OutForm::OUT_ALG) // ����� ����� ������
	{
		if (!CompareDouble::IsZero(_re)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
		{
			oss << _re;
		}
		else
		{
			oss << '0';
		}

		if (!CompareDouble::IsZero(_im)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
		{
			oss.setf(std::ios::showpos);
			oss << _im << 'j';
			oss.unsetf(std::ios::showpos);
		}
		else
		{
			oss << "+0j";
		}
	}
	else
	{
		if (!CompareDouble::IsZero(_mod)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
		{
			oss << _mod;

			if (!CompareDouble::IsZero(_arg)) // ��������� �������� �� ������� �� ����, ����� �� �������� ������� ��������
			{
				oss << "e^" << _arg << 'j';
			}
		}
		else
		{
			oss << '0';
		}
	}

	return oss.str();
}

}