#include <iostream>
#include <ctime>
#include <fstream>
#include <cmath>
using namespace std;

//// ���������� ������� ���������� �������
//void random(double *arr)
//{
//	for (int i = 0; i < 200; i++)
//	{
//		arr[i] = (rand() % 25 + 1) / double((rand() % 25 + 1));
//	}
//}

//����������� �-�� �� �����������
template<typename T>
void f1(T *arr)
{
	double j = 0.0;
	for (int i = 0; i < 200; i++, j += 0.2)
	{
		arr[i] = j;
	}

	//k, b - ������������
	T k = 1;
	T b = 0;

	for (int i = 0; i < 200; i++)
	{
		arr[i] = k * arr[i] + b;
	}
}

//����������� �-�� �� ��������
template<typename T>
void f2(T *arr)
{
	double j = 0.0;
	for (int i = 0; i < 200; i++, j += 0.2)
	{
		arr[i] = j;
	}

	//k, b - ������������
	T k = 1;
	T b = 0;

	for (int i = 0; i < 200; i++)
	{
		arr[i] = -k * arr[i] + b;
	}
}

//��������� �-��
template<typename T>
void f3(T *arr)		//to do: ������� ���� ������
{
	//k ���������� �����������  [-25,25]

	for (int i = 0; i < 200; i++)
	{
		T k = T(rand() % 51 + (-25));
		arr[i] = k; 
	}

}

//�������� ����������� �-��(�����)
template<typename T>
void f4(T *arr)
{	
	double j = 0.0;
	for (int i = 0; i < 200; i++, j += 0.2)
	{
		arr[i] = j;
	}

	T a = 1; // �������
	T c = 1; // ���������
	T b = 1; // ����� ����

	for (int i = 0; i < 200; i++)
	{
		arr[i] = sin(a * arr[i] + c) * b;
	}

}

//�������� ����������� �-�� (����)
template<typename T>
void f5(T *arr)
{
	double j = 0.0;
	for (int i = 0; i < 200; i++, j += 0.2)
	{
		arr[i] = j;
	}

	T a = 1; // �������
	T c = 1; // ���������
	T b = 1; // ����� ����

	for (int i = 0; i < 200; i++)
	{
		arr[i] = asin(sin(arr[i] * a + c)) * b;
	}

}

//�������� ����������� �-�� (�����������)
template<typename T>
T f6(T x)
{
	T a = 1; // �������
	T c = 1; // ���������
	T b = 1; // ����� ����
	T res = asin(sin(x * a + c)) * b;
	return res;
}


int main()
{
	ofstream out("out.txt");
	srand(time(NULL));

	double* arr = new double[200];

	////������������ ������
	//f1(arr);

	////��������� ������
	//f2(arr);

	////��������� ����
	//f3(arr);

	////���������
	//f4(arr);

	//����
	f5(arr);

	//// ������ �������
	//for (int i = 0; i < 200; i++)
	//{
	//	cout << arr[i] << endl;
	//}

	// ������ ������ � ����
	for (int i = 0; i < 200; i++)
	{
		out << arr[i] << '\n';
	}

	out.close();
}