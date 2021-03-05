#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <conio.h>

using namespace std;

// ���������� "����"
struct Window
{
	struct Pair
	{
		Window* nextWindow;
		string description;

		Pair(Window* nextWindow, string description)
		{
			this->nextWindow = nextWindow;
			this->description = description;
		}
	};

	// �������, ����������� ��� ����� � ������ ��������� ����
	void(*function)();

	// ������ �������, ����� ������� ����� ������� ����, � �� ��������������� ��������
	vector<Pair> nextWindows;

	Window(void(*func)())
	{
		function = func;
	}

	// ���������� �������� �� ������ "����" �� ������� "����"
	void AddJunction(Window* window, const string description)
	{
		nextWindows.push_back(Pair(window, description));
	}
};


struct Menu
{
private:

	const int diff = 48;

	// ������ ���������� "����"
	vector<Window*> windows;

public:

	Menu()
	{
		windows = vector<Window*>();
	}

	// ���������� ����������� "����" � ����
	void AddWindow(void(*func)())
	{
		windows.push_back(new Window(func));
	}

	// ���������� �������� �� ����������� "����" � ������� indexFrom � "����" � �������� indexTo
	void AddJunction(const int indexFrom, const int indexTo, const string description)
	{
		windows[indexFrom]->AddJunction(windows[indexTo], description);
	}

	// ������ ����������� ����
	void Start()
	{
		if (windows.size() == 0) { throw "Error 66"; }
		// �������� �� ��, ��� �� ������� ��������� ���� ���� ���� �����

		Window* currentWindow = windows[0];

		// ���� ����
		while (true)
		{
			system("CLS");

			if (currentWindow->function != nullptr) { currentWindow->function(); }

			if (currentWindow->nextWindows.size() == 0) { break; }
			else if (currentWindow->nextWindows.size() == 1) { currentWindow = currentWindow->nextWindows[0].nextWindow; }
			else
			{
				for (int i = 0; i < currentWindow->nextWindows.size(); i++)
				{
					cout << i + 1 << ". " << currentWindow->nextWindows[i].description << endl;
				}

				int index;
				while (true)
				{
					index = _getch() - diff - 1;
					if (index >= 0 && index < currentWindow->nextWindows.size()) { break; }
				}

				currentWindow = currentWindow->nextWindows[index].nextWindow;
			}
		}
	}
};