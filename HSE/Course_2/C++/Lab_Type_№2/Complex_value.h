#pragma once

template<typename T = double>
class Complex
{
private:
	T re; // вещественная часть
	T im; // мнимая часть
public:
	Complex(T _re = 0, T _im = 0)
	{
		this->re = _re;
		this->im = _im;
	}
	// 
	T real() { return this->re; }
	T imag() { return this->im; }
	void real(T _re) { this->re = _re; }
	void imag(T _im) { this->im = _im; }
	// комплексное число+= обычное
	Complex<T> operator +=(T value)
	{
		this->re += value;
		return (*this);
	}
	// комплексное число+= комплексное число
	template<typename T1>
	Complex<T> operator+=(Complex<T1> value)
	{
		this->re += value.real();
		this->im += value.imag();
		return (*this);
	}
	// Комплексное число = обычное
	Complex<T> operator=(T value)
	{
		this->real(value);
		this->im = 0;
		return (*this);
	}
	// Комплексное число = комплексное
	template<typename T1>
	Complex<T> operator=(Complex<T1> value)
	{
		this->real(value.real());
		this->imag(value.imag());
		return (*this);
	}
	// Комлексное число -= обычное
	Complex<T> operator-=(T value)
	{
		this->re -= value;
		return (*this);
	}
	// Комплексное число -= комплексное
	template<typename T1>
	Complex<T> operator-=(Complex<T1> value)
	{
		this->re -= value.real();
		this->im -= value.imag();
		return (*this);
	}
	// Комплексное число *= обычное
	Complex<T> operator*=(T value)
	{
		this->re *= value;
		this->im *= value;
		return (*this);
	}
	// Комплексное число *= комплексное
	template<typename T1>
	Complex<T> operator*=(Complex<T1> value)
	{
		T tmp_re = this->re * value.real() - (this->im * value.imag());
		T tmp_im = this->re * value.imag() + (this->im * value.real());
		this->re = tmp_re;
		this->im = tmp_im;
		return (*this);
	}
	// Комплекснео число + обычное
	Complex<T> operator+(T value)
	{
		Complex<T> result = value + (*this);
		return result;
	}
	// Комплекснео число + комплексное
	template<typename T1>
	Complex<T> operator+(Complex<T1> value)
	{
		Complex<T> result(this->real() + value.real(), this->imag() + value.imag());
		return result;
	}


	// Комплексное число - обычное
	Complex<T> operator-(T value)
	{
		Complex<T> result(this->real() - value, this->imag());
		return result;
	}

	// Комплексное  - комплексное
	template<typename T1>
	Complex<T> operator-(Complex<T1> value)
	{
		Complex<T> result(this->real() - value.real(), this->imag() - value.imag());
		return result;
	}
	// Комплексное число * обычное
	Complex<T> operator*(T value)
	{
		Complex<T> result(this->real() * value, this->imag());
		return result;
	}
	// Комплексное * комплексное
	template<typename T1>
	Complex<T> operator*(Complex<T1> value)
	{
		T tmp_re = this->re * value.real() - (this->im * value.imag());
		T tmp_im = this->re * value.imag() + (this->im * value.real());
		Complex<T> result(tmp_re, tmp_im);
		return result;
	}
	// Комплексное / комплексное
	template<typename T1>
	Complex<T> operator/(Complex<T1> value)
	{
		T tmp_re = (this->re * value.real() + this->im * value.imag())/(value.real() * value.real() + value.imag() * value.imag());
		T tmp_im = (value.real() * this->im - this->re * value.imag()) / (value.real() * value.real() + value.imag() * value.imag());
		Complex<T> result(tmp_re, tmp_im);
		return result;
	}


	//
	template<typename T, typename T1>
	friend Complex<T1> operator+(T value, Complex<T1>& rigth);
	template<typename T, typename T1>
	friend Complex<T1> operator-(T value, Complex<T1>& rigth);
	template<typename T, typename T1>
	friend Complex<T1> operator*(T value, Complex<T1>& rigth);


	template<typename T1>
	friend std::istream& operator >> (std::istream& in, Complex<T1>& object);
	template<typename T1>
	friend std::ostream& operator << (std::ostream& out,const Complex<T1>& object);
};


// Обычное число + Комплексное
template<typename T, typename T1>
Complex<T1> operator+(T value, Complex<T1>& rigth)
{
	Complex<T1> result(rigth.real(), rigth.imag());
	result += value;
	return result;
}

// Обычное число - Комплексное
template<typename T, typename T1>
Complex<T1> operator-(T value, Complex<T1>& rigth)
{
	Complex<T1> result(value - rigth.real(), -rigth.imag());
	return result;
}

// Обычное число * Комплексное
template<typename T, typename T1>
Complex<T1> operator*(T value, Complex<T1>& rigth)
{
	Complex<T1> result(rigth.real()*value, rigth.imag()*value);
	return result;
}


// Перегрузка оператора вывода
template<typename T1>
std::ostream& operator << (std::ostream& out,const Complex<T1>& object)
{
	
	out << object.re << ' ';
	if (object.im < 0)
	{
		out << object.im << "i ";
	}
	else
	{
		out << "+" << object.im << "i ";
	}
	//out << '\n';
	return out;
}


// Уже работает
// Перегрузка оператора ввода - не сделано!
template<typename T1>
std::istream& operator >> (std::istream& in, Complex<T1>& object)
{
	T1 _re = 0, _im = 0;
	in >> _re >> _im;
	object.real(_re);
	object.imag(_im);
	return in;
}