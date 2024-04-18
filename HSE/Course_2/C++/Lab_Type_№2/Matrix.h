

namespace linalg
{

	// Класс ошибок линейной алгебры
	class LinAlgError
	{
		std::string message;
	public:
		LinAlgError(std::string _message)
		{
			this->message = _message;
		}
		std::string what() const {
			return message;
		}
	};
	





	template<typename T = double>
	class Matrix
	{
	private:
		T** m_ptr = nullptr; // указатель на динамический массив
		size_t m_rows; // кол-во строк
		size_t m_columns; // кол-во столбцов
	public:
		// конструктор - ОК!
		Matrix(size_t rows, size_t columns = 1)
		{
			m_rows = rows;
			m_columns = columns;
			m_ptr = new T * [rows];
			for (size_t i = 0; i < rows; ++i) m_ptr[i] = new T[columns];
			for (size_t i = 0; i < rows; ++i)
			{
				for (size_t j = 0; j < columns; ++j) m_ptr[i][j] = 0;
			}
		}
		// конструктор копирования - ОК!
		Matrix(const Matrix& rigth)
		{
			m_rows = rigth.m_rows;
			m_columns = rigth.m_columns;
			m_ptr = new T * [m_rows];
			for (size_t i = 0; i < m_rows; ++i) m_ptr[i] = new T[m_columns];
			for (size_t i = 0; i < m_rows; ++i) for (size_t j = 0; j < m_columns; ++j) m_ptr[i][j] = rigth.m_ptr[i][j];
		}
		// Конструктор перемещения
		Matrix(Matrix&& move_m)
		{
			// Конструктор перемещения вызывается при вызове функции std::move(), если его нет, то вызывается конструктор копирования
			// адреса памяти передаются новому объекту
			m_ptr = move_m.m_ptr;
			m_rows = move_m.m_rows;
			m_columns = move_m.m_columns;
			// удаление информации из move_m
			move_m.m_ptr = nullptr;
			move_m.m_rows = 0;
			move_m.m_columns = 0;
		}
		// Перемещающие присваивание
		template<typename T1>
		Matrix<T1>& operator=(Matrix<T1>&& rigth)
		{
			// перенос данных
			m_rows = rigth.m_rows;
			m_columns = rigth.m_columns;
			m_ptr = rigth.m_ptr;
			// очищение правого объекта
			rigth.m_ptr = nullptr;
			rigth.m_rows = 0;
			rigth.m_columns = 0;
			return *this;

		}
		// Конструктор инициализации
		Matrix(const std::initializer_list<T>& list)
		{
			m_columns = 1;
			m_rows = list.size();
			m_ptr = new T * [m_rows];
			for (size_t i = 0; i < m_rows; i++)
			{
				m_ptr[i] = new T[m_columns];
			}

			size_t i = 0;
			for (auto& element : list)
			{
				m_ptr[i][0] = (T)element;
				++i;
			}
		}
		Matrix(const std::initializer_list<std::initializer_list<T>>& list)
		{
			m_rows = list.size();
			m_columns = list.begin()->size();
			m_ptr = new T * [m_rows];
			for (size_t i = 0; i < m_rows; i++)
			{
				m_ptr[i] = new T[m_columns];
			}

			size_t i = 0;
			size_t j = 0;
			for (auto& element : list)
			{
				for (auto& h : element)
				{
					m_ptr[i][j] = (T)h;
					++j;
				}
				++i;
				j = 0;
			}
		}

		// Функционал матрицы
		T det();
		size_t rank();
		template<typename T1>
		friend Matrix<T1> transpose(Matrix<T1>& rigth);
		double trace();
		/*
		template<typename T1>
		friend Matrix<T1> inv(const Matrix<T1>& rigth);
		*/
		template<typename T1>
		friend Matrix<T1> inv(Matrix<T1> A);
		template<typename T1>
		Matrix<T1> pow(const Matrix<T1>& rigth, size_t deg);
		double norm();
		template<typename T1>
		friend double multy_scalar(Matrix<T1>& left, Matrix<T1>& rigth);
		template<typename T1>
		friend double angle(Matrix<T1>& left, Matrix<T1>& rigth);
		template<typename T1>
		friend Matrix<T1> unit(Matrix<T1>& vector);
		template<typename T1>
		friend Matrix<T1> multy_vector(Matrix<T1>& left_vector, Matrix<T1>& rigth_vector);
		template<typename T1>
		friend Matrix<T1> solve(Matrix<T1> A, Matrix<T1> B);
		// Перегрузка операторов
		Matrix<T> operator + (const Matrix<T>& rigth);
		Matrix<T> operator+(T value);
		Matrix<T>& operator = (const Matrix<T>& right);
		Matrix<T> operator - (const Matrix<T>& rigth);
		Matrix<T> operator - (T value);
		Matrix<T> operator*(const Matrix<T>& rigth);
		Matrix<T>& operator*=(const Matrix<T>& rigth);
		Matrix<T>& operator+=(const Matrix<T>& rigth);
		Matrix<T>& operator-=(const Matrix<T>& rigth);
		Matrix<T> operator*(T value);
		template<typename T1>
		friend Matrix<T1> operator+(T1 value, Matrix<T1>& rigth);
		template<typename T1>
		friend Matrix<T1> operator-(T1 value, Matrix<T1>& rigth);
		template<typename T1>
		friend Matrix<T1> operator*(T1, Matrix<T1>& rigth);
		template<typename T1>
		friend bool operator ==(Matrix<T1> A, Matrix<T1> B);
		// Перегрузка оператора вывода
		template<typename T1>
		friend std::ostream& operator << (std::ostream& out, const Matrix<T1>& object);
		// Перегрузка оператора ()
		T& operator () (size_t _row, size_t _column) const
		{
			return m_ptr[_row][_column];
		}
		/*const T& operator () (size_t _row, size_t _column) const
		{
			return m_ptr[_row][_column];
		}*/
	};

	// Функционал МАТРИЦЫ, заложенный при первой ЛР


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
	std::ostream& operator << (std::ostream& out, const Matrix<T1>& object)
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
		// Проверка на единичную - работает только для обычных типов
		/*
		for (size_t i = 0; i < result.m_rows; i++)
		{
			for (size_t j = 0; j < result.m_columns; j++)
			{
				if (((result(i,j)<1e-15)||(-result(i,j)<1e-15))&&(i!=j))
				{
					result(i,j)=0.0;
				}
			}
		}
		*/
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


	// Перегрузка оператора сравнения
	template<typename T1>
	bool operator ==(Matrix<T1> A, Matrix<T1> B)
	{
		size_t size_A = A.rank();
		size_t size_B = B.rank();
		if (size_A != size_B)
		{
			return false;
		}
		for (size_t i = 0; i < size_A; i++)
		{
			for (size_t j = 0; j < size_A; j++)
			{
				if (A(i, j) != B(i, j))
				{
					return false;
				}
			}
		}
		return true;
	}


	// РАСШИРЯЮЩИЙ ФУНКЦИОНАЛ МАТРИЦЫ

	template<typename T1>
	void clearMemory(T1** TMP_MATRIX, size_t TMP_SIZE)
	{
		for (size_t i = 0; i < TMP_SIZE; i++)
		{
			delete[] TMP_MATRIX[i];
		}
		delete[]TMP_MATRIX;
	}


	template<typename T1>
	T1 FindDet(T1** MATRIX, size_t SIZE)
	{
		if (SIZE == 1)
		{
			return MATRIX[0][0];
		}
		else if (SIZE == 2)
		{
			return MATRIX[0][0] * MATRIX[1][1] - MATRIX[0][1] * MATRIX[1][0];
		}
		else
		{
			// Определитель матрицы
			T1 d = 0;
			for (size_t k = 0; k < SIZE; k++)
			{
				T1** M = new T1 * [SIZE - 1];
				for (size_t i = 0; i < SIZE - 1; i++)
				{
					M[i] = new T1[SIZE - 1];
				}
				for (size_t i = 1; i < SIZE; i++)
				{
					size_t t = 0;
					for (size_t j = 0; j < SIZE; j++)
					{
						if (j == k) continue;
						M[i - 1][t] = MATRIX[i][j];
						t++;
					}
				}
				d += pow(-1, k + 2) * MATRIX[0][k] * FindDet(M, SIZE - 1);
				// Очистка памяти
				clearMemory(M, SIZE - 1);
			}
			return d;
		}
	}

	// Вычисление определителя

	template<typename T1>
	T1 Matrix<T1>::det()
	{
		if (m_columns != m_rows)
		{
			throw LinAlgError("Matrix isn't square");
		}
		T1 DET = FindDet(this->m_ptr, this->m_columns);
		return DET;
	}

	// Транспонирование

	template<typename T1>
	Matrix<T1> transpose(Matrix<T1>& rigth)
	{
		Matrix<T1> New_Matrix(rigth.m_columns, rigth.m_rows);
		for (size_t i = 0; i < New_Matrix.m_columns; i++)
		{
			for (size_t j = 0; j < New_Matrix.m_rows; j++)
			{
				New_Matrix.m_ptr[j][i] = rigth.m_ptr[i][j];
			}
		}
		return New_Matrix;
	}


	// Ранг матрицы

	template<typename T1>
	size_t Matrix<T1>::rank()
	{

		Matrix<T1> tmp = (*this);
		// Проверка, нужно ли транспонировать
		if (this->m_columns > this->m_rows)
		{
			tmp = transpose(*this);
		}
		size_t rank = 0;
		for (size_t col = 0; col < tmp.m_columns; col++)
		{
			size_t row = rank;
			
			for (size_t i = rank + 1; i < tmp.m_rows; i++)
			{
				if (fabs(tmp.m_ptr[i][col]) > fabs(tmp.m_ptr[row][col]))
				{
					row = i;
				}
			}
			
			
			if (fabs(tmp.m_ptr[row][col]) < 1e-10)
			{
				continue;
			}
			
			for (size_t j = 0; j < tmp.m_columns; j++)
			{
				T1 tmp_value = tmp.m_ptr[rank][j];
				tmp.m_ptr[rank][j] = tmp.m_ptr[row][j];
				tmp.m_ptr[row][j] = tmp_value;
			}
			for (size_t i = 0; i < tmp.m_rows; i++)
			{
				if (i != rank)
				{
					T1 c = tmp.m_ptr[i][col] / tmp.m_ptr[rank][col];
					for (size_t j = col; j < tmp.m_columns; j++)
					{
						tmp.m_ptr[i][j] -= c * tmp.m_ptr[rank][j];
					}
				}
			}
			rank++;
		}
		return rank;
	}

	// След матрицы

	template<typename T1>
	double Matrix<T1>::trace()
	{
		double trace = 0;
		for (size_t i = 0; i < this->m_rows; i++)
		{
			trace += this->m_ptr[i][i];
		}
		return trace;
	}

	// Обратная матрица

	template<typename T1>
	Matrix<T1> inv(Matrix<T1> A)
	{
		if (A.m_rows != A.m_columns)
		{
			throw LinAlgError("The matrix isn't square, therefore it haven't inverse matrix");
		}
		T1 tmp;
		size_t size_A = A.rank();
		// Единичная матрица
		Matrix<T1> E(size_A, size_A);
		for (size_t i = 0; i < size_A; i++)
		{
			for (size_t j = 0; j < size_A; j++)
			{
				E(i, j) = 0;
				if (i == j)
				{
					E(i, j) = 1;
				}
			}
		}
		for (size_t i = 0; i < size_A; i++)
		{
			tmp = A(i, i);

			for (size_t j = 0; j < size_A; j++)
			{
				A(i, j) = A(i,j) / tmp;
				E(i, j) = E(i,j) / tmp;
			}

			for (size_t k = i + 1; k < size_A; k++)
			{
				tmp = A(k, i);

				for (size_t j = 0; j < size_A; j++)
				{
					A(k, j) -= A(i, j) * tmp;
					E(k, j) -= E(i, j) * tmp;
				}

			}
		}
		for (size_t i = size_A - 1; i > 0; i--)
		{
			for (int j = i - 1; j >= 0; j--)
			{
				tmp = A(j, i);

				for (size_t k = 0; k < size_A; k++)
				{
					A(j, k) -= A(i, k) * tmp;
					E(j, k) -= E(i, k) * tmp;
				}
			}
		}
		for (size_t i = 0; i < size_A; i++)
		{
			for (size_t j = 0; j < size_A; j++)
			{
				A(i, j) = E(i, j);
			}
		}
		return A;
	}






	// Не ОК! Совсем!
 
	/*
	template<typename T1>
	Matrix<T1> inv(const Matrix<T1>& rigth)
	{
		size_t SIZE = rigth.m_columns;

		T1** INVERSE_MATRIX;
		INVERSE_MATRIX = new T1 * [SIZE];
		for (size_t i = 0; i < SIZE; i++)
		{
			INVERSE_MATRIX[i] = new T1[SIZE];
		}

		T1** Copy;

		Copy = new T1 * [SIZE];
		for (size_t i = 0; i < SIZE; i++)
		{
			Copy[i] = new T1[SIZE];
		}

		for (size_t i = 0; i < SIZE; i++)
		{
			for (size_t j = 0; j < SIZE; j++)
			{
				Copy[i][j] = rigth.m_ptr[i][j];
			}
		}

		//Matrix<T1> INVERSE_MATRIX(SIZE, SIZE);

		for (size_t i = 0; i < SIZE; i++)
		{
			INVERSE_MATRIX[i][i] = 1;
		}

		for (size_t i = 0; i < SIZE; i++)
		{
			size_t t = i;
			for (size_t j = i + 1; j < SIZE; j++)
			{
				if (fabs(Copy[j][i]) > fabs(Copy[t][i]))
				{
					t = j;
				}
			}
			T1* tmp_arr;

			// Вот этот момомент! Со свапом!

			tmp_arr = Copy[i];
			Copy[i] = Copy[t];
			Copy[t] = tmp_arr;

			tmp_arr = INVERSE_MATRIX[i];
			INVERSE_MATRIX[i] = INVERSE_MATRIX[t];
			INVERSE_MATRIX[t] = tmp_arr;

			T1 t_inv = 1.0 / Copy[i][i];
			Copy[i][i] = 1.0;
			for (size_t j = i + 1; j < SIZE; j++)
			{
				Copy[i][j] *= t_inv;
			}
			for (size_t j = 0; j < SIZE; j++)
			{
				INVERSE_MATRIX[i][j] *= t_inv;
			}

			for (size_t j = 0; j < SIZE; j++)
			{
				if (i == j) continue;
				T1 el = Copy[i][j];
				Copy[j][i] = 0;
				for (size_t k = i + 1; k < SIZE; k++)
				{
					Copy[j][k] -= el * Copy[i][k];
				}
				for (size_t k = 0; k < SIZE; k++)
				{
					INVERSE_MATRIX[j][k] -= el * INVERSE_MATRIX[i][k];
				}
			}
		}
		Matrix<T1> original(SIZE, SIZE);
		for (size_t i = 0; i < SIZE; i++)
		{
			for (size_t j = 0; j < SIZE; j++)
			{
				original.m_ptr[i][j] = INVERSE_MATRIX[i][j];
			}
		}

		return original;
	}

	*/

	// Возведение матрицу в степень - ОК!

	template<typename T1>
	Matrix<T1> pow(const Matrix<T1>& rigth, size_t deg)
	{
		Matrix<T1> NEW_MATRIX = rigth;
		if (deg == 1)
		{
			return NEW_MATRIX;
		}
		for (size_t i = 1; i < deg; i++) NEW_MATRIX *= rigth;
		return NEW_MATRIX;
	}

	// Норма (Фробениуса и Евклидовое) - ОК!

	template<typename T1>
	double Matrix<T1>::norm()
	{
		double norm = 0;
		// Учесть случай вектора
		if (this->m_columns == 1)
		{
			for (size_t i = 0; i < this->m_rows; i++)
			{
				norm += (*this)(i, 0) * (*this)(i, 0);
				//norm += (this->m_ptr[i][0] * this->m_ptr[i][0]);
			}
			norm = sqrtf(norm);
			return norm;
		}
		for (size_t i = 0; i < this->m_rows; i++)
		{
			for (size_t j = 0; j < this->m_rows; j++)
			{
				norm += (*this)(i, j) * (*this)(i, j);
				//norm += (this->m_ptr[i][j] * this->m_ptr[i][j]);
			}
		}
		norm = sqrtf(norm);
		return norm;
	}



	// Скалярное произведение векторов

	template<typename T1>
	double multy_scalar(Matrix<T1>& left, Matrix<T1>& rigth)
	{
		double multy_scalar = 0;
		if ((left.m_columns == 1) && (rigth.m_columns == 1) && (left.m_rows == rigth.m_rows))
		{
			for (size_t i = 0; i < rigth.m_rows; i++)
			{
				multy_scalar += (left.m_ptr[i][0] * rigth.m_ptr[i][0]);
			}
			return multy_scalar;
		}
	}


	// Нахождение угла между векторами - ОК!
	template<typename T1>
	double angle(Matrix<T1>& left, Matrix<T1>& rigth)
	{
		if (!((left.rank() == 1) && (rigth.rank() == 1)))
		{
			throw LinAlgError("First or Second - isn't vector\n");
		}
		double angle = multy_scalar(left, rigth) / (left.norm() * rigth.norm());
		angle = acos(angle);
		return angle;
	}

	// Нормировка вектора - ОК!
	template<typename T1>
	Matrix<T1> unit(Matrix<T1>& vector)
	{
		if (vector.m_columns == 1)
		{
			double norm = vector.norm();
			Matrix<T1> UNIT_VECTOR = vector;
			for (size_t i = 0; i < UNIT_VECTOR.m_rows; i++)
			{
				UNIT_VECTOR.m_ptr[i][0] /= norm;
			}
			return UNIT_VECTOR;
		}
		else
		{
			throw LinAlgError("This object isn't a vector, therefore it haven't unit vector\n");
		}
	}

	// Векторное произведение

	template<typename T1>
	Matrix<T1> multy_vector(Matrix<T1>& left_vector, Matrix<T1>& rigth_vector)
	{
		Matrix<T1> result_vector(left_vector.m_rows, rigth_vector.m_columns);
		if ((left_vector.m_rows == rigth_vector.m_rows) && (left_vector.m_columns == 1) && (rigth_vector.m_columns == 1))
		{
			for (size_t i = 0; i < result_vector.m_rows; i++)
			{

				for (size_t j = 0; j < result_vector.m_rows; j++)
				{
					for (size_t k = 0; k < result_vector.m_rows; k++)
					{
						int sgn = (j + k) % 2 == 0 ? 1 : -1;
						result_vector.m_ptr[i][0] += (left_vector.m_ptr[j][0] * rigth_vector.m_ptr[k][0] * sgn * (j == i ? 1 : 0) * (k == i ? 1 : 0));
					}
				}
			}
			return result_vector;
		}
	}


	// Задание 4. решить систему линейных уравнений вида: A * x = f
	template<typename T1>
	Matrix<T1> solve(Matrix<T1> A, Matrix<T1> B)
	{
		// Создать вектор неизвестных
		Matrix<T1> X(A.rank(), 1);
		// Прямой ход
		
		T1 d, s;
		size_t size_A = A.rank();
		for (size_t i = 0; i < size_A; i++)
		{
			for (size_t j = i + 1; j < size_A; j++)
			{
				d = A(j, i) / A(i, i);
				
				for (size_t k = i; k < size_A; k++)
				{
					A(j, k) = A(j, k) - d * A(i, k);
				}
				B(j, 0) = B(j, 0) - d * B(i, 0);

			}
		}
		// обратный ход
		for (size_t i = size_A-1; i > 0; i--)
		{
			d = 0;
			for (size_t j = i + 1; j < size_A; j++)
			{
				s = A(i, j) * X(j, 0);
				d = d + s;
			}
			X(i,0) = (B(i, 0) - d) / A(i, i);
		}
		return X;
	}
}




/*
template<typename T=double>
class Matrix
{
private:
	T **m_ptr = nullptr; // указатель на динамический массив
	size_t m_rows; // кол-во строк
	size_t m_columns; // кол-во столбцов
public:
	// конструктор - ОК!
	Matrix(size_t rows, size_t columns = 1)
	{
		m_rows = rows;
		m_columns = columns;
		m_ptr = new T * [rows];
		for (size_t i = 0; i < rows; ++i) m_ptr[i] = new T[columns];
		for (size_t i = 0; i < rows; ++i)
		{
			for (size_t j = 0; j < columns; ++j) m_ptr[i][j] = 0;
		}
	}
	// конструктор копирования - ОК!
	Matrix(const Matrix& rigth)
	{
		m_rows = rigth.m_rows;
		m_columns = rigth.m_columns;
		m_ptr = new T * [m_rows];
		for (size_t i = 0; i < m_rows; ++i) m_ptr[i] = new T[m_columns];
		for (size_t i = 0; i < m_rows; ++i) for (size_t j = 0; j < m_columns; ++j) m_ptr[i][j] = rigth.m_ptr[i][j];
	}
	// Конструктор перемещения
	Matrix(Matrix&& move_m)
	{
		// Конструктор перемещения вызывается при вызове функции std::move(), если его нет, то вызывается конструктор копирования
		// адреса памяти передаются новому объекту
		m_ptr = move_m.m_ptr;
		m_rows = move_m.m_rows;
		m_columns = move_m.m_columns;
		// удаление информации из move_m
		move_m.m_ptr = nullptr;
		move_m.m_rows = 0;
		move_m.m_columns = 0;
	}
	// Перемещающие присваивание
	template<typename T1>
	Matrix<T1>& operator=(Matrix<T1>&& rigth)
	{
		// перенос данных
		m_rows = rigth.m_rows;
		m_columns = rigth.m_columns;
		m_ptr = rigth.m_ptr;
		// очищение правого объекта
		rigth.m_ptr = nullptr;
		rigth.m_rows = 0;
		rigth.m_columns = 0;
		return *this;

	}
	// Конструктор инициализации
	Matrix(const std::initializer_list<T> &list)
	{
		m_columns = 1;
		m_rows = list.size();
		m_ptr = new T*[m_rows];
		for (size_t i = 0; i < m_rows; i++)
		{
			m_ptr[i] = new T[m_columns];
		}

		size_t i = 0;
		for (auto& element : list)
		{
			m_ptr[i][0] = (T)element;
			++i;
		}
	}
	Matrix(const std::initializer_list<std::initializer_list<T>>& list)
	{
		m_rows = list.size();
		m_columns = list.begin()->size();
		m_ptr = new T * [m_rows];
		for (size_t i = 0; i < m_rows; i++)
		{
			m_ptr[i] = new T[m_columns];
		}

		size_t i = 0;
		size_t j = 0;
		for (auto& element : list)
		{
			for (auto& h : element)
			{
				m_ptr[i][j] = (T)h;
				++j;
			}
			++i;
			j = 0;
		}
	}

	// Функционал матрицы
	T det();
	size_t rank();
	template<typename T1>
	friend Matrix<T1> transpose(Matrix<T1>& rigth);
	double trace();
	template<typename T1>
	friend Matrix<T1> inv(const Matrix<T1>& rigth);
	template<typename T1>
	Matrix<T1> pow(const Matrix<T1>& rigth, size_t deg);
	double norm();
	template<typename T1>
	friend double multy_scalar(Matrix<T1>& left, Matrix<T1>& rigth);
	template<typename T1>
	friend double angle(Matrix<T1>& left, Matrix<T1>& rigth);
	template<typename T1>
	friend Matrix<T1> unit(Matrix<T1>& vector);
	template<typename T1>
	friend Matrix<T1> multy_vector(Matrix<T1>& left_vector, Matrix<T1>& rigth_vector);
	// Перегрузка операторов
	Matrix<T> operator + (const Matrix<T>& rigth);
	Matrix<T> operator+(T value);
	Matrix<T>& operator = (const Matrix<T> &right);
	Matrix<T> operator - (const Matrix<T>& rigth);
	Matrix<T> operator - (T value);
	Matrix<T> operator*(const Matrix<T>& rigth);
	Matrix<T>& operator*=(const Matrix<T>& rigth);
	Matrix<T>& operator+=(const Matrix<T>& rigth);
	Matrix<T>& operator-=(const Matrix<T>& rigth);
	Matrix<T> operator*(T value);
	template<typename T1>
	friend Matrix<T1> operator+(T1 value,Matrix<T1>& rigth);
	template<typename T1>
	friend Matrix<T1> operator-(T1 value, Matrix<T1>& rigth);
	template<typename T1>
	friend Matrix<T1> operator*(T1, Matrix<T1>& rigth);
	// Перегрузка оператора вывода
	template<typename T1>
	friend std::ostream& operator << (std::ostream& out, const Matrix<T1>& object);
	// Перегрузка оператора ()
	T& operator () (size_t _row, size_t _column) const
	{
		return m_ptr[_row][_column];
	}
	/*const T& operator () (size_t _row, size_t _column) const
	{
		return m_ptr[_row][_column];
	}
};
*/