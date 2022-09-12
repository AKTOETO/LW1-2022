#include<iostream>
#include<ctime>
#include <fstream>
using namespace std;

//����������� �-�� �� �����������
template<typename T>
T f1(T x)
{
	//y=kx � - �����������
	T k = 2;
	return k * x;
}

//����������� �-�� �� ��������
template<typename T>
T f2(T x)
{
	//y=kx+b � - �����������
	T k = 2;
	T b = 2;
	return -k * x + b;
}

//��������� �-��
template<typename T>
T f3(T x)
{
	//k in [0,9]
	T k = T(rand() % 10);
	return x * k;
}

//�������� ����������� �-��
template<typename T>
T f4(T x)
{
	//� - �����������
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