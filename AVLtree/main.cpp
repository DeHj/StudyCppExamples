// BinarySearchTree.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "AVLtree.h"
#include "Menu.h"

#include <iostream>


using namespace std;


AVLtree<int, int> avltree1 = AVLtree<int, int>();


void funcForDFS(const Node<int, int> node)
{
	int nSpace;
	if (node.Ancestor == nullptr) { nSpace = 0; }
	else
	{
		int leftDepth;
		if (node.Ancestor->LeftTree == nullptr) { leftDepth = 0; }
		else { leftDepth = node.Ancestor->LeftTree->Depth; }

		int rightDepth;
		if (node.Ancestor->RightTree == nullptr) { rightDepth = 0; }
		else { rightDepth = node.Ancestor->RightTree->Depth; }

		if (leftDepth > rightDepth) { nSpace = leftDepth; }
		else { nSpace = rightDepth; }
		nSpace = avltree1.Height() - nSpace;
	}

	for (int i = 0; i < nSpace * 1; i++)
	{
		cout << " ";
	}

	cout << node.Value;

	cout << endl;
}


void add()
{
	int key, value;
	cout << "Введите значение добавляемого элемента:" << endl;
	cin >> value;

	if (!cin.fail())
	{
		cout << "Введите значение ключа добавляемого элемента:" << endl;
		cin >> key;
	}

	if (cin.fail())
	{
		cout << "Некорректный ввод." << endl;
		cin.clear();
		cin.ignore(32767, '\n');

		_getch();
	}
	else
	{
		avltree1.Add(key, value);
	}
}

void remove()
{
	int key;
	cout << "Введите значения ключа, по которому необходимо удалить элемент:" << endl;
	cin >> key;

	if (cin.fail())
	{
		cout << "Некорректный ввод." << endl;
		cin.clear();
		cin.ignore(32767, '\n');

		_getch();
	}
	else
	{
		avltree1.Remove(key);
	}
}

void find()
{
	int key;
	cout << "Введите значения ключа, по которому необходимо найти элемент:" << endl;
	cin >> key;

	if (cin.fail())
	{
		cout << "Некорректный ввод." << endl;
		cin.clear();
		cin.ignore(32767, '\n');
	}
	else
	{
		Result<int> result = avltree1.Find(key);
		if (result.isFind) { cout << "Значение элемента с ключом " << key << " равно " << result.result << "." << endl; }
		else { cout << "Элемент с ключом " << key << " не найден."; }
	}

	_getch();
}

void writeOnScreen()
{
	avltree1.DFS(funcForDFS);
	cout << endl;
	_getch();
}

int main()
{
	setlocale(LC_ALL, "Russian");

	Menu menu1 = Menu();

	menu1.AddWindow(nullptr);       // 0
	menu1.AddWindow(add);           // 1
	menu1.AddWindow(remove);        // 2
	menu1.AddWindow(find);          // 3
	menu1.AddWindow(writeOnScreen); // 4
	menu1.AddWindow(nullptr);       // 5

	menu1.AddJunction(0, 1, "Добавить элемент в дерево.");
	menu1.AddJunction(0, 2, "Удалить элемент дерева.");
	menu1.AddJunction(0, 3, "Найти элемент дерева.");
	menu1.AddJunction(0, 4, "Вывести на экран все элементы дерева в соответствии с порядком обхода в глубину, начиная с корня.");
	menu1.AddJunction(0, 5, "Закончить работу с деревом.");
	menu1.AddJunction(1, 0, "");
	menu1.AddJunction(2, 0, "");
	menu1.AddJunction(3, 0, "");
	menu1.AddJunction(4, 0, "");

	menu1.Start();
}