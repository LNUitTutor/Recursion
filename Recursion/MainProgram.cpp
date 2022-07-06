#include <Windows.h>
#include "rec-procedures.h"

int main()
{
	// ������������ ������

	SetConsoleOutputCP(1251); // ��������� ��������� ���������
	int answer;
	do
	{
		system("cls");
		cout << "������� �������� ��� ���������:\n\n 1 - ����� Գ�������\n"
			<< " 2 - ������ ��� �������� ���\n 3 - �������� �������� ����������\n"
			<< " 4 - ����� ��������� ������\n 5 - ���������� ������\n>>>> ";
		cin >> answer;
		system("cls");
		switch (answer)
		{
		case 1: CalcFibo(); break;
		case 2: SolveTowers(); break;
		case 3: UseQuickSort(); break;
		case 4: TraverseTree(); break;
		default: cout << "�� ���������!\n";
		}
		system("pause");
	}
	while (answer > 0 && answer < 5);
	return 0;
}