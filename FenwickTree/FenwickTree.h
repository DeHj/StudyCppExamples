#include <vector>

using namespace std;

#pragma once
template<class T>
class FenwickTree
{
public:

	FenwickTree(vector<T> arr, T(*f)(T a, T b), T(*reversef)(T a, T b));
	~FenwickTree();

	T FunctionForSegment(const int l, const int r);

	void ChangeItem(const int index, const T value);

private:

	vector<T> tree;

	// ��������� �� ������������ �������.
	T(*usingOperation)(T a, T b);
	T(*reverseOperation)(T a, T b);

	T FunctionForPrefix(const int prefixSize);

	// ������� F
	int F(const int i)
	{
		return (i & (i + 1));
	}
};

// f - ��������� �������������, ��������������� ��������� ��������. reversef - �������� � f ��������. ����������� �� ��������� ��� ���� T, �� ���� T(), ������ ����������� �� ��������� � �������� f ������� e, �� ���� �����, ��� f(e, a) = f(a, e) = a.
template<class T>
FenwickTree<T>::FenwickTree(vector<T> arr, T(*f)(T a, T b), T(*reversef)(T a, T b))
{
	usingOperation = f;
	reverseOperation = reversef;

	tree = vector<T>(arr.size());

	for (int i = 0; i < arr.size(); i++)
	{
		tree[i] = T();

		for (int j = F(i); j <= i; j++)
			tree[i] = usingOperation(tree[i], arr[j]);
	}
}

template<class T>
FenwickTree<T>::~FenwickTree()
{
}

template<class T>
T FenwickTree<T>::FunctionForSegment(const int l, const int r)
{
	if (l > r)
		throw "error 1";
	return reverseOperation(FunctionForPrefix(r + 1), FunctionForPrefix(l));
}

template<class T>
T FenwickTree<T>::FunctionForPrefix(const int prefixSize)
{
	T result = T();

	int index = prefixSize - 1;
	while (index >= 0)
	{
		result = usingOperation(result, tree[index]);
		index = F(index) - 1;
	}

	return result;
}

template<class T>
void FenwickTree<T>::ChangeItem(int index, const T value)
{
	T changeValue = FunctionForSegment(index, index);

	while (index < tree.size())
	{
		tree[index] = reverseOperation(tree[index], changeValue);
		tree[index] = usingOperation(tree[index], value);

		index = (index | (index + 1));
	}
}
