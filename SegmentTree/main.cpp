// Task1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "SegmentTree.h"
#include "Menu.h"

#include <iostream>
#include <string>


int sumInt(int a, int b)
{
	return a + b;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}




SegmentTree<int> st1;

void init()
{
	cout << "Введите размер создаваемого дерева отрезков." << endl;

	int size;
	cin >> size;

	vector<int> v = vector<int>(size);

	for (int i = 0; i < size; i++)
	{
		cout << "Введите " << i << "-й элемент создаваемого дерева отрезков." << endl;
		cin >> v[i];
	}

	st1 = SegmentTree<int>(SegmentTree<int>(v, sumInt));
}

void segmentSum()
{
	int l, r;

	cout << "Введите индекс левой границы отрезка." << endl;
	cin >> l;

	cout << "Введите индекс правой границы отрезка." << endl;
	cin >> r;

	if (l < 0 || r >= st1.Size() || l > r)
		cout << "Некорректный ввод." << endl;
	else
		cout << "Сумма элементов на данном отрезке равна " << st1.FunctionSegment(l, r) << "." << endl;

	_getch();
}

void changeItem()
{
	int index;

	cout << "Введите индекс элемента, который Вы хотите изменить." << endl;
	cin >> index;

	if (index < 0 || index >= st1.Size())
		cout << "Некорректный ввод." << endl;
	else
	{
		int newValue;

		cout << "Введите новое значение элемента." << endl;
		cin >> newValue;

		st1.ChangeItem(index, newValue);

		cout << "Готово." << endl;
	}

	_getch();
}


string sumStr(string a, string b)
{
	return a + b;
}

int main()
{
	/*vector<int> v1 = vector<int>(7);
	v1[0] = 0;
	v1[1] = 1;
	v1[2] = 2;
	v1[3] = 3;
	v1[4] = 4;
	v1[5] = 5;
	v1[6] = 6;

	SegmentTree<int> st2 = SegmentTree<int>(v1, sumInt);

	st2.ChangeItem(0, 10);

	cout << st2.FunctionSegment(0, 1) << endl;*/

	/*vector<string> v2 = vector<string>(9);
	v2[0] = "ab";
	v2[1] = "cde";
	v2[2] = "f";
	v2[3] = "kl";
	v2[4] = "p";
	v2[5] = "r";
	v2[6] = "s";
	v2[7] = "t";
	v2[8] = "ooo";

	SegmentTree<string> st2 = SegmentTree<string>(v2, sumStr);

	cout << st2.FunctionSegment(1, 4) << endl;*/

	//
	system("pause");



	setlocale(LC_ALL, "Russian");

	Menu menu1 = Menu();

	menu1.AddWindow(nullptr);       // 0
	menu1.AddWindow(init);          // 1
	menu1.AddWindow(nullptr);       // 2
	menu1.AddWindow(segmentSum);    // 3
	menu1.AddWindow(changeItem);    // 4
	menu1.AddWindow(nullptr);       // 5

	menu1.AddJunction(0, 1, "Создать новое дерево отрезков.");
	menu1.AddJunction(1, 2, "");
	menu1.AddJunction(2, 1, "Инициализировать дерево отрезков.");
	menu1.AddJunction(2, 3, "Посчитать сумму на отрезке.");
	menu1.AddJunction(2, 4, "Изменить какой-либо элемент.");
	menu1.AddJunction(2, 5, "Закончить работу с деревом.");
	menu1.AddJunction(3, 2, "");
	menu1.AddJunction(4, 2, "");

	menu1.Start();
}

