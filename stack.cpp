#define _CRT_SECURE_N0_WARNINGS
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<array>
#include<list>
#include<assert.h>
#include<functional>
using namespace std;


namespace fj
{
	template<class T,class Cont=vector<T>>
	class stack
	{
	public:
		stack()
		{}
		void push(const T &x)
		{
			c.push_back(x);
		}
		T& top()
		{
			return c.back();
		}
		void pop()
		{
			c.pop_back();
		}
		bool empty()const
		{
			return c.empty();
		}
	private:
		Cont c;
	};
	template<class T,class Cont=list<T>>
	class queue
	{
	public:
		queue()
		{}
		void push(const T &x)
		{
			c.push_back(x);
		}
		T front()const
		{
			return c.front();
		}
	private:
		Cont c;
	};
}

void main()
{
	fj::stack<int> st;
	for (int i = 1; i <= 5; ++i)
		st.push(i);
	while (!st.empty())
	{
		int val = st.top();
		st.pop();
		cout << val << " 出栈." << endl;
	}
}

/*
namespace fj
{
	template<class T>
	class stack
	{
	public:
		stack()
		{}
		void push(const T &x)
		{
			c.push_back(x);
		}
		T& top()
		{
			return c.back();
		}
		void pop()
		{
			c.pop_back();
		}
		bool empty()const
		{
			return c.empty();
		}
	private:
		list<T> c;
	};
}

void main()
{
	fj::stack<int> st;
	for (int i = 1; i <= 5; ++i)
		st.push(i);
	while (!st.empty())
	{
		int val = st.top();
		st.pop();
		cout << val << " 出栈." << endl;
	}
}

/*
namespace fj
{
	template<class T>
	class stack
	{
	public:
		stack()
		{}
		void push(const T &x)
		{
			c.push_back(x);
		}
		T& top()
		{
			return c.back();
		}
		void pop()
		{
			c.pop_back();
		}
		bool empty()const
		{
			return c.empty();
		}
	private:
		vector<T> c;
	};
}

void main()
{
	fj::stack<int> st;
	for (int i = 1; i <= 5; ++i)
		st.push(i);
	while (! st.empty())
	{
		int val = st.top();
		st.pop();
		cout << val << " 出栈." << endl;
	}
}

/*
namespace fj
{
	template<class T>
	class stack
	{
	public:
		stack(int sz = STACK_DEFAULT_SIZE)
		{
			_capacity = sz > STACK_DEFAULT_SIZE ? sz : STACK_DEFAULT_SIZE;
			_base = new T[_capacity];
			_top = 0;
		}
		~stack()
		{
			if (_base)
			{
				delete []_base;
				_capacity = _top = 0;
			}
		}
	public:
		void push(const T &x)
		{
			if (_top >= _capacity)
				return;
			_base[_top++] = x;
		}
		void pop()
		{
			if (_top == 0)
				return;
			_top--;
		}
		T& top()const
		{
			assert(_top != 0);
			return _base[_top - 1];
		}
		bool empty()const
		{
			return _top == 0;
		}

	private:
		enum{STACK_DEFAULT_SIZE=8};
		T *_base;
		size_t _capacity;
		size_t _top;
	};
}

void main()
{
	fj::stack<int> st;
	for (int i = 1; i <= 5; ++i)
		st.push(i);
	while (!st.empty())
	{
		int val = st.top();
		st.pop();
		cout << val << " 出栈." << endl;
	}
	
}

/*
void main()
{
	array<int, 10> ar = {1,2,3,4,5,6,7,8,9,10};
}

/*
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{}
public:
	bool operator<(const Date &dt)const
	{
		return (_year < dt._year)
			|| (_year == dt._year&&_month < dt._month)
			|| (_year == dt._year&&_month == dt._month&&_day < dt._day);
	}

public:
	int _year;
	int _month;
	int _day;
};

void main()
{
	priority_queue<Date> pq;
	pq.push(Date(2020, 1, 1));
	pq.push(Date(2020, 5, 10));
	pq.push(Date(2019, 1, 1));
	pq.push(Date(2019, 10, 10));

	Date dt = pq.top();
	cout << dt._year << "-" << dt._month << "-" << dt._day << endl;
}

/*
void main()
{
	vector<int> v{ 3, 2, 7, 6, 0, 4, 1, 9, 8, 5 };
	priority_queue<int,vector<int>,greater<int>> pq;
	for (const auto &e : v)
		pq.push(e);

	cout << "top=" << pq.top() << endl;
	while (!pq.empty())
	{
		int val = pq.top();
		pq.pop();
		cout << val << " 出堆." << endl;
	}
}

/*
void main()
{
	queue<char> Q;
	Q.push('A');
	Q.push('B');
	Q.push('C');
	Q.push('D');
	Q.push('E');
	Q.push('F');

	cout << "size=" << Q.size() << endl;
	cout << "flont=" << Q.front() << endl;
	cout << "back=" << Q.back() << endl;

	while (!Q.empty())
	{
		char val = Q.front();
		Q.pop();
		cout << val << "出队." << endl;
	}
}

/*
void main()
{
	stack<char>st;
	st.push('A');
	st.push('B');
	st.push('C');
	st.push('D');
	st.push('E');
	st.push('F');

	cout << "size=" << st.size() << endl;
	cout << "top=" << st.top() << endl;

	while (!st.empty())
	{
		char val = st.top();
		st.pop();
		cout << val << "出栈" << endl;
	}
}
*/