#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <conio.h>

using namespace std;

// Диалоговое "окно"
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

	// Функций, выполняемая при входе в данное состояние меню
	void(*function)();

	// Список пунктов, среди которых можно выбрать один, и их соответствующие описания
	vector<Pair> nextWindows;

	Window(void(*func)())
	{
		function = func;
	}

	// Добавление перехода на другое "окно" из данного "окна"
	void AddJunction(Window* window, const string description)
	{
		nextWindows.push_back(Pair(window, description));
	}
};


struct Menu
{
private:

	const int diff = 48;

	// Список диалоговых "окон"
	vector<Window*> windows;

public:

	Menu()
	{
		windows = vector<Window*>();
	}

	// Добавление диалогового "окна" в меню
	void AddWindow(void(*func)())
	{
		windows.push_back(new Window(func));
	}

	// Добавление перехода из диалогового "окна" с индеком indexFrom в "окно" с индексом indexTo
	void AddJunction(const int indexFrom, const int indexTo, const string description)
	{
		windows[indexFrom]->AddJunction(windows[indexTo], description);
	}

	// Запуск диалогового меню
	void Start()
	{
		if (windows.size() == 0) { throw "Error 66"; }
		// Проверка на то, что из каждого состояния меню есть куда пойти

		Window* currentWindow = windows[0];

		// Цикл меню
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