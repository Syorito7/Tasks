#pragma once
/*

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
	// нужно транспонировать, если столбцов больше, чем строк!
	// ...
	Matrix<T1> tmp = (*this);
	if (this->m_columns > this->m_rows)
	{
		// перемещающие присваивание, чтобы меньше времени и памяти тратилось
		tmp = std::move(transpose(*this));
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


// Не ОК! Совсем!

template<typename T1>
Matrix<T1> inv(const Matrix<T1>& rigth)
{
	size_t SIZE = rigth.m_columns;

	T1** INVERSE_MATRIX;
	INVERSE_MATRIX = new T1*[SIZE];
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
			norm += (this->m_ptr[i][0] * this->m_ptr[i][0]);
		}
		norm = sqrtf(norm);
		return norm;
	}
	for (size_t i = 0; i < this->m_rows; i++)
	{
		for (size_t j = 0; j < this->m_rows; j++)
		{
			norm += (this->m_ptr[i][j] * this->m_ptr[i][j]);
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

*/