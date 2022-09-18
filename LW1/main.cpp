#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "gui/gui.hpp"	// для графиков
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
void f3(T* arr, int size)		//to do: чота тут было, но чо-хз
{
	//k изменяется в интервале [-25,25]
	for (int i = 0; i < size; i++)
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

int main()
{
	setlocale(LC_ALL, "ru");

	srand(time(NULL));

	// тип массива
	int type;
	cout << "Выберите тип данных массива:\n\t1.int\n\t2.double\n";
	cin >> type;

	// размер массива
	int size = 200;

	// массив
	int* arr_i = new int[size];
	// массив
	double* arr_d = new double[size];

	// массив указателей на функции типа int
	void (*funcs_i[])(int*, int) = { f1,f2,f3,f4,f5,f6 };

	// массив указателей на функции типа double
	void (*funcs_d[])(double*, int) = { f1,f2,f3,f4,f5,f6 };

	// имена файлов
	char name_of_file[6][7] =
	{
		"f1.txt",
		"f2.txt",
		"f3.txt",
		"f4.txt",
		"f5.txt",
		"f6.txt"
	};
	
	// запуск всех функций
	for (int i = 0; i < 6; i++)
	{
		// файл вывода данных
		ofstream out(name_of_file[i]);

		// выбор типа данных
		switch (type)
		{
			// если был выбран int
		case 1:
			funcs_i[i](arr_i, size);
			
			// печать массива в файл
			print_arr(arr_i, size, out);
			break;
			// если был выбран double
		case 2:
			funcs_d[i](arr_d, size);
			
			// печать массива в файл
			print_arr(arr_d, size, out);
			break;
		}

		// закрытие файлового потока
		out.close();
	}	
	// отрисовка графиков
	DRAW
	return 0;
}