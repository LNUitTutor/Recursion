#include <Windows.h>
#include "rec-procedures.h"

int main()
{
	// Застосування рекурсії

	SetConsoleOutputCP(1251); // налаштуємо виведення кирилицею
	int answer;
	do
	{
		system("cls");
		cout << "Виберіть алгоритм для виконання:\n\n 1 - Числа Фібоначчі\n"
			<< " 2 - Задача про Ханойські вежі\n 3 - Алгоритм швидкого сортування\n"
			<< " 4 - Обхід двійкового дерева\n 5 - Завершення роботи\n>>>> ";
		cin >> answer;
		system("cls");
		switch (answer)
		{
		case 1: CalcFibo(); break;
		case 2: SolveTowers(); break;
		case 3: UseQuickSort(); break;
		case 4: TraverseTree(); break;
		default: cout << "До побачення!\n";
		}
		system("pause");
	}
	while (answer > 0 && answer < 5);
	return 0;
}