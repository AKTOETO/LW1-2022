#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <chrono>
#include "gui/GraphsDrawer.h"	// для графиков
						// (в финальной версии лабы
						// можно будет удалить)
using namespace std;

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
	//k, b - коэффициент
	T k = 1;
	T b = 0;

	double j = 0.0; // координата y
	for (int i = 0; i < size; i++, j += 0.2)
	{
		arr[i] = k * j + b;
	}
}

// упорядочная ф-ия по убыванию
template<typename T>
void f2(T* arr, int size)
{
	//k, b - коэффициенты прямой
	T k = 1;
	T b = 0;

	double j = 0.0; // координата y
	for (int i = 0; i < size; i++, j += 0.2)
	{
		arr[i] = -k * j + b;
	}
}

// случайная ф-ия
template<typename T>
void f3(T* arr, int size)
{
	//i изменяется в интервале [-25,25]
	double j = 0.0;
	for (int i = 0; i < size; i++, j += 0.2)
	{
		arr[i] = rand_double(-25, 25);
	}
}

// синусоидальная функция
template<typename T>
void f4(T* arr, int size)
{
	T a = 1; // масштабирование по x
	T c = 1; // сдвиг по х
	T b = 5; // мастабирование по y

	double j = 0.0; // координата y
	for (int i = 0; i < size; i++, j += 0.2)
	{
		arr[i] = sin(a * j + c) * b;
	}
}

// пилообразная функция
template<typename T>
void f5(T* arr, int size)
{
	T a = 1; // масштабирование по x
	T c = 1; // сдвиг по х
	T b = 1; // мастабирование по y
	double j = 0.0; // координата y
	for (int i = 0; i < size; i++, j += 0.2)
	{
		arr[i] = asin(sin(j * a + c)) * b;
	}
}

// ступенчатая функция
template<typename T>
void f6(T* arr, int size)
{
	int width = 20;		// длина одной ступени
	double high = 0.3;	// высота одной ступени
	double j = 0.0;		// координата y

	// координата j увеличивается на high (высоту шага),
	// если по i (координата x) прошло ровно width значений
	for (int i = 0; i < size; i++, j += ((i % width == 0) ? high : 0.0))
	{
		// координата y + шум, зависящий от высоты шага
		arr[i] = j + rand_double(high / 10, high / 10 * 4);
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
	//double* arr_d = new double[size];

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

int main()
{
	setlocale(LC_ALL, "ru");

	srand(time(NULL));

	// тип массива (int или double)
	int type = input_and_check(1, 2,
		"Выберите тип данных массива [1,2]:\n\t1.int\n\t2.double\n",
		"Должна быть введена 1 или 2\n");

	// размер массива
	int size = input_and_check(0, 1000,
		"Введите размер массива [0,1000]:\n",
		"Должна быть введено значение в интервале [0,1000]\n");

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
	//DRAW
	GraphsDrawer gd;
	gd.run();

	return 0;
}