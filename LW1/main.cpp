/***********************************************************************\
*                    кафедра № 304 2 курс 3 семестр информатика			*
*-----------------------------------------------------------------------*
*	Project type : solution												*
*	Project name : LW1													*
*	File name    : main.cpp												*
*	Language     : c/c++												*
*	Programmers  : Плоцкий Б.А. Раужев Ю. М.							*
*	Created      :  12/09/22											*
*	Last revision:  19/09/22											*
*	Comment(s)   : 														*
*																		*
*	1 этап работы														*
*	Разработать функции, формирующие последовательности чисел:			*
*	- упорядоченные по возрастанию,										*
*	- упорядоченные по убыванию,										*
*	- случайную последовательность,										*
*	- частично упорядоченные: «пилообразные», «синусоидальные»,			*
*		«ступенчатые».													*
*																		*
*	> для целых чисел и чисел с плавающей запятой						*
*	> (должно быть два комплекта функций и соответственно результатов).	*
*																		*
*	2 этап работы														*
*	Оценить длительность формирования последовательностей всех типов	*
*	для различных значений размеров последовательностей,				*
*	и на основе	полученных значений построить графики зависимостей		*
*	длительностей формирования массивов от их размера (лучше в виде		*
*	столбчатых диаграмм, можно в Microsoft Excel).						*
*																		*
*	Составить отчет, в котором привести структурные схемы алгоритмов	*
*	главной функции и какой-то одной из функций (например,				*
*	реализующей частично упорядоченную последовательность),				*
*	текст программы, результаты по временным интервалам для различных	*
*	размерностей массивов, графики зависимостей (времени от				*
*	размерностей) и выводы по полученным результатам. 					*
*																		*
\***********************************************************************/


#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <chrono>
#include "gui/GraphsDrawer.h"	// для отрисовки графиков

using namespace std;

/****************************************************************
*              П Р О Т О Т И П Ы   Ф У Н К Ц И Й                *
****************************************************************/

// генерация рандомного вещественного числа
// в интервале [min, max]
double rand_double(double min, double max);

// упорядочная ф-ия по возрастанию
template<typename T>
void f1(T* arr, int size);

// упорядочная ф-ия по убыванию
template<typename T>
void f2(T* arr, int size);

// случайная ф-ия
template<typename T>
void f3(T* arr, int size);

// синусоидальная функция
template<typename T>
void f4(T* arr, int size);

// пилообразная функция
template<typename T>
void f5(T* arr, int size);

// ступенчатая функция
template<typename T>
void f6(T* arr, int size);

// печать массива в поток
template<typename T>
void print_arr(T* arr, int size, ostream& stream);

// ввод и проверка размера массива
int size_of_arr();

// ввод и проверка значений
int input_and_check(int min, int max,
	const char* welcome_str, const char* err_str);

// создание массивов и вывод их в файлы
template<typename T>
void creating_arrays(int size);


/****************************************************************
*                Г Л А В Н А Я   Ф У Н К Ц И Я                  *
****************************************************************/

int main()
{
	// установка русского языка в консоли
	setlocale(LC_ALL, "ru");

	// инициализация генератора случайных чисел
	srand(time(NULL));

	// тип массива (int или double), вводится через консоль
	int type = input_and_check(1, 2,
		"Выберите тип данных массива [1,2]:\n\t1.int\n\t2.double\n",
		"Должна быть введена 1 или 2\n");

	// размер массива, вводится через консоль
	int size = input_and_check(0, 1000,
		"Введите размер массива [0,1000]:\n",
		"Должна быть введено значение в интервале [0,1000]\n");

	// выбор типа массива
	switch (type)
	{
		// если был выбран int
	case 1:
		creating_arrays<int>(size);
		break;

		// если был выбран double
	case 2:
		creating_arrays<double>(size);
		break;
	}

	// отрисовка графиков
	GraphsDrawer gd;
	gd.draw();

	return 0;
}

/****************************************************************
*             Р Е А Л И З А Ц И Я   Ф У Н К Ц И Й               *
****************************************************************/

// генерация рандомного вещественного числа
// в интервале [min, max]
double rand_double(double min, double max)
{
	double f = (double)rand() / RAND_MAX;
	return min + f * (max - min);
}

// упорядочная ф-ия по возрастанию
template<typename T>
void f1(T* arr, int size)
{
	//k, b - коэффициенты прямой
	T k = 0.5;
	T b = 0;

	double x = 0.0; // координата x
	for (int i = 0; i < size; i++, x += 0.2)
	{
		arr[i] = k * x + b;
	}
}

// упорядочная ф-ия по убыванию
template<typename T>
void f2(T* arr, int size)
{
	//k, b - коэффициенты прямой
	T k = 0.5;
	T b = 0;

	double x = 0.0; // координата x
	for (int i = 0; i < size; i++, x += 0.2)
	{
		arr[i] = -k * x + b;
	}
}

// случайная ф-ия
template<typename T>
void f3(T* arr, int size)
{
	//i изменяется в интервале [-25,25]
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand_double(-5, 5);
	}
}

// синусоидальная функция
template<typename T>
void f4(T* arr, int size)
{
	T x_scale = 1; // масштабирование по x
	T x_shift = 1; // сдвиг по х
	T y_scale = 5; // мастабирование по y
	double x = 0.0; // координата x

	for (int i = 0; i < size; i++, x += 0.2)
	{
		arr[i] = sin(x_scale * x + x_shift) * y_scale;
	}
}

// пилообразная функция
template<typename T>
void f5(T* arr, int size)
{
	T x_scale = 1;	// масштабирование по x
	T x_shift = 1;	// сдвиг по х
	T y_scale = 1;	// мастабирование по y
	double x = 0.0;	// координата x

	for (int i = 0; i < size; i++, x += 0.2)
	{
		arr[i] = asin(sin(x * x_scale + x_shift)) * y_scale;
	}
}

// ступенчатая функция
template<typename T>
void f6(T* arr, int size)
{
	int step_length = 20;						// длина одной ступени
	double step_height = step_length / 10.0;	// высота одной ступени
	double rand_value = step_height / 10.0;		// значение для создания шума
	double x = 0.0;								// координата x

	// координата x увеличивается на step_height (высоту шага),
	// если прошло ровно step_length значений
	for (int i = 0; i < size; i++, x += ((i % step_length == 0) ? step_height : 0.0))
	{
		// координата y + шум, зависящий от высоты шага
		arr[i] = x + rand_double(-rand_value, rand_value);
		//cout << "i: " << i << " x: " << x << endl;
	}
}

// печать массива в поток
template<typename T>
void print_arr(T* arr, int size, ostream& stream)
{
	for (int i = 0; i < size; i++)
	{
		stream << fixed << setprecision(6)
			<< arr[i] << '\n';
	}
}

// проверка и ввод размера массива
int size_of_arr()
{
	// размер массива
	int size;
	cout << "Введите размер массива [0,1000]:\n";
	cin >> size;

	// если было введено не то
	if (size > 1000 || size < 0) {
		cout << "Должна быть введено значение в интервале [0,1000]\n";
		// если была введена не цифра
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		system("cls");
		size = size_of_arr();
	}
	return size;
}

// ввод и проверка значений
int input_and_check(int min, int max,
	const char* welcome_str, const char* err_str)
{
	// размер массива
	int num;
	cout << welcome_str;
	cin >> num;

	// если было введено не то
	if (num > max || num < min) {
		// если была введена не цифра
		if (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		system("cls");
		cout << err_str;
		num = input_and_check(min, max, welcome_str, err_str);
	}
	return num;
}

// создание массивов и вывод их в файлы
template<typename T>
void creating_arrays(int size)
{
	// массивы
	T* arr = new T[size];

	// массив указателей на функции
	void (*funcs[])(T*, int) = { f1,f2,f3,f4,f5,f6 };

	// имена файлов
	const char name_of_file[6][13] =
	{
		"files/f1.txt",
		"files/f2.txt",
		"files/f3.txt",
		"files/f4.txt",
		"files/f5.txt",
		"files/f6.txt"
	};

	// запуск всех функций
	for (int i = 0; i < 6; i++)
	{
		// файл вывода данных
		ofstream out(name_of_file[i]);

		// начало отсчета времени
		auto begin = std::chrono::steady_clock::now();

		// вызов формирующей функции
		funcs[i](arr, size);;

		// конец отсчета времени
		auto end = std::chrono::steady_clock::now();

		// вывод в консоль времени работы программы
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		cout << "\tВремя выполнения " << i + 1 << " функции = " <<
			fixed << setw(5) << elapsed_ms.count() << " (нс)\n";

		// печать массива в файл
		print_arr(arr, size, out);

		// закрытие файлового потока
		out.close();
	}
}
/**************** End Of main.cpp File ***************/