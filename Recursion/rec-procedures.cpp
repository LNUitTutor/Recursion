#include "rec-procedures.h"
#include <chrono>

long long HarmFibo(unsigned n)
{
	if (n < 2) return 1LL;                         // елементарний розв'язок
	else return HarmFibo(n - 1) + HarmFibo(n - 2); // зведення
}

long long Factorial(unsigned n)
{
	if (n < 2) return 1LL;            // елементарний розв'язок
	else return n * Factorial(n - 1); // зведення
}

long long Fibo(long long a, long long b, unsigned n)
{
	if (n < 1) return a;               // елементарний розв'язок
	else return Fibo(b, a + b, n - 1); // зведення
}
long long Fibonacci(unsigned n)
{
	return Fibo(1, 1, n);
}

void CalcFibo()
{
	cout << "* Обчислення чисел Фібоначчі *\n\n";
	unsigned n;
	cout << "Введіть n: "; cin >> n;
	cout << "Рекурсія комбінуванням викликів\n F(" << n << ") = ";
	auto begin = std::chrono::steady_clock::now();
	long long F = HarmFibo(n);
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << F << "   " << elapsed_ms.count() << " ms ellapsed\n";
	cout << "Рекурсія комбінуванням параметрів\n F(" << n << ") = ";
	begin = std::chrono::steady_clock::now();
	F = Fibonacci(n);
	end = std::chrono::steady_clock::now();
	elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	cout << F << "   " << elapsed_ms.count() << " ms ellapsed\n";
}

// ================================================================================

// друкує команду щодо переміщення одного диска
void MoveDisk(Position from, Position to)
{
	static const char* name[3] = {" Left ", "Middle", " Right"};
	cout << name[from] << " --> " << name[to] << '\n';
}
// будує послідовність команд про переміщення вежі з
// h дисків зі стержня from на стережень _to
void MoveTower(short h, Position from, Position to, Position through)
{
	if (h == 1) MoveDisk(from, to);   // найменша задача
	else
	{                                  // зведення до двох задач розміру h-1
		MoveTower(h - 1, from, through, to);
		MoveDisk(from, to);
		MoveTower(h - 1, through, to, from);
	}
}
void SolveTowers()
{
	cout << "* Розв'язування задачі про Ханойські вежі *\n\n";
	short h;
	cout << "Введіть висоту вежі: "; cin >> h;
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
// процедура швидкого сортування масиву a розміру n
void StableQuickSort(ExtInt *a, int n)
{
	// перетворення масиву
	int pivot_index = 0; // кінець відсортованої частини, номер елемента-дискримінанта
	int begin_of_unsorted = 1; // початок невідсортованої частини
	while (begin_of_unsorted < n)
	{
		if (a[pivot_index] > a[begin_of_unsorted])
		{                // треба звільнити місце для меншого від дискримінанта
			ExtInt to_transfer = a[begin_of_unsorted];
			for (int k = begin_of_unsorted - 1; k >= pivot_index; --k) a[k + 1] = a[k];
			a[pivot_index] = to_transfer;
			++pivot_index;
		}
		// більший від дискримінанта залишається праворуч
		++begin_of_unsorted;
	}
	// усі менші залишилися на початку, впорядковуємо їх
	if (pivot_index > 1) StableQuickSort(a, pivot_index);
	// усі більші – після дискримінанта, впорядковуємо їх також
	if (n - pivot_index > 1)
		StableQuickSort(a + pivot_index + 1, n - pivot_index - 1);
}

void QuickSort(ExtInt* a, int low, int high)
{
	// менші розташовано на проміжку [low; end_of_small]
	int end_of_small = high;       // права межа групи менших
	// більші розташовано на проміжку [begin_of_large; high]
	int begin_of_large = low;      // ліва межа групи більших
	ExtInt pivot = a[(low + high) / 2]; // значення дискримінанта
	while (begin_of_large <= end_of_small)
	{
		// знайдемо "неправильні": великі серед менших
		while (pivot > a[begin_of_large]) ++begin_of_large;
		//                         та малі серед більших
		while (a[end_of_small] > pivot) --end_of_small;
		if (begin_of_large < end_of_small)
			// якщо "неправильні" не в своїх групах, то їх треба обміняти місцями
		{
			ExtInt to_swap = a[begin_of_large];
			a[begin_of_large] = a[end_of_small];
			a[end_of_small] = to_swap;
			++begin_of_large;
			--end_of_small;
		}
		else if (begin_of_large == end_of_small)
			// пошук завершився на дискримінанті
		{
			++begin_of_large;
			--end_of_small;
		}
	}
	if (end_of_small > low)       // впорядковуємо менші
		QuickSort(a, low, end_of_small);
	if (begin_of_large < high)    // та більші
		QuickSort(a, begin_of_large, high);
}

void UseQuickSort()
{
	cout << "* Впорядкування масиву цілих \"чисел\" *\n\n";
	ExtInt a[] = { { 5, 'a' }, { 3, 'a' }, { 9, 'a' }, { 2, 'a' }, { 1, 'a' }, { 2, 'b' }, { 6, 'a' }, { 5, 'b' }, { 8, 'a' }, { 3, 'b' },
	               { 4, 'a' }, { 7, 'a' }, { 2, 'c' }, { 8, 'b' }, { 5, 'c' }, { 5, 'd' } };
	ExtInt b[] = { { 5, 'a' }, { 3, 'a' }, { 9, 'a' }, { 2, 'a' }, { 1, 'a' }, { 2, 'b' }, { 6, 'a' }, { 5, 'b' }, { 8, 'a' }, { 3, 'b' },
	               { 4, 'a' }, { 7, 'a' }, { 2, 'c' }, { 8, 'b' }, { 5, 'c' }, { 5, 'd' } };
	const int n = sizeof a / sizeof a[0];
	cout << "Початковий масив\n";
	PrintArr(a, n);
	cout << "Результати швидкого стабільного сортування\n";
	StableQuickSort(a, n);
	PrintArr(a, n);
	QuickSort(b, 0, n - 1);
	cout << "Результати швидкого сортування\n";
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

// друкує дерево з відображенням структури
void PrintTree(const Tree_t t, unsigned shift)
{
	// друк елементів дерева по одному в рядку з відступами, що моделюють структуру дерева
	if (t != nullptr)
	{
		PrintTree(t->left, shift + 1);  // друк лівого піддерева
		// Друк кореня двоетапний:
		for (unsigned i = 0; i < shift; ++i) cout << '\t'; // спочатку - відступи
		std::cout << t->val << '\n';                       // потім - значення
		PrintTree(t->right, shift + 1); // друк правого піддерева
	}
}

void TraverseTree()
{
	cout << "* Друк двійкового дерева й обчислення суми його елементів *\n\n";
	Tree_t t = new TreeNode(1, new TreeNode(2, new TreeNode(4, nullptr, nullptr), new TreeNode(5, nullptr, nullptr)),
		new TreeNode(3, nullptr, new TreeNode(6, nullptr, nullptr)));
	PrintTree(t, 0);
	cout << " s = " << PreorderSum(t) << '\n';
	cout << " S = " << Sum(t) << '\n';
}
