#pragma once


template <class ValueT>
struct Result
{
	bool isFind;
	ValueT result;

	Result()
	{
	}

	Result(const bool isFind, const ValueT result)
	{
		this->isFind = isFind;
		this->result = result;
	}
};



template <typename KeyT, class ValueT>
class Node
{
public:
	Node<KeyT, ValueT>* LeftTree;
	Node<KeyT, ValueT>* RightTree;
	Node<KeyT, ValueT>* Ancestor;

	KeyT Key;
	ValueT Value;
	int Depth;

	Node(KeyT key, ValueT value)
	{
		Key = key;
		Value = value;
		Depth = 1;

		LeftTree = nullptr;
		RightTree = nullptr;
		Ancestor = nullptr;
	}
};



template <typename KeyT, class ValueT>
class AVLtree
{
private:
	Node<KeyT, ValueT>* Root;

public:

	AVLtree()
	{
		Root = nullptr;
	}

	~AVLtree()
	{
		while (Root != nullptr) { RemoveNode(Root); }
	}

	// Добавляет узел со значением value и с ключом key
	void Add(const KeyT key, const ValueT value)
	{
		if (Root == nullptr)
		{
			Root = new Node<KeyT, ValueT>(key, value);
			return;
		}

		Node<KeyT, ValueT>* currentNode = Root;
		while (true)
		{
			// Определение того, куда двигаться:
			Node<KeyT, ValueT>* nextNode;
			if (key > currentNode->Key) { nextNode = currentNode->RightTree; }
			else if (key < currentNode->Key) { nextNode = currentNode->LeftTree; }
			else { return; }

			if (nextNode == nullptr) { break; }
			else { currentNode = nextNode; }
		}

		Node<KeyT, ValueT>* newNode = new Node<KeyT, ValueT>(key, value);
		newNode->Ancestor = currentNode;

		if (key > currentNode->Key) { currentNode->RightTree = newNode; }
		else { currentNode->LeftTree = newNode; }

		// Подъём вверх до корня и балансировка узлов:
		while (currentNode != nullptr)
		{
			FindDepth(currentNode);

			Balancing(currentNode);

			currentNode = currentNode->Ancestor;
		}
	}

	// Удаляет узел, ключ которого равен key
	void Remove(const KeyT key)
	{
		Node<KeyT, ValueT>* removingNode = FindNode(key);
		
		if (removingNode != nullptr)
		{
			RemoveNode(removingNode);
		}
	}

	// Возвращает значение узла, ключ которого равен key
	Result<ValueT> Find(const KeyT key)
	{
		Node<KeyT, ValueT>* node = FindNode(key);

		Result<ValueT> result;
		if (node != nullptr) { result = Result<ValueT>(true, node->Value); }
		else { result = Result<ValueT>(false, NULL); }

		return result;
	}

	// Обход дерева в глубину
	void DFS(void(*ptFunc)(Node<KeyT, ValueT>))
	{
		DFSRecursive(ptFunc, Root);
	}

	// Возвращает высоту дерева
	int Height()
	{
		return Root->Depth;
	}

private:

	void DFSRecursive(void(*ptFunc)(Node<KeyT, ValueT>), Node<KeyT, ValueT>* node)
	{
		if (node != nullptr)
		{
			DFSRecursive(ptFunc, node->LeftTree);
			
			ptFunc(*node);

			DFSRecursive(ptFunc, node->RightTree);
		}
	}

	void RemoveNode(Node<KeyT, ValueT>* removingNode)
	{
		int left = 0; int right = 0;
		if (removingNode->LeftTree != nullptr) { left = removingNode->LeftTree->Depth; }
		if (removingNode->RightTree != nullptr) { right = removingNode->RightTree->Depth; }

		if (left == 0 && right == 0)
		{
			// В случае, если удаляемый элемент - лист:

			if (removingNode != Root)
			{
				if (removingNode->Ancestor->LeftTree == removingNode) { removingNode->Ancestor->LeftTree = nullptr; }
				else { removingNode->Ancestor->RightTree = nullptr; }
			}
			else { Root = nullptr; }

			Node<KeyT, ValueT>* currentNode = removingNode->Ancestor;

			delete removingNode;

			// Подъём вверх до корня и балансировка узлов:
			while (currentNode != nullptr)
			{
				FindDepth(currentNode);

				Balancing(currentNode);

				currentNode = currentNode->Ancestor;
			}
		}
		else
		{
			Node<KeyT, ValueT>* currentNode;

			if (left > right)
			{
				// Поиск в левом поддереве
				currentNode = removingNode->LeftTree;
				while (currentNode->RightTree != nullptr) { currentNode = currentNode->RightTree; }
			}
			else
			{
				// Поиск в правом поддереве
				currentNode = removingNode->RightTree;
				while (currentNode->LeftTree != nullptr) { currentNode = currentNode->LeftTree; }
			}

			removingNode->Key = currentNode->Key;
			removingNode->Value = currentNode->Value;

			RemoveNode(currentNode);
		}
	}

	Node<KeyT, ValueT>* FindNode(const KeyT key)
	{
		Node<KeyT, ValueT>* currentNode = Root;

		while (currentNode != nullptr)
		{
			if (key > currentNode->Key) { currentNode = currentNode->RightTree; }
			else if (key < currentNode->Key) { currentNode = currentNode->LeftTree; }
			else { return currentNode; }
		}

		return nullptr;
	}

	int max(const int a, const int b)
	{
		if (a > b) { return a; }
		else { return b; }
	}

	// Переопределение значения глубины поддерева с корнем node
	void FindDepth(Node<KeyT, ValueT>* node)
	{
		int left = 0; int right = 0;
		if (node->LeftTree != nullptr) { left = node->LeftTree->Depth; }
		if (node->RightTree != nullptr) { right = node->RightTree->Depth; }

		node->Depth = max(left, right) + 1;
	}


	// При вращениях пересчитываются глубины только тех поддеревьев, которые непосредственно вращались
	// Для всех элементов "выше" балансируемого элемента необходим также пересчёт глубины

	// Малое левое вращение
	void SmallLeftRotation(Node<KeyT, ValueT>* node)
	{
		Node<KeyT, ValueT> *a, *b;
		Node<KeyT, ValueT> *L, *C, *R;

		a = node;
		b = a->RightTree;

		L = a->LeftTree;
		C = b->LeftTree;
		R = b->RightTree;

		if (node->Ancestor != nullptr)
		{
			if (node->Ancestor->LeftTree == node) { node->Ancestor->LeftTree = b; }
			else { node->Ancestor->RightTree = b; }
		}
		else { Root = b; }

		b->Ancestor = node->Ancestor;

		b->LeftTree = a;
		b->RightTree = R;
		a->Ancestor = b;
		R->Ancestor = b;

		a->LeftTree = L;
		a->RightTree = C;
		if (L != nullptr) { L->Ancestor = a; }
		if (C != nullptr) { C->Ancestor = a; }

		FindDepth(a);
		FindDepth(b);
	}
	// Большое левое вращение
	void LargeLeftRotation(Node<KeyT, ValueT>* node)
	{
		Node<KeyT, ValueT> *a, *b, *c;
		Node<KeyT, ValueT> *L, *R, *M, *N;

		a = node;
		b = a->RightTree;
		c = b->LeftTree;

		L = a->LeftTree;
		M = c->LeftTree;
		N = c->RightTree;
		R = b->RightTree;

		if (node->Ancestor != nullptr)
		{
			if (node->Ancestor->LeftTree == node) { node->Ancestor->LeftTree = c; }
			else { node->Ancestor->RightTree = c; }
		}
		else { Root = c; }

		c->Ancestor = node->Ancestor;

		c->LeftTree = a;
		c->RightTree = b;
		a->Ancestor = c;
		b->Ancestor = c;

		a->LeftTree = L;
		a->RightTree = M;
		if (L != nullptr) { L->Ancestor = a; }
		if (M != nullptr) { M->Ancestor = a; }

		b->LeftTree = N;
		b->RightTree = R;
		if (N != nullptr) { N->Ancestor = b; }
		if (R != nullptr) { R->Ancestor = b; }

		FindDepth(a);
		FindDepth(b);
		FindDepth(c);
	}
	// Малое правое вращение
	void SmallRightRotation(Node<KeyT, ValueT>* node)
	{
		Node<KeyT, ValueT> *a, *b;
		Node<KeyT, ValueT> *L, *C, *R;

		a = node;
		b = a->LeftTree;

		L = b->LeftTree;
		C = b->RightTree;
		R = a->RightTree;

		if (node->Ancestor != nullptr)
		{
			if (node->Ancestor->LeftTree == node) { node->Ancestor->LeftTree = b; }
			else { node->Ancestor->RightTree = b; }
		}
		else { Root = b; }

		b->Ancestor = node->Ancestor;

		b->LeftTree = L;
		b->RightTree = a;
		L->Ancestor = b;
		a->Ancestor = b;

		a->LeftTree = C;
		a->RightTree = R;
		if (C != nullptr) { C->Ancestor = a; }
		if (R != nullptr) { R->Ancestor = a; }

		FindDepth(a);
		FindDepth(b);
	}
	// Большое правое вращение
	void LargeRightRotation(Node<KeyT, ValueT>* node)
	{
		Node<KeyT, ValueT> *a, *b, *c;
		Node<KeyT, ValueT> *L, *R, *M, *N;

		a = node;
		b = a->LeftTree;
		c = b->RightTree;

		L = b->LeftTree;
		M = c->LeftTree;
		N = c->RightTree;
		R = a->RightTree;

		if (node->Ancestor != nullptr)
		{
			if (node->Ancestor->LeftTree == node) { node->Ancestor->LeftTree = c; }
			else { node->Ancestor->RightTree = c; }
		}
		else { Root = c; }

		c->Ancestor = node->Ancestor;

		c->LeftTree = b;
		c->RightTree = a;
		b->Ancestor = c;
		a->Ancestor = c;

		b->LeftTree = L;
		b->RightTree = M;
		if (L != nullptr) { L->Ancestor = b; }
		if (M != nullptr) { M->Ancestor = b; }

		a->LeftTree = N;
		a->RightTree = R;
		if (N != nullptr) { N->Ancestor = a; }
		if (R != nullptr) { R->Ancestor = a; }

		FindDepth(a);
		FindDepth(b);
		FindDepth(c);
	}

	// Типы вращений поддеревьев
	enum RotationType { LEFT, RIGHT, LARGE, SMALL };

	// Балансировка узла unbalancedNode
	void Balancing(Node<KeyT, ValueT>* node)
	{
		int left = 0; int right = 0;

		if (node->LeftTree != nullptr) { left = node->LeftTree->Depth; }
		if (node->RightTree != nullptr) { right = node->RightTree->Depth; }

		RotationType type1;

		if (left - right >= 2) { type1 = RIGHT; }
		else if (right - left >= 2) { type1 = LEFT; }
		else { return; }


		int center = 0; int side = 0;
		if (type1 == RIGHT)
		{
			if (node->LeftTree->LeftTree != nullptr) { side = node->LeftTree->LeftTree->Depth; }
			if (node->LeftTree->RightTree != nullptr) { center = node->LeftTree->RightTree->Depth; }
		}
		else
		{
			if (node->RightTree->LeftTree != nullptr) { center = node->RightTree->LeftTree->Depth; }
			if (node->RightTree->RightTree != nullptr) { side = node->RightTree->RightTree->Depth; }
		}

		RotationType type2;

		if (center > side) { type2 = LARGE; }
		else { type2 = SMALL; }

		
		// Вращение
		if (type1 == LEFT && type2 == SMALL) { SmallLeftRotation(node); }
		else if (type1 == RIGHT && type2 == SMALL) { SmallRightRotation(node); }
		else if (type1 == LEFT && type2 == LARGE) { LargeLeftRotation(node); }
		else if (type1 == RIGHT && type2 == LARGE) { LargeRightRotation(node); }
	}
};

