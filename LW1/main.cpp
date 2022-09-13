#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

//// заполнение массива случайными числами
//void random(double *arr)
//{
//	for (int i = 0; i < 200; i++)
//	{
//		arr[i] = (rand() % 25 + 1) / double((rand() % 25 + 1));
//	}
//}

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
	double j = 0.0; // координата y
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
void print_arr(T* arr, int size,
	basic_ofstream<char, char_traits<char>>& stream)
{
	for (int i = 0; i < size; i++)
	{
		stream << fixed << setprecision(6)
			<< arr[i] << '\n';
	}
}

int main()
{
	ofstream out("out.txt");
	srand(time(NULL));

	// размер массива
	int size = 200;

	double* arrd = new double[size];
	int* arri = new int[size];

	//вызов генерации случайной функции
	f1(arrd, size);

	// вывод массива
	print_arr(arrd, size, out);

	out.close();
}