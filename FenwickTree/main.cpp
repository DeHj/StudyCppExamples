// Task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "FenwickTree.h"
#include <iostream>

int sum(int a, int b)
{
	return a + b;
}

int diff(int a, int b)
{
	return a - b;
}

int xor(int a, int b)
{
	return a ^ b;
}

int main()
{
	vector<int> v1 = vector<int>(9);
	v1[0] = 8;
	v1[1] = 5;
	v1[2] = 1;
	v1[3] = 7;
	v1[4] = 3;
	v1[5] = 9;
	v1[6] = 4;
	v1[7] = 6;
	v1[8] = 15;




	cout << "sum:" << endl;
	FenwickTree<int> ft1 = FenwickTree<int>(v1, sum, diff);

	cout << ft1.FunctionForSegment(0, 3) << endl;
	cout << ft1.FunctionForSegment(3, 5) << endl;
	cout << ft1.FunctionForSegment(5, 8) << endl;

	ft1.ChangeItem(3, 0);

	cout << ft1.FunctionForSegment(0, 3) << endl;
	cout << ft1.FunctionForSegment(3, 5) << endl;
	cout << ft1.FunctionForSegment(5, 8) << endl;




	cout << endl;

	cout << "xor:" << endl;
	FenwickTree<int> ft2 = FenwickTree<int>(v1, xor, xor);

	cout << ft2.FunctionForSegment(0, 3) << endl;
	cout << ft2.FunctionForSegment(3, 5) << endl;
	cout << ft2.FunctionForSegment(5, 8) << endl;

	system("pause");
}
