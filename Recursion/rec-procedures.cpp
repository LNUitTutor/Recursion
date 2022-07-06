#include "rec-procedures.h"
#include <chrono>

long long HarmFibo(unsigned n)
{
	if (n < 2) return 1LL;                         // ������������ ����'����
	else return HarmFibo(n - 1) + HarmFibo(n - 2); // ��������
}

long long Factorial(unsigned n)
{
	if (n < 2) return 1LL;            // ������������ ����'����
	else return n * Factorial(n - 1); // ��������
}

long long Fibo(long long a, long long b, unsigned n)
{
	if (n < 1) return a;               // ������������ ����'����
	else return Fibo(b, a + b, n - 1); // ��������
}
long long Fibonacci(unsigned n)
{
	return Fibo(1, 1, n);
}

void CalcFibo()
{
	cout << "* ���������� ����� Գ������� *\n\n";
	unsigned n;
	cout << "������ n: "; cin >> n;
	cout << "������� ������������ �������\n F(" << n << ") = ";
	auto begin = std::chrono::steady_clock::now();
	long long F = HarmFibo(n);
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << F << "   " << elapsed_ms.count() << " ms ellapsed\n";
	cout << "������� ������������ ���������\n F(" << n << ") = ";
	begin = std::chrono::steady_clock::now();
	F = Fibonacci(n);
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << F << "   " << elapsed_ms.count() << " ms ellapsed\n";
}

// ================================================================================

// ����� ������� ���� ���������� ������ �����
void MoveDisk(Position from, Position to)
{
	static const char* name[3] = {" Left ", "Middle", " Right"};
	cout << name[from] << " --> " << name[to] << '\n';
}
// ���� ����������� ������ ��� ���������� ��� �
// h ����� � ������� from �� ��������� _to
void MoveTower(short h, Position from, Position to, Position through)
{
	if (h == 1) MoveDisk(from, to);   // �������� ������
	else
	{                                  // �������� �� ���� ����� ������ h-1
		MoveTower(h - 1, from, through, to);
		MoveDisk(from, to);
		MoveTower(h - 1, through, to, from);
	}
}
void SolveTowers()
{
	cout << "* ����'�������� ������ ��� �������� ��� *\n\n";
	short h;
	cout << "������ ������ ���: "; cin >> h;
	MoveTower(h, Left, Right, Middle);
}

// ================================================================================

void PrintArr(ExtInt* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		cout.width(3); cout << a[i];
	}
	cout << '\n';
}
ostream& operator<<(ostream& os, const ExtInt& x)
{
	os << x.val << '-' << x.ind;
	return os;
}
bool operator>(const ExtInt& a, const ExtInt& b)
{
	return a.val > b.val;
}
// ��������� �������� ���������� ������ a ������ n
void StableQuickSort(ExtInt *a, int n)
{
	// ������������ ������
	int pivot_index = 0; // ����� ����������� �������, ����� ��������-������������
	int begin_of_unsorted = 1; // ������� ������������� �������
	while (begin_of_unsorted < n)
	{
		if (a[pivot_index] > a[begin_of_unsorted])
		{                // ����� �������� ���� ��� ������� �� ������������
			ExtInt to_transfer = a[begin_of_unsorted];
			for (int k = begin_of_unsorted - 1; k >= pivot_index; --k) a[k + 1] = a[k];
			a[pivot_index] = to_transfer;
			++pivot_index;
		}
		// ������ �� ������������ ���������� ��������
		++begin_of_unsorted;
	}
	// �� ����� ���������� �� �������, ������������ ��
	if (pivot_index > 1) StableQuickSort(a, pivot_index);
	// �� ����� � ���� ������������, ������������ �� �����
	if (n - pivot_index > 1)
		StableQuickSort(a + pivot_index + 1, n - pivot_index - 1);
}

void QuickSort(ExtInt* a, int low, int high)
{
	// ����� ����������� �� ������� [low; end_of_small]
	int end_of_small = high;       // ����� ���� ����� ������
	// ����� ����������� �� ������� [begin_of_large; high]
	int begin_of_large = low;      // ��� ���� ����� ������
	ExtInt pivot = a[(low + high) / 2]; // �������� ������������
	while (begin_of_large <= end_of_small)
	{
		// �������� "����������": ����� ����� ������
		while (pivot > a[begin_of_large]) ++begin_of_large;
		//                         �� ��� ����� ������
		while (a[end_of_small] > pivot) --end_of_small;
		if (begin_of_large < end_of_small)
			// ���� "����������" �� � ���� ������, �� �� ����� ������� ������
		{
			ExtInt to_swap = a[begin_of_large];
			a[begin_of_large] = a[end_of_small];
			a[end_of_small] = to_swap;
			++begin_of_large;
			--end_of_small;
		}
		else if (begin_of_large == end_of_small)
			// ����� ���������� �� �����������
		{
			++begin_of_large;
			--end_of_small;
		}
	}
	if (end_of_small > low)       // ������������ �����
		QuickSort(a, low, end_of_small);
	if (begin_of_large < high)    // �� �����
		QuickSort(a, begin_of_large, high);
}

void UseQuickSort()
{
	cout << "* ������������� ������ ����� \"�����\" *\n\n";
	ExtInt a[] = { { 5, 'a' }, { 3, 'a' }, { 9, 'a' }, { 2, 'a' }, { 1, 'a' }, { 2, 'b' }, { 6, 'a' }, { 5, 'b' }, { 8, 'a' }, { 3, 'b' },
	               { 4, 'a' }, { 7, 'a' }, { 2, 'c' }, { 8, 'b' }, { 5, 'c' }, { 5, 'd' } };
	ExtInt b[] = { { 5, 'a' }, { 3, 'a' }, { 9, 'a' }, { 2, 'a' }, { 1, 'a' }, { 2, 'b' }, { 6, 'a' }, { 5, 'b' }, { 8, 'a' }, { 3, 'b' },
	               { 4, 'a' }, { 7, 'a' }, { 2, 'c' }, { 8, 'b' }, { 5, 'c' }, { 5, 'd' } };
	const int n = sizeof a / sizeof a[0];
	cout << "���������� �����\n";
	PrintArr(a, n);
	cout << "���������� �������� ���������� ����������\n";
	StableQuickSort(a, n);
	PrintArr(a, n);
	QuickSort(b, 0, n - 1);
	cout << "���������� �������� ����������\n";
	PrintArr(b, n);
}

// ================================================================================

DataType_t PreorderSum(Tree_t t)
{
	if (t == nullptr) return 0;
	else
		return t->val + PreorderSum(t->left) + PreorderSum(t->right);
}

DataType_t SumEco(Tree_t t)
{
	if (t == nullptr) return 0;
	else
	{
		DataType_t s = t->val;
		if (t->left != nullptr) s += SumEco(t->left);
		if (t->right != nullptr) s += SumEco(t->right);
		return s;
	}
}

DataType_t SumNotEmpty(Tree_t t)
{
	DataType_t s = t->val;
	if (t->left != nullptr) s += SumNotEmpty(t->left);
	if (t->right != nullptr) s += SumNotEmpty(t->right);
	return s;
}
DataType_t Sum(Tree_t t)
{
	return (t == nullptr) ? 0 : SumNotEmpty(t);
}

// ����� ������ � ������������ ���������
void PrintTree(const Tree_t t, unsigned shift)
{
	// ���� �������� ������ �� ������ � ����� � ���������, �� ��������� ��������� ������
	if (t != nullptr)
	{
		PrintTree(t->left, shift + 1);  // ���� ����� ��������
		// ���� ������ ����������:
		for (unsigned i = 0; i < shift; ++i) cout << '\t'; // �������� - �������
		std::cout << t->val << '\n';                       // ���� - ��������
		PrintTree(t->right, shift + 1); // ���� ������� ��������
	}
}

void TraverseTree()
{
	cout << "* ���� ��������� ������ � ���������� ���� ���� �������� *\n\n";
	Tree_t t = new TreeNode(1, new TreeNode(2, new TreeNode(4, nullptr, nullptr), new TreeNode(5, nullptr, nullptr)),
		new TreeNode(3, nullptr, new TreeNode(6, nullptr, nullptr)));
	PrintTree(t, 0);
	cout << " s = " << PreorderSum(t) << '\n';
	cout << " S = " << Sum(t) << '\n';
}
