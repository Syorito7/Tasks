#define _USE_MATH_DEFINES


#include <iostream>
#include <utility>
#include "Matrix.h"
//#include "operators_matrix.h"
#include <stdexcept>
//#include "New_function_matrix.h"
#include "Complex_value.h"
#include <cmath>



// Определитель матрицы - ОК!

int main()
{
	// Проверка всего и вся

	// 1) Объявление переменных и пространство имён linalg - ОК


	linalg::Matrix<> matr(3, 3);

	linalg::Matrix<> vec(3);

	linalg::Matrix<> TMP{ {1,2,3},{2,2,2},{1,1,1} };

	linalg::Matrix<> vector_TMP{ 1,2,3 };

	// 2) Расширить функционал матрицы


	// ОК
	double d = matr.det();
	std::cout << "Determinat = " << d << '\n';
	std::cout << "Determinat = " << TMP.det() << '\n';

	// ОК
	int r = matr.rank();
	std::cout << "Rank = " << r << '\n';
	std::cout << "Rank = " << TMP.rank() << '\n';

	// ОК
	double n = matr.norm();
	std::cout << "Norm = " << n << '\n';
	std::cout << "Norm = " << TMP.norm() << '\n';

	// ОК
	double t = matr.trace();
	std::cout << "Trace = " << t << '\n';
	std::cout << "Trace = " << TMP.trace() << '\n';

	// ОК
	linalg::Matrix<> m_tr = linalg::transpose(matr);
	linalg::Matrix<> m_TMP = linalg::transpose(TMP);
	std::cout << "m_tr" << '\n' << m_tr;
	std::cout << "m_TMP" << "\n" << m_TMP;

	// Обратная матрица - надо проверить

	// Обратная матрица - ОК

	linalg::Matrix<> A_for_inverse{ {2,5,7},{6,3,4},{5,-2,-3} };

	std::cout << "A for inverse :\n";
	std::cout << A_for_inverse;
	std::cout << "A - inverse :\n";
	std::cout << linalg::inv(A_for_inverse);

	// возведение в степень (умножение матрицы на себя) - ОК
	linalg::Matrix<> m_p = linalg::pow(matr, 4);
	linalg::Matrix<> pow_TMP = linalg::pow(TMP, 4);
	std::cout << "m_p" << '\n' << m_p;
	std::cout << "pow_TMP" << '\n' << pow_TMP;

	// 3) Расширить функционал по работе с матрицами, представляющими из себя вектора

	std::cout << "Next functions for vectors" << '\n';

	// ОК
	double e = vec.norm();
	double e_TMP = vector_TMP.norm();
	std::cout << "Norm = " << e << '\n';
	std::cout << "Norm = " << e_TMP << '\n';

	// Рассчитывает угол между векторами, выдаёт что-то странное. Надо проверить
	double a = linalg::angle(vec, vec);
	double a_TMP = linalg::angle(vec, vector_TMP);
	std::cout << "Angle = " << a << '\n';
	std::cout << "Angle = " << a_TMP << '\n';

	// ОК
	double s = linalg::multy_scalar(vec, vec);
	double s_TMP = linalg::multy_scalar(vector_TMP, vector_TMP);
	std::cout << "Multy_scalar = " << s << '\n';
	std::cout << "Multy_scalar = " << s_TMP << '\n';

	// ОК
	linalg::Matrix<> m_v = linalg::multy_vector(vec, vec);
	linalg::Matrix<> TMP_m_vect = linalg::multy_vector(vector_TMP, vector_TMP);
	std::cout << "Multy_vector = " << '\n' << m_v;
	std::cout << "Multy_vector = " << '\n' << TMP_m_vect;

	// ОK, только Nan - если вектор (0,0,0)
	linalg::Matrix<> m_u = linalg::unit(vec);
	linalg::Matrix<> TMP_vectorik = linalg::unit(vector_TMP);
	std::cout << "Unit_vector = " << '\n' << m_u;
	std::cout << "Unit_vector = " << '\n' << TMP_vectorik;

	// 4) Расширить функционал по работе с матрицами, чтобы решать системы линейных уравнений вида
	// A * X = F, Пример: Matrix<> vec_x = solve(matr_A,vec_f); - ОК

	linalg::Matrix<> A{ {7,2,3},{5,-3,2},{10,-11,5} };
	std::cout << "Matrix A :\n";
	std::cout << A;
	linalg::Matrix<> B{ 15,15,36 };
	std::cout << "Vector B :\n";
	std::cout << B;
	linalg::Matrix<> X = linalg::solve(A, B);
	std::cout << "Vector X :\n";
	std::cout << X;

	// Этот пункт надо сделать!

	// 5) Создать класс ошибок: LinAlgError - для исключений


	linalg::Matrix<> E{ {1,2,3}, {4,2,5} };
	std::cout << "Matrix E :\n" << E << "Determinat E\n" << E.det();

	// 6) Разработать шаблонный класс комплексных чисел Complex<>, по умолчанию - double - OK

	// Всё ОК

	/*

	Complex<int> val_i;
	Complex<short> val_s(1);
	Complex<> val(1, -2);
	//
	double r_new = val.real();
	double i = val.imag();
	std::cout << "Real of val = " << r_new << '\n';
	std::cout << "Imag of val = " << i << '\n';
	//
	val.real(-2);
	val.imag(1.1);
	std::cout << "New real of val = " << val.real() << '\n';
	std::cout << "New imag of val = " << val.imag() << '\n';
	// Операции с обычным числом
	val += 2;
	std::cout << "val +=2 : " << val.real() << ' ' << val.imag() << '\n';
	val -= 5;
	std::cout << "val -=5 : " << val.real() << ' ' << val.imag() << '\n';
	val *= -3;
	std::cout << "val *=-3 : " << val.real() << ' ' << val.imag() << '\n';
	// Операции с комлексным числом
	Complex<> val_new(5, -10.1);
	val = val_new;
	std::cout << "val_new :" << val_new.real() << ' ' << val_new.imag() << '\n';
	std::cout << "val = val_new" << '\n';
	std::cout << "val :" << val.real() << ' ' << val.imag() << '\n';
	// ОК
	val += Complex<int>{5, 7};
	std::cout << "val += Complex<int>{5, 7} : " << val.real() << " " << val.imag() << '\n';
	val -= Complex<int>{3, 4};
	std::cout << "val -= Complex<int>{3, 4} : " << val.real() << ' ' << val.imag() << '\n';
	val *= Complex<int>{-2, 1};
	std::cout << "val *= Complex<int>{-2, 1} : " << val.real() << ' ' << val.imag() << '\n';

	// 7) Расширить функционал разработанного класса Complex<>: - ОК

	// Надо переделать перегрузку (обычное число "оператор" комплексное)


	std::cout << "val+1 : " << (val + 1).real() << ' ' << (val + 1).imag() << '\n';
	std::cout << "1+val : " << (1 + val).real() << ' ' << (1 + val).imag() << '\n';
	std::cout << "val*1 : " << (val * 1).real() << ' ' << (val * 1).imag() << '\n';
	std::cout << "1*val : " << (1 * val).real() << ' ' << (1 * val).imag() << '\n';
	std::cout << "val-1 : " << (val - 1).real() << ' ' << (val - 1).imag() << '\n';
	std::cout << "1-val : " << (1 - val).real() << ' ' << (1 - val).imag() << '\n';

	// Работа между комплексными числами - ОК

	Complex<> value_1(-2, 4);
	Complex<> value_2(5, -3.5);
	std::cout << "value_1 :" << value_1.real() << ' ' << value_1.imag() << '\n';
	std::cout << "value_2 :" << value_2.real() << ' ' << value_2.imag() << '\n';
	std::cout << "value_1 * value_2 : " << (value_1 * value_2).real() << ' ' << (value_1 * value_2).imag() << '\n';

	std::cout << "value_1 + value_2 :" << (value_1 + value_2).real() << ' ' << (value_1 + value_2).imag() << '\n';
	std::cout << "value_1 - value_2 :" << (value_1 - value_2).real() << ' ' << (value_1 - value_2).imag() << '\n';

	// Операторы ввода в поток и вывод из него
	std::cout << Complex<>(1.1);

	// Ввод - ОК
	Complex<> C_in_value;
	//std::cin >> C_in_value;
	//std::cout << C_in_value;


	// 8) Перегрузить у матрицы оператор сравнения (поэлементно) и используя его проверить следующие свойства
	// Используя комплексные элементы: (A_in_T)inverse ?= (A_inverse)transpose

	// Обычные числа - ОК
	linalg::Matrix<> M{ {1,1,1},{2,3,-1},{5,3,-2},{10,0.5,0} };
	std::cout << "Matrix M :\n";
	std::cout << M;
	linalg::Matrix<> N{ {1,1,1},{2,3,-1},{5,3,-2},{10,0.5,0} };
	std::cout << "Matrix N :\n";
	std::cout << N;
	if (M == N)
	{
		std::cout << "Yes : M=N\n";
	}
	else
	{
		std::cout << "No : M!=N\n";
	}
	linalg::Matrix<> K{ {10,0.5,0},{2,3,-1},{5,3,-2},{1,1,1} };
	std::cout << "Matrix K :\n";
	std::cout << K;
	if (M == K)
	{
		std::cout << "Yes : M=K\n";
	}
	else
	{
		std::cout << "No : M!=K\n";
	}
	std::cout << TMP;
	std::cout << "(TMP.transpose).inverse ?= (TMP.inverse).transpose\n";
	linalg::Matrix<> K1 = linalg::transpose(TMP);
	linalg::Matrix<> K2 = linalg::inv(TMP);
	// ОК, работает с квадратными матрицами, так как обратная существует только у такой
	if (linalg::inv(K1) == linalg::transpose(K2))
	{
		std::cout << "Yes\n";
	}
	else
	{
		std::cout << "NO\n";
	}
	// Проверим свойство (A1 * A2).inverse ?= A2.inverse * A1.inverse.
	// Они должны быть квадратными, иначе inverse не существует

	linalg::Matrix<> L1{ {1,2,3,4}, {3,5,-1,2}, {5,5,5,0},{-1,1,0,2} };
	std::cout << "L1 Matrix :\n" << L1;
	linalg::Matrix<> L2{ {0,0,2,3},{-12,6,13,5},{-1,-1,2,3},{9,3,6,-2} };
	std::cout << "L2 Matrix :\n" << L2;
	linalg::Matrix<> L_Left = linalg::inv(L1 * L2);
	linalg::Matrix<> L_Rigth = linalg::inv(L2) * linalg::inv(L1);
	std::cout << "(L1*L2).inverse ?= L2.inverse * L1.inverse\n";
	/*
	// Выдаёт неправильный ответ
	if (L_Left == L_Rigth)
	{
		std::cout << "Yes\n";
	}
	else
	{
		std::cout << "No\n";
	}

	*/

	// Старые тесты

	//std::cout << asin(sqrt(2)/2)* 180 / M_PI;
	
	

	/*

	Matrix<> m1 = { {-4,-3,-2},{-1,0,1},{2,3,4} };
	//std::cout << m1.norm();




	Matrix<> vec = {1,2,3};
	Matrix<> vec_2 = { 1,1,1 };
	std::cout << vec;

	Complex<> value;
	std::cin >> value;
	std::cout << value;
	*/

	// Не работает!
	//Matrix<> vec_3 = multy_vector(vec, vec_2);
	//std::cout << vec_3;

	//std::cout << vec.norm();

	//std::cout << '\n' << multy_scalar(vec, vec_2) << '\n';
	//std::cout << angle(vec, vec_2);
	//std::cout << unit(vec);




	/*Complex<int> val_i;
	Complex<short> val_s(1);
	Complex<> val(1, -2);
	double r = val.real();
	double i = val.imag();

	std::cout << val << '\n';
	Complex<int>val_2(-1, -1);
	std::cout << val_2 << '\n';
	Complex<> val_3 = (val * val_2);
	std::cout << val_3;*/
	// Нужно реализовать для разных типов Complex


	/*
	std::cout << r << ' ' << i << '\n';
	val.real(2);
	val.imag(1.1);
	r = val.real();
	i = val.imag();
	std::cout << r << ' ' << i << '\n';

	val += -2;
	r = val.real();
	i = val.imag();
	std::cout << r << ' ' << i << '\n';
	Complex<> val_2(1, 3);
	val += val_2;

	r = val.real();
	i = val.imag();
	std::cout << r << ' ' << i << '\n';

	val *= val_2;
	std::cout << val.real() << ' ' << val.imag();


	*/
	//Matrix<double> m1 = { {1,1,1},{3,2,2},{3,3,1} };
	//std::cout << m1;
	/*std::cout << m1.rank();
	std::cout << '\n' << m1.trace();
	Matrix<double> m2 = inv(m1);
	std::cout << m2;*/
	//std::cout << pow(m1, 0);
	//int a = m1.det();
	//std::cout << a;
	/*int b = m1.rank();
	std::cout << '\n' << b << '\n';
	std::cout << m1;*/
	/*
	// При заполнении элементов использовать дефолтные конструкторы: - ОК!
	Matrix<> m1(4);
	Matrix<> m2(4, 6);
	std::cout << m1;
	// Конструктор копирования: - ОК!
	Matrix<double> m3(m1);
	// Конструктор перемещения
	Matrix<>m4(std::move(m2));
	Matrix<int>m5 = { 1,2,3,4 };
	Matrix<int>m6 = { {1, 2 , 3}, {4, 5 , 6} };
	std::cout << m6;
	Matrix<int> m7 = { {1, 2, 3, 4, 5, 6} }; // 1 строка и 6 столбцов
	std::cout << m7;
	//Matrix<int> m8 = { {1},{2},{3},{4},{5},{6} }; // 6 строк и 1 столбец
	m1 = m2; // копирующее присваивание
	std::cout << m1;
	m1 = Matrix<double>{ 1,2,3,4,5,6 }; // Перемещающие присваивание
	std::cout << m1;
	Matrix<int> m = { {1,2,3},{4,5,6} };
	int val = m(0, 0); // перегрузка оператора () - вызов функции
	m(0, 2) = 7;
	std::cout << m;

	Matrix<> D1(1, 3);
	Matrix<> D2(1, 1);
	Matrix<> D3 = D1 * D2;
	//std::cout << "D3!!!\n" << D3;

	const Matrix<int> c_m = { {1,2,3},{4,5,6} };
	//int d = c_m(0, 2); 
	//c_m(0, 2) = 1; - для const
	Matrix<int> A = { {1,1,1}, {3,3,3} };
	Matrix<int> B = { {3,3,3}, {1,1,1} };
	// Проверка на операторы + и -
	std::cout << (A + B);
	int number = 4;
	std::cout << (A + number);
	std::cout << (number + A);
	std::cout << (A - B);
	std::cout << (A - number);
	// Проверка на операторы *, *=
	Matrix<int> A_1 = { {3,5,7},{1,1,1},{0,2,5} };
	std::cout << "A_1\n" << A_1;
	Matrix<int> B_1 = { {3,2,1},{1,1,1},{0,0,0} };
	std::cout << "B_1\n" << B_1;
	std::cout << (A_1 * B_1);
	A_1 *= B_1;
	std::cout << A_1;
	B_1 += A_1;
	std::cout << B_1;
	B_1 -= A_1;
	std::cout << B_1;
	std::cout << (B_1 * 5);
	Matrix<int> C = { {25,124,2},{-1,-20,33},{1550,30,111} };
	std::cout << "KEK\n" << C;
	std::cout << (5 * B_1);
	// Математические операторы перегружены - ОК!

	Matrix<double> m_d = { {1,2},{3,4},{5,6} };
	//Matrix<int> m_i = { {(1.1,2.2,3.3},{4.4,5.5,6.6} };
	*/
}
