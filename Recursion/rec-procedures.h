#ifndef _REC_PROCEDURES_GUARD_
#define _REC_PROCEDURES_GUARD_

#include <iostream>
using std::cout;
using std::cin;
using std::ostream;

long long HarmFibo(unsigned);
long long Fibonacci(unsigned n);

enum Position {Left, Middle, Right};
void MoveTower(short h, Position from, Position _to, Position through);

struct ExtInt
{
	int val;
	char ind;
};
ostream& operator<<(ostream& os, const ExtInt& x);
bool operator>(const ExtInt& a, const ExtInt& b);

void StableQuickSort(ExtInt* array, int n);
void QuickSort(ExtInt* array, int low, int high);

struct TreeNode; // ������� ���������� ��������� ������� ��� ���������� ���������
typedef TreeNode* Tree_t; // ��������� ���� ��'� ����� ��������
typedef int DataType_t;   // ��� ������������ ������� ������� ���� ���� ��������

struct TreeNode
{
	DataType_t val;  // ����������� �������
	Tree_t left;     // ��'���� � ����������
	Tree_t right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(DataType_t x, Tree_t l, Tree_t r) : val(x), left(l), right(r) {}
};

DataType_t PreorderSum(Tree_t t);
DataType_t SumEco(Tree_t t);
DataType_t SumNotEmpty(Tree_t t);
DataType_t Sum(Tree_t t);
void PrintTree(const Tree_t, unsigned);

void CalcFibo();
void SolveTowers();
void UseQuickSort();
void TraverseTree();


#endif