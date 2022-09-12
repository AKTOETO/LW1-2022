#include<iostream>
#include<ctime>
#include <fstream>
using namespace std;

//упорядочная ф-ия по возрастанию
template<typename T>
T f1(T x)
{
	//y=kx к - коэффициент
	T k = 2;
	return k * x;
}

//упорядочная ф-ия по убыванию
template<typename T>
T f2(T x)
{
	//y=kx+b к - коэффициент
	T k = 2;
	T b = 2;
	return -k * x + b;
}

//случайная ф-ия
template<typename T>
T f3(T x)
{
	//k in [0,9]
	T k = T(rand() % 10);
	return x * k;
}

//частично упорядочная ф-ия
template<typename T>
T f4(T x)
{
	//к - коэффициент
	T k = 1;
	T res = sin(x) * k;
	return res;
}
int main()
{
	ofstream out("out.txt");
	srand(time(NULL));

	double a[50];
	double j = 0.0;
	for (int i = 0; i < 50; i++, j += 0.2)
	{
		a[i] = f1(j);
		out << a[i] << '\n';
	}
	out.close();
}