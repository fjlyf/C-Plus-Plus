#include<iostream>
using namespace std;

template <class Type>
class BST;

//¶þ²æËÑË÷Ê÷
template<class Type>
class BSTNode
{
	friend class BST<Type>;
public:
	BSTNode(Type d = Type(), BSTNode<Type> *left = nullptr, BSTNode<Type> *right = nullptr)
		:data(d), leftChild(left), rightChild(right)
	{}
	~BSTNode()
	{}
private:
	Type data;
	BSTNode<Type> *leftChild;
	BSTNode<Type> *rightChild;
};

template <class Type>
class BST
{
public:
	BST() :root(nullptr)
	{}
public:
	bool Insert(const Type &x)
	{
		return Insert(root, x);
	}
protected:
	bool Insert(BSTNode<Type> *&t, const Type &x)
	{
		if (t == nullptr)
		{
			t = new BSTNode<Type>(x);
			return true;
		}
		else if (x < t->data)
			Insert(t->leftChild, x);
		else if (x>t->data)
			Insert(t->rightChild, x);
		else
			return false;
	}

private:
	BSTNode<Type> *root;
};

void main()
{
	int ar[] = { 53, 78, 65, 17, 87, 9, 81, 45, 23 };
	int n = sizeof(ar) / sizeof(ar[0]);
	BST<int> bst;
	for (int i = 0; i < n; ++i)
	{
		bst.Insert(ar[i]);
	}
}