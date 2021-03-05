#include <vector>

using namespace std;

#pragma once
template<class T>
class SegmentTree
{
	template<class T>
	struct Node
	{
		T value;
		Node<T>* leftSon;
		Node<T>* rightSon;

		Node()
		{
			leftSon = nullptr;
			rightSon = nullptr;
		}
	};

public:
	
	SegmentTree();
	SegmentTree(vector<T> segment, T(*f)(T a, T b));
	//SegmentTree(const SegmentTree<T> & copy);
	~SegmentTree();

	T FunctionSegment(const int l, const int r);

	void ChangeItem(const int index, const T value);

	int Size();

private:
	// Указатель на используемую функцию.
	T(*function)(T a, T b);

	Node<T>* root;
	int size;

	void build(Node<T>* node, vector<T> segment, const int l, const int r);

	void deleteTree(Node<T>* node);

	T functionOfSon(Node<T>* node, const int lNode, const int rNode, const int lSegment, const int rSegment);

	void copyTree(Node<T>* newNode, Node<T>* copyNode);

	void changeSon(Node<T>* node, const int lNode, const int rNode, const int index, const T value);
};





template<class T>
SegmentTree<T>::SegmentTree()
{
	function = nullptr;
	root = nullptr;
	size = 0;
}

// f - некоторая ассоциативная, коммуникативная функция.
template<class T>
SegmentTree<T>::SegmentTree(vector<T> segment, T(*f)(T a, T b))
{
	function = f;
	size = segment.size();

	root = new Node<T>();

	build(root, segment, 0, segment.size() - 1);
}

template<class T>
SegmentTree<T>::~SegmentTree()
{
	
}

template<class T>
T SegmentTree<T>::FunctionSegment(const int l, const int r)
{
	if (r < l)
		throw "error 1";

	return functionOfSon(root, 0, size - 1, l, r);
}

template<class T>
void SegmentTree<T>::ChangeItem(const int index, const T value)
{
	changeSon(root, 0, size - 1, index, value);

	/*int l = 0;
	int r = size - 1;

	Node<T>* currentNode = root;
	
	while (l != r)
	{
		int m = (r + l + 1) / 2;

		if (index < m)
		{
			r = m - 1;
			currentNode = currentNode->leftSon;
		}
		else
		{
			l = m;
			currentNode = currentNode->rightSon;
		}
	}

	currentNode->value = value;*/
}

template<class T>
int SegmentTree<T>::Size()
{
	return size;
}

template<class T>
void SegmentTree<T>::build(Node<T>* node, vector<T> segment, const int l, const int r)
{
	if (l == r)
	{
		node->value = segment[l];
	}
	else
	{
		int m = (r + l + 1) / 2;

		node->leftSon = new Node<T>();
		build(node->leftSon, segment, l, m - 1);

		node->rightSon = new Node<T>();
		build(node->rightSon, segment, m, r);

		node->value = function(node->leftSon->value, node->rightSon->value);
	}
}

template<class T>
T SegmentTree<T>::functionOfSon(Node<T>* node, const int lNode, const int rNode, const int lSegment, const int rSegment)
{
	int m = (rNode + lNode + 1) / 2;

	if (lSegment == lNode && rSegment == rNode)
		return node->value;

	if (rSegment < m)
		return functionOfSon(node->leftSon, lNode, m - 1, lSegment, rSegment);
	else if (lSegment >= m)
		return functionOfSon(node->rightSon, m, rNode, lSegment, rSegment);
	else
	{
		return function(functionOfSon(node->leftSon, lNode, m - 1, lSegment, m - 1),
			functionOfSon(node->rightSon, m, rNode, m, rSegment));
	}
}

template<class T>
void SegmentTree<T>::copyTree(Node<T>* newNode, Node<T>* copyNode)
{
	newNode->value = copyNode->value;

	if (copyNode->leftSon != nullptr)
	{
		newNode->leftSon = new Node<T>();
		copyTree(newNode->leftSon, copyNode->leftSon);
	}

	if (copyNode->rightSon != nullptr)
	{
		newNode->rightSon = new Node<T>();
		copyTree(newNode->rightSon, copyNode->rightSon);
	}
}

template<class T>
void SegmentTree<T>::changeSon(Node<T>* node, int lNode, int rNode, const int index, const T value)
{
	if (lNode == rNode)
	{
		node->value = value;
	}
	else
	{
		int m = (rNode + lNode + 1) / 2;

		T newValueSon;

		if (index < m)
		{
			rNode = m - 1;
			changeSon(node->leftSon, lNode, rNode, index, value);
		}
		else
		{
			lNode = m;
			changeSon(node->rightSon, lNode, rNode, index, value);
		}

		node->value = function(node->leftSon->value, node->rightSon->value);
	}
}