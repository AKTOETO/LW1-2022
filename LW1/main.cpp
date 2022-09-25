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

#define _USE_MATH_DEFINES	// для PI

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <chrono>
#include "gui/GraphsDrawer.h"	// для отрисовки графиков


using namespace std;


/****************************************************************
*					   К О Н С Т А Н Т Ы						*
****************************************************************/

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

/****************************************************************
*              П Р О Т О Т И П Ы   Ф У Н К Ц И Й                *
****************************************************************/

// генерация рандомного вещественного числа
// в интервале [min, max]
double rand_double(double min, double max);

// упорядочная ф-ия по возрастанию
template<typename T>
void f1(T* arr, int size, double max, double step);

// упорядочная ф-ия по убыванию
template<typename T>
void f2(T* arr, int size, double max, double step);

// случайная ф-ия
template<typename T>
void f3(T* arr, int size, double max, double step);

// синусоидальная функция
template<typename T>
void f4(T* arr, int size, double max, double step);

// пилообразная функция
template<typename T>
void f5(T* arr, int size, double max, double step);

// ступенчатая функция
template<typename T>
void f6(T* arr, int size, double max, double step);

// печать массива в поток
template<typename T>
void print_arr(T* arr, int size, double step, ostream& stream);

// ввод и проверка значений
template<typename T>
T input_and_check(T min, T max,
	const char* welcome_str, const char* err_str);

// создание массивов и вывод их в файлы
template<typename ARRAY_TYPE, typename TYPE_OF_TIME = chrono::nanoseconds>
void creating_arrays(int size, double max, double x_step,
	// (arr,size, x_step, func_num,  elapsed_ms)
	void (*stage) (
		ARRAY_TYPE* arr,
		int size,
		double x_step,
		int func_num,
		TYPE_OF_TIME elapsed_time
		)
);

// функция обработки массивов для первого этапа работы
template<typename ARRAY_TYPE, typename TYPE_OF_TIME = chrono::nanoseconds>
void first_stage(
	ARRAY_TYPE* arr,
	int size,
	double x_step,
	int func_num,
	TYPE_OF_TIME elapsed_time
);

// функция обработки массивов для второго этапа работы
template<typename ARRAY_TYPE, typename TYPE_OF_TIME = chrono::microseconds>
void second_stage(
	ARRAY_TYPE* arr,
	int size,
	double x_step,
	int func_num,
	TYPE_OF_TIME elapsed_time
);

// решение первой задачи
// массивы размером от 150 до 200
// отрисовка графиков функций
// есть вывод в файл данных массива
void first_task();

// вторая задача
// массивы размером 5*10^5,10*10^5,50*10^5
// отрисовки нет
// вывода в файл нет
// в консоли видно
// время формирования последовательностей
void second_task();


/****************************************************************
*                Г Л А В Н А Я   Ф У Н К Ц И Я                  *
****************************************************************/

int main()
{
	// установка русского языка в консоли
	setlocale(LC_ALL, "ru");

	// инициализация генератора случайных чисел
	srand(time(NULL));

	// выполнение первого этапа
	first_task();

	// выполнение второго этапа
	second_task();

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
void f1(T* arr, int size, double max, double step)
{
	//k, b - коэффициенты прямой
	T k = max / (step * size);
	T b = 0;

	double x = 0.0; // координата x
	for (int i = 0; i < size; i++, x += step)
	{
		arr[i] = k * x + b;
	}
}

// упорядочная ф-ия по убыванию
template<typename T>
void f2(T* arr, int size, double max, double step)
{
	//k, b - коэффициенты прямой
	T k = max / (step * size);
	T b = 0;

	double x = 0.0; // координата x
	for (int i = 0; i < size; i++, x += step)
	{
		arr[i] = -k * x + b;
	}
}

// случайная ф-ия
template<typename T>
void f3(T* arr, int size, double max, double step)
{
	//i изменяется в интервале [-25,25]
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand_double(-max, max);
	}
}

// синусоидальная функция
template<typename T>
void f4(T* arr, int size, double max, double step)
{
	T x_scale = 1; // масштабирование по x
	T x_shift = 1; // сдвиг по х
	T y_scale = max; // мастабирование по y
	double x = 0.0; // координата x

	for (int i = 0; i < size; i++, x += step)
	{
		arr[i] = sin(x_scale * x + x_shift) * y_scale;
	}
}

// пилообразная функция
template<typename T>
void f5(T* arr, int size, double max, double step)
{
	T x_scale = 0.5;	// масштабирование по x
	T x_shift = 0;	// сдвиг по х
	T y_scale = max;	// мастабирование по y
	double x = 0.0;	// координата x

	for (int i = 0; i < size; i++, x += step)
	{
		arr[i] = asin(sin(x * x_scale + x_shift)) * y_scale / M_PI_2;
	}
}

// ступенчатая функция
template<typename T>
void f6(T* arr, int size, double max, double step)
{
	int count_of_step = 5;						// количество ступеней
	double step_height = max / count_of_step;	// высота одной ступени
	int step_length = ceil(size * step);		// длина одной ступени
	double rand_value = max / 20.0;				// значение для создания шума
	double x = 0.0;								// координата x

	// координата x увеличивается на step_height (высоту шага),
	// если прошло ровно step_length значений
	for (int i = 0; i < size; i++, x += ((i % step_length == 0) ? step_height : 0.0))
	{
		// координата y + шум, зависящий от высоты шага
		arr[i] = x + rand_double(-rand_value, rand_value);
	}
}

// печать массива в поток
template<typename T>
void print_arr(T* arr, int size, double step, ostream& stream)
{
	// вывод шага по x в файл
	stream << step << endl;

	// вывод координат массива
	for (int i = 0; i < size; i++)
	{
		stream << fixed << setprecision(6)
			<< arr[i] << '\n';
	}
}

// первая часть
void first_task()
{
	cout << "========= ПЕРВЫЙ ЭТАП =========\n";

	// тип массива (int или double), вводится через консоль
	int type = input_and_check(1, 2,
		"\nВыберите тип данных массива [1,2]:\n\t1.int\n\t2.double\n",
		"Должна быть введена 1 или 2\n");

	// размер массива, вводится через консоль
	int size = input_and_check(150, 200,
		"\nВведите размер массива [150,200]:\n",
		"Должно быть введено значение в интервале [150,200]\n");

	double max_value = input_and_check(10, 1000,
		"\nВведите максимальное значение по оси y [10,1000]:\n",
		"Должно быть введено значение в интервале [10,1000]\n"
	);

	double x_step = input_and_check(0.01, 10.0,
		"\nВведите величину шага по x [0.01, 10]:\n",
		"Должно быть введено значение в интервале [0.01, 10] через точку, а не запятую\n"
	);

	// выбор типа массива
	switch (type)
	{
		// если был выбран int
	case 1:
		creating_arrays<int>(size, max_value, x_step, first_stage);
		break;

		// если был выбран double
	case 2:
		creating_arrays<double>(size, max_value, x_step, first_stage);
		break;
	}

	// отрисовка графиков
	GraphsDrawer gd;
	gd.run();

	cout << "== КОНЕЦ ПЕРВОГО ЭТАПА ==\n\n";
}

// втроая часть
void second_task()
{
	cout << "========= ВТОРОЙ ЭТАП =========\n";

	// тип массива (int или double), вводится через консоль
	int type = input_and_check(1, 2,
		"\nВыберите тип данных массива [1,2]:\n\t1.int\n\t2.double\n",
		"Должна быть введена 1 или 2\n");

	double max_value = input_and_check(10, 1000,
		"\nВведите максимальное значение по оси y [10,1000]:\n",
		"Должно быть введено значение в интервале [10,1000]\n"
	);

	double x_step = input_and_check(0.01, 10.0,
		"\nВведите величину шага по x [0.01, 10]:\n",
		"Должно быть введено значение в интервале [0.01, 10] через точку, а не запятую\n"
	);
	cout << "Длина последовательности |f1 мкС |f2 мкС |f3 мкС |f4 мкС |f5 мкС |f6 мкС |\n";
	for (int size = 500000; size <= 5000000; size += 500000)
	{
		cout << fixed << setfill(' ') << setw(25) << size << "|";
		switch (type)
		{
			// если был выбран int
		case 1:
			creating_arrays<int, chrono::microseconds>(
				size, max_value, x_step,
				second_stage);
			break;

			// если был выбран double
		case 2:
			creating_arrays<double, chrono::microseconds>(
				size, max_value, x_step,
				second_stage);
			break;
		}
		cout << endl;
	}
	cout << "== КОНЕЦ ВТОРОГО ЭТАПА ==\n";
}

// ввод и проверка значений
template<typename T>
T input_and_check(T min, T max,
	const char* welcome_str, const char* err_str)
{
	// размер массива
	T num;
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
template<typename ARRAY_TYPE, typename TYPE_OF_TIME = chrono::nanoseconds>
void creating_arrays(int size, double max, double x_step,
	void (*stage) (
		ARRAY_TYPE* arr,
		int size,
		double x_step,
		int func_num,
		TYPE_OF_TIME elapsed_time
		)
)
{
	// массив
	ARRAY_TYPE* arr = new ARRAY_TYPE[size];

	// массив указателей на функции
	void (*funcs[])(
		ARRAY_TYPE * arr,		// массив
		int size,		// размер массива
		double max_y,	// максимальное значение по y
		double x_step	// шаг по x
		) = { f1,f2,f3,f4,f5,f6 };

	// запуск всех функций
	for (int i = 0; i < 6; i++)
	{
		// начало отсчета времени
		auto begin = std::chrono::steady_clock::now();

		// вызов формирующей функции
		funcs[i](arr, size, max, x_step);

		// конец отсчета времени
		auto end = std::chrono::steady_clock::now();

		// вывод в консоль времени работы программы
		auto elapsed_ms = std::chrono::duration_cast<TYPE_OF_TIME>(end - begin);

		// вызов функции 
		stage(arr, size, x_step, i, elapsed_ms);
	}

	// очистка памяти, занимаемой массивом
	delete[] arr;
}

// функция обработки массивов для первого этапа работы
template<typename ARRAY_TYPE, typename TYPE_OF_TIME = chrono::nanoseconds>
void first_stage(
	ARRAY_TYPE* arr,
	int size,
	double x_step,
	int func_num,
	TYPE_OF_TIME elapsed_time
)
{
	// печать времени формирования последовательности
	cout << "\tВремя выполнения " << func_num + 1 << " функции = " <<
		fixed << setw(5) << elapsed_time.count() << " (нс)\n";

	// создание определенного файлового потока
	ofstream out(name_of_file[func_num]);

	// печать массива в файл
	print_arr(arr, size, x_step, out);

	// закрытие файлового потока
	out.close();

}

// функция обработки массивов для второго этапа работы
template<typename ARRAY_TYPE, typename TYPE_OF_TIME = chrono::microseconds>
void second_stage(
	ARRAY_TYPE* arr,
	int size,
	double x_step,
	int func_num,
	TYPE_OF_TIME elapsed_time
)
{
	cout << fixed << setfill(' ') << setw(6) << elapsed_time.count() << " |";
}
/**************** End Of main.cpp File ***************/