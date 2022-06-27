// Complex.hpp
// в данном файле реализован класс Complex для работы с комплексными числами

#include "Complex.hpp"


namespace cpx
{


// определяем точность сравнения
double CompareDouble::_epsilon{ 1.0e-10 };


// макрос сравнения числа с бесконечно малым
template<typename T>
bool CompareDouble::IsZero(const T& value) noexcept
{
	return static_cast<double>(value) < _epsilon && -static_cast<double>(value) < _epsilon;
}

// макрос равенства двух чисел с бесконечно малой точностью
template<typename T>
bool CompareDouble::AreEqual(const T& value1, const T& value2) noexcept
{
	return static_cast<double>(value1 - value2) < _epsilon && -static_cast<double>(value1 - value2) < _epsilon;
}

// метод установки свойств
void CompareDouble::SetEpsilon(const double& epsilon) noexcept
{
	_epsilon = epsilon;
}

// метод получения свойств
double CompareDouble::GetEpsilon(const double& epsilon) noexcept
{
	return _epsilon;
}


// определяем флаги
OutForm Complex::_outForm{ OutForm::OUT_ALG };
size_t Complex::_outPrecision{ 3u };


// определим тригонометрические функции от градусов, чтобы в дальнейшем не работать с радианами
// в данном случае актуален спецификатор inline, чтобы встраивать функции при компиляции и не вызывать их каждый раз
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

// нормализация угла необходима, чтобы аргумент комплексного числа не выходил за пределы (-180°; 180°]
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

// получение аргумента комплексного числа по его алгебраическим параметрам 
// одной функции _AtanDeg() не достаточно, она возвращает значения [-90; 90], а аргумент комплексного числа принимает (-180°; 180°]
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

// получение модуля комплексного числа по его алгебраическим параметрам 
inline double _Mod(const double& re, const double& im)
{
	return std::sqrt(re * re + im * im);
}


// конструкторо алгебраической формы
Complex::Complex(double re, double im)
	: _re(re)
	, _im(im)
{
	_mod = std::sqrt(_re * _re + _im * _im);
	_arg = _ArgDeg(_re, _im);
}

// конструктор экспоненциальной формы (третий параметр является лишь указанием конструктора экспоненциальной формы)
Complex::Complex(double mod, double arg, const ConstructForm&)
	: _mod(mod)
	, _arg(arg)
{
	_NormalizeDeg(_arg);

	_re = _mod * _CosDeg(_arg);
	_im = _mod * _SinDeg(_arg);
}

// операция отрицания
Complex Complex::operator-() const
{
	return Complex(-_re, -_im);
}

// операция комплексной сопряжённости
Complex Complex::operator*() const
{
	return Complex(_re, -_im);
}

// операция суммы
Complex operator+(const Complex& comlex1, const Complex& comlex2)
{
	Complex result(comlex1); // присваиваем результату первый параметр и к нему прибавляем второй

	result._re += comlex2._re;
	result._im += comlex2._im;
	result._mod = std::sqrt(result._re * result._re + result._im * result._im);
	result._arg = _ArgDeg(result._re, result._im);

	return result;
}

// операция разности
Complex operator-(const Complex& comlex1, const Complex& comlex2)
{
	Complex result(comlex1);

	result._re -= comlex2._re;
	result._im -= comlex2._im;
	result._mod = _Mod(result._re, result._im);
	result._arg = _ArgDeg(result._re, result._im);

	return result;
}

// операция умножения
Complex operator*(const Complex& comlex1, const Complex& comlex2)
{
	Complex result(comlex1);

	result._mod *= comlex2._mod;
	result._arg += comlex2._arg;
	_NormalizeDeg(result._arg); // нормализируем угол
	result._re = result._mod * _CosDeg(result._arg);
	result._im = result._mod * _SinDeg(result._arg);

	return result;
}

// операция деления
Complex operator/(const Complex& comlex1, const Complex& comlex2)
{
	Complex result(comlex1);

	result._mod /= comlex2._mod;
	result._arg -= comlex2._arg;
	_NormalizeDeg(result._arg); // нормализируем угол
	result._re = result._mod * _CosDeg(result._arg);
	result._im = result._mod * _SinDeg(result._arg);

	return result;
}

// операция суммы с присваиванием
Complex& Complex::operator+=(const Complex& comlex2)
{
	_re += comlex2._re;
	_im += comlex2._im;
	_mod = _Mod(_re, _im);
	_arg = _ArgDeg(_re, _im);

	return *this;
}

// операция разности с присваиванием
Complex& Complex::operator-=(const Complex& comlex2)
{
	_re -= comlex2._re;
	_im -= comlex2._im;
	_mod = _Mod(_re, _im);
	_arg = _ArgDeg(_re, _im);

	return *this;
}

// операция умножения с присваиванием
Complex& Complex::operator*=(const Complex& comlex2)
{
	_mod *= comlex2._mod;
	_arg += comlex2._arg;
	_NormalizeDeg(_arg); // нормализируем угол
	_re = _mod * _CosDeg(_arg);
	_im = _mod * _SinDeg(_arg);

	return *this;
}

// операция деления с присваиванием
Complex& Complex::operator/=(const Complex& comlex2)
{
	_mod /= comlex2._mod;
	_arg -= comlex2._arg;
	_NormalizeDeg(_arg); // нормализируем угол
	_re = _mod * _CosDeg(_arg);
	_im = _mod * _SinDeg(_arg);

	return *this;
}

// методы получения свойств
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

// методы установки свойств
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

// метод установки флага формы вывода комплексного числа
void Complex::SetOutForm(const OutForm& outForm)
{
	Complex::_outForm = outForm;
}

// метод установки количества знаков после запятой при выводе
void Complex::SetOutPrecision(const size_t& outPrecision)
{
	Complex::_outPrecision = outPrecision;
}

// операция равенства
bool Complex::operator==(const Complex& comlex2) const
{
	return CompareDouble::AreEqual(_re, comlex2._re) && CompareDouble::AreEqual(_im, comlex2._im);
}

// операция неравенства
bool Complex::operator!=(const Complex& comlex2) const
{
	return !CompareDouble::AreEqual(_re, comlex2._re) || !CompareDouble::AreEqual(_im, comlex2._im);
}

// метод преобразования в строку
std::string Complex::ToString() const
{
	std::ostringstream oss;

	oss.setf(std::ios::fixed);
	oss.precision(Complex::_outPrecision);

	if (Complex::_outForm == OutForm::OUT_ALG) // выбор формы вывода
	{
		if (!CompareDouble::IsZero(_re)) // проверяем значение на отличие от нуля, чтобы не выводить нулевые значения
		{
			oss << _re;
		}
		else
		{
			oss << '0';
		}

		if (!CompareDouble::IsZero(_im)) // проверяем значение на отличие от нуля, чтобы не выводить нулевые значения
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
		if (!CompareDouble::IsZero(_mod)) // проверяем значение на отличие от нуля, чтобы не выводить нулевые значения
		{
			oss << _mod;

			if (!CompareDouble::IsZero(_arg)) // проверяем значение на отличие от нуля, чтобы не выводить нулевые значения
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

// операция приведения Complex к double
Complex::operator double() const noexcept
{
	return _mod;
}

}