/*

class ErrorMatrix : public std::exception
{
public:
	ErrorMatrix(const std::string& message) : message_(message) {}
	const char* what() const throw() { return message_.c_str(); };
private:
	std::string message_;
};

// Присваивание - ОК

template<typename T1>
Matrix<T1>& Matrix<T1>::operator = (const Matrix<T1>& rigth)
{
	// Очищение памяти
	for (size_t i = 0; i < rigth.m_rows; ++i)
	{
		 delete[] this->m_ptr[i];
	}
	delete[] m_ptr;
	// Копирование данных из rigth в *this
	this->m_rows = rigth.m_rows;
	this->m_columns = rigth.m_columns;
	this->m_ptr = new T1 * [this->m_rows];
	for (size_t i = 0; i < this->m_rows; ++i)
	{
		for (size_t j = 0; j < this->m_columns; ++j)
		{
			this->m_ptr[i][j] = rigth.m_ptr[i][j];
		}
	}
	return *this;
}

// Перегрузка оператора вывода

template<typename T1>
std::ostream& operator << (std::ostream& out,const Matrix<T1> &object)
{
	for (size_t j = 0; j < object.m_columns; ++j)
	{
		out << "-----------";
	}
	out << '\n';
	for (size_t i = 0; i < object.m_rows; ++i)
	{
		for (size_t j = 0; j < object.m_columns; ++j)
		{
			out << "           ";
		}
		out << "\n*\t" << object.m_ptr[i][0];
		for (size_t j = 1; j < object.m_columns; ++j)
		{
			out << "\t" << object.m_ptr[i][j];
		}
		out << "\t*\n";
		for (size_t j = 0; j < object.m_columns; ++j)
		{
			out << "           ";
		}
		out << '\n';
	}
	for (size_t j = 0; j < object.m_columns; ++j)
	{
		out << "-----------";
	}
	out << '\n';
	return out;
}

// Перегрузка оператора + (матрица+матрица)
template <typename T1>
Matrix<T1> Matrix<T1>::operator+(const Matrix<T1>& rigth)
{
	Matrix<T1> result(m_rows, m_columns);
	for (size_t i = 0; i < m_rows; ++i)
	{
		for (size_t j = 0; j < m_columns; ++j)
		{
			result.m_ptr[i][j] = m_ptr[i][j] + rigth.m_ptr[i][j];
		}
	}
	return result;
}

// Перегрузка операторы + (матрица+число)

template <typename T1>
Matrix<T1> Matrix<T1>::operator+(T1 value)
{
	Matrix<T1> result(*this);
	for (size_t i = 0; i < m_rows; ++i)
	{
		for (size_t j = 0; j < m_columns; ++j)
		{
			result.m_ptr[i][j] += value;
		}
	}
	return result;
}

// Перегрузка оператора + (число+матрица)
template<typename T1>
Matrix<T1> operator+(T1 value, Matrix<T1>& rigth)
{
	return (rigth + value);
}

// Перегрузка оператора - (матрица-матрица)

template <typename T1>
Matrix<T1> Matrix<T1>::operator-(const Matrix<T1>& rigth)
{
	Matrix<T1> result(m_rows, m_columns);
	for (size_t i = 0; i < m_rows; ++i)
	{
		for (size_t j = 0; j < m_columns; ++j)
		{
			result.m_ptr[i][j] = m_ptr[i][j] - rigth.m_ptr[i][j];
		}
	}
	return result;
}

// Перегрузка операторы - (матрица-число)

template <typename T1>
Matrix<T1> Matrix<T1>::operator-(T1 value)
{
	Matrix<T1> result(*this);
	for (size_t i = 0; i < m_rows; ++i)
	{
		for (size_t j = 0; j < m_columns; ++j)
		{
			result.m_ptr[i][j] -= value;
		}
	}
	return result;
}

// Перегрузка оператора - (число-матрица)
template<typename T1>
Matrix<T1> operator-(T1 value, Matrix<T1>& rigth)
{
	Matrix<T1> result(rigth);
	for (size_t i = 0; i < result.m_rows; ++i)
	{
		for (size_t j = 0; j < result.m_columns; ++j)
		{
			result.m_ptr[i][j] *= -1;
		}
	}
	return (result + value);
}


// Перегрузка оператора * (матрица*матрица)
template<typename T1>
Matrix<T1> Matrix<T1>::operator*(const Matrix<T1>& rigth)
{
	Matrix<T1> result(m_rows, rigth.m_columns);
	// Исключение умножение матриц
	try
	{
		if ((*this).m_columns != rigth.m_rows)
		{
			ErrorMatrix error("SIZE");
			throw error;
			Matrix<T1> tmp(m_rows, m_columns);
			return tmp;
		}
		for (size_t i = 0; i < result.m_rows; i++)
		{
			for (size_t j = 0; j < result.m_columns; j++)
			{
				for (size_t k = 0; k < m_columns; k++)
				{
					result.m_ptr[i][j] += (m_ptr[i][k] * rigth.m_ptr[k][j]);
				}
			}
		}
	}
	catch (ErrorMatrix& e)
	{
		
	}
	return result;
}


// Перегрузка оператора *= (матрица*=матрица)
template<typename T1>
Matrix<T1>& Matrix<T1>::operator*=(const Matrix<T1>& rigth)
{
	return (*this = (*this * rigth));
}

// Перегрузка оператора +=(матрица+=матрица)
template<typename T1>
Matrix<T1>& Matrix<T1>::operator+=(const Matrix<T1>& rigth)
{
	return (*this = (*this + rigth));
}

// Перегрузка оператра -=(матрица-=матрица)
template<typename T1>
Matrix<T1>& Matrix<T1>::operator-=(const Matrix<T1>& rigth)
{
	return (*this = (*this - rigth));
}

// Перегрузка оператора * (матрица*число)
template<typename T1>
Matrix<T1> Matrix<T1>::operator*(T1 value)
{
	Matrix result(*this);
	for (size_t i = 0; i < m_rows; ++i)
	{
		for (size_t j = 0; j < m_columns; ++j)
		{
			result.m_ptr[i][j] *= value;
		}
	}
	return result;
}


// Перегрузка оператора * (число*матрица)
template<typename T1>
Matrix<T1> operator * (T1 value, Matrix<T1>& right)
{
	return(right * value);
}

*/