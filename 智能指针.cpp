#include<iostream>
#include<vld.h>
#include<string>
#include<memory>
#include<thread>
#include<mutex>
using namespace std;

template<typename T>
class LASingletonTemplateBase
{
private:
	static T* sm_instance;
protected:
	LASingletonTemplateBase()
	{
		assert(sm_instance == 0);
		sm_instance = static_cast<T*>(this);
	}
	virtual ~LASingletonTemplateBase()
	{
		assert(sm_instance != 0);
		sm_instance = 0;
	}

public:
	static T* get_instance_ptr()
	{
		if (sm_instance == 0)
		{
			sm_instance = new T();
		}
		return sm_instance;
	}

	static T& get_instance_ref()
	{
		if (sm_instance == 0)
		{
			sm_instance = new T();
		}
		return *sm_instance;
	}

	static void remove_instance()
	{
		assert(sm_instance);
		if (sm_instance)
		{
			delete sm_instance;
		}
		assert(sm_instance == 0);
	}
};

template<typename T>
T* LASingletonTemplateBase<T>::sm_instance = 0;

class Test
{};

/*
mutex mt;

//懒汉模式
class Test
{
public:
	static Test* CreateInstance()
	{
		if(_instance == nullptr)   //双检机制
		{
			mt.lock();
			if(_instance == nullptr)
			{
				_instance = new Test;
			}
			mt.unlock();
		}
		
		return _instance;
	}
protected:
	Test()
	{
		cout<<"Test::Test()"<<endl;
	}
private:
	static Test *_instance;
};

Test* Test::_instance = nullptr;

void thread_fun()
{
	for(int i=0; i<10; ++i)
	{
		Test *pt = Test::CreateInstance();
		printf("pt = %p\n", pt);
	}
}

void main()
{
	thread t1(thread_fun);
	thread t2(thread_fun);
	
	t1.join();
	t2.join();
}

/*
//饿汉模式
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		return &m_instance;
	}
private:
	// 构造函数私有
	Singleton(){};
	// C++98 防拷贝
	Singleton(Singleton const&);
	Singleton& operator=(Singleton const&);
private:
	static Singleton m_instance;
};
Singleton Singleton::m_instance;  //使用的非常频繁非常多

void main()
{
	//....
	int a = 10;
}

/*
class Test
{
public:
	static Test* CreateInstance()
	{
		if(_instance == nullptr)
		{
			_instance = new Test;
		}
		return _instance;
	}
protected:
	Test()
	{}
private:
	static Test *_instance;
};

Test* Test::_instance = nullptr;

void main()
{
	Test *pt = Test::CreateInstance();
	Test *pt1 = Test::CreateInstance();
	Test *pt2 = Test::CreateInstance();
	Test *pt3 = Test::CreateInstance();
	Test *pt4 = Test::CreateInstance();
	Test *pt5 = Test::CreateInstance();
}

/*
class Test
{
public:
	Test(int data = 0) : m_data(data)
	{}
private:
	int  m_data = 0;
};

void main()
{
	Test t1;
	Test t2;
	Test t3 = t2;
}


/*
#include<boost/noncopyable.hpp>
using namespace boost;

class Base final
{
};

class D : public Base
{};

void main()
{
	D d;
}

/*
class Test : noncopyable
{
public:
	Test(int data = 0) : m_data(data)
	{}
private:
	int  m_data = 0;
};

void main()
{
	Test t(1);
	Test t1;
	Test t2;

	Test t3;
	//t3 = t;
	//Test t4 = t3;
}

/*
class Test
{
public:
	Test(int data = 0) : m_data(data)
	{}
private:
	Test(const Test&);
	Test& operator=(const Test &t);
private:
	int  m_data = 0;
};

void main()
{
	Test t(1);
	Test t1;
	Test t2;

	Test t3;
	t3 = t;
}

/*
//只能在栈上创建对象  方法二
class Test
{
public:
	Test(int data = 0) : m_data(data)
	{}
	Test(const Test &);
private:
	void* operator new(size_t sz);
	void* operator new(size_t sz, int pos);
private:
	int  m_data = 0;
};

void main()
{
	Test t;
	Test *pt = new Test;   //new operator    operator new
}

/*
//只能在栈上创建对象  方法一
class Test
{
public:
	static Test& CreateInstance(int data = 0)
	{
		return Test(data);
	}
private:
	Test(int data = 0) : m_data(data)
	{}
	Test(const Test &);
private:
	int  m_data = 0;
};

void main()
{
	Test &pt = Test::CreateInstance();
	Test *pt = new Test;
}


/*
//只能在堆上创建
class Test
{
public:
	static Test* CreateInstance(int data = 0)
	{
		return new Test(data);
	}
private:
	Test(int data = 0) :m_data(data)
	{}
	Test(const Test &);
private:
	int  m_data = 0;
};

void main()
{
	Test *pt = Test::CreateInstance();
	//Test t = *pt;
}

/*
//#include<boost/smart_ptr.hpp>
//using namespace boost;

struct listNode
{
	int data;
	std::weak_ptr<listNode> prev;
	std::weak_ptr<listNode> next;
	listNode()
	{
		cout<<"listNode::listNode()"<<endl;
	}
	~listNode()
	{
		cout<<"listNode::~listNode()"<<endl;
	}
};

//定制删除器  函数
void Del(listNode *pn)
{
	cout<<"Del pn"<<endl;
	delete []pn;
}

void DelMalloc(int *pn)
{
	cout<<"DelMalloc pn"<<endl;
	delete []pn;
}

void main()
{
	listNode *pa = new listNode[5];
	shared_ptr<listNode> spa(pa, Del);       //delete _px;

	int *ptr = (int*)malloc(sizeof(int)*10);
	shared_ptr<int> spa1(ptr, DelMalloc);
}

/*
struct listNode
{
	int data;
	//shared_ptr<listNode> prev;
	//shared_ptr<listNode> next;

	weak_ptr<listNode> prev;
	weak_ptr<listNode> next;

	~listNode()
	{
		cout<<"listNode::~listNode()"<<endl;
	}
};

void main()
{
	shared_ptr<listNode> node1(new listNode);
	shared_ptr<listNode> node2(new listNode);

	cout<<"node1 use_count = "<<node1.use_count()<<endl;
	cout<<"node2 use_count = "<<node1.use_count()<<endl;

	node1->next = node2;
	node2->prev = node1;

	cout<<"node1 use_count = "<<node1.use_count()<<endl;
	cout<<"node2 use_count = "<<node1.use_count()<<endl;

}
	

/*
template<class T>
class Shared_Ptr
{
public:
	Shared_Ptr(T *_P = 0) : _Ptr(_P), _UseCount((size_t*)new int(1)),_Mutex(new mutex)
	{}
	Shared_Ptr(const Shared_Ptr<T> &_Y) 
		: _Ptr(_Y._Ptr),_UseCount(_Y._UseCount),_Mutex(_Y._Mutex)
	{
		Increment();
	}
	Shared_Ptr<T>& operator=(const Shared_Ptr<T> &_Y)
	{
		if(this != &_Y)
		{
			//释放资源
			Decrement();
			_Ptr = _Y._Ptr;
			_UseCount = _Y._UseCount;
			Increment();
		}
		return *this;
	}
	~Shared_Ptr()
	{
		Decrement();
	}
public:
	T& operator*()const
	{
		return *_Ptr;
	}
	T* operator->()const
	{
		return _Ptr;
	}
	void reset(T *_P = 0)
	{
		if(_Ptr != _P)
			Decrement();
		_Ptr = _P;
		_UseCount = (size_t*)new int(1);
	}
public:
	size_t use_count()const
	{
		return *_UseCount;
	}
	bool unique()const
	{
		return (use_count() == 1);
	}
public:
	void Increment()
	{
		_Mutex->lock();
		++*_UseCount;   //临界区
		_Mutex->unlock();
	}
	void Decrement()
	{
		bool delete_flag = false;
		_Mutex->lock();
		if(--*_UseCount == 0)
		{
			delete _Ptr;
			delete _UseCount;
			delete_flag = true;
		}
		_Mutex->unlock();
		if(delete_flag)
			delete _Mutex;
	}
private:
	T *_Ptr;
	size_t *_UseCount;
	mutex *_Mutex;
};


class Date
{
public:
	Date() : year(0),month(0),day(0)
	{}
public:
	int year;
	int month;
	int day;
};

mutex mt;
void SharePtrFunc(Shared_Ptr<Date>& sp, size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		Shared_Ptr<Date> copy(sp);
		mt.lock();
		copy->year++;
		copy->month++;
		copy->day++;
		mt.unlock();
	}
}

void main()
{
	Shared_Ptr<Date> sp(new Date);

	const size_t n = 10000000;
	thread t1(SharePtrFunc, sp, n);
	thread t2(SharePtrFunc, sp, n);
	t1.join();
	t2.join();
	cout << sp->year << endl;
	cout << sp->month << endl;
	cout << sp->day << endl;
}

/*
void thread_fun(Shared_Ptr<int> &sp, int n)
{
	for(int i=0; i<n; ++i)
	{
		cout<<"use_count = "<<sp.use_count()<<endl;
		Shared_Ptr<int> copy(sp);
		cout<<"use_count = "<<sp.use_count()<<endl;
	}
	cout<<"use_count = "<<sp.use_count()<<endl;
}



void main()
{
	int n = 2;
	int *p = new int(100);

	Shared_Ptr<int> sp(p);

	thread th1(thread_fun, sp, n);
	thread th2(thread_fun, sp, n);

	cout<<"sp use_count ="<<sp.use_count()<<endl;

	th1.join();
	th2.join();
}

/*
void main()
{
	int *p = new int(100);
	int *q = new int(200);
	int *x = new int(1);
	Shared_Ptr<int> sp(p);
	cout<<"*sp = "<<*sp<<endl;
	cout<<"use_count = "<<sp.use_count()<<endl;
	Shared_Ptr<int> sp1 = sp;
	cout<<"use_count = "<<sp.use_count()<<endl;

	{
		Shared_Ptr<int> sp2 = sp1;
		cout<<"use_count = "<<sp.use_count()<<endl;
	}
	cout<<"use_count = "<<sp.use_count()<<endl;


	Shared_Ptr<int> sp2(q);
	Shared_Ptr<int> sp3(sp2);

	sp2 = sp1;

	sp3.reset(x);
}
*/
/*
#include<iostream>
#include<vld.h>
#include<string>
#include<memory>
using namespace std;

template<class T>
class Shared_Ptr
{
public:
	Shared_Ptr(T *_P = 0) : _Ptr(_P), _UseCount((size_t*)new int(1))
	{}
	Shared_Ptr(const Shared_Ptr<T> &_Y) : _Ptr(_Y._Ptr),_UseCount(_Y._UseCount)
	{
		Increment();
	}
	Shared_Ptr<T>& operator=(const Shared_Ptr<T> &_Y)
	{
		if(this != &_Y)
		{
			//释放资源
			Decrement();
			_Ptr = _Y._Ptr;
			_UseCount = _Y._UseCount;
			Increment();
		}
		return *this;
	}
	~Shared_Ptr()
	{
		Decrement();
	}
public:
	T& operator*()const
	{
		return *_Ptr;
	}
	T* operator->()const
	{
		return _Ptr;
	}
	void reset(T *_P = 0)
	{
		if(_Ptr != _P)
			Decrement();
		_Ptr = _P;
		_UseCount = (size_t*)new int(1);
	}
public:
	size_t use_count()const
	{
		return *_UseCount;
	}
	bool unique()const
	{
		return (use_count() == 1);
	}
public:
	void Increment()
	{
		++*_UseCount;
	}
	void Decrement()
	{
		if(--*_UseCount == 0)
		{
			delete _Ptr;
			delete _UseCount;
		}
	}
private:
	T *_Ptr;
	size_t *_UseCount;
};

void main()
{
	int *p = new int(100);
	int *q = new int(200);
	int *x = new int(1);
	Shared_Ptr<int> sp(p);
	cout<<"*sp = "<<*sp<<endl;
	cout<<"use_count = "<<sp.use_count()<<endl;
	Shared_Ptr<int> sp1 = sp;
	cout<<"use_count = "<<sp.use_count()<<endl;


	Shared_Ptr<int> sp2(q);
	Shared_Ptr<int> sp3(sp2);

	sp2 = sp1;

	sp3.reset(x);
}

/*
void main()
{
	int *p = new int(10);
	shared_ptr<int> sp;
	cout<<"use_count = "<<sp.use_count()<<endl;
	sp.reset(p);
	cout<<"*sp = "<<*sp<<endl;
	cout<<"use_count = "<<sp.use_count()<<endl;

	weak_ptr<int> wp = sp;
	cout<<"use_count = "<<sp.use_count()<<endl;

	shared_ptr<int> sp1;
	sp1 = sp;
	cout<<"use_count = "<<sp.use_count()<<endl;

	weak_ptr<int> wp1 = wp; //弱指针： * ->
	//cout<<*wp<<endl;

	cout<<"wp_use_count = "<<wp.use_count()<<endl;
	
}

/*
void main()
{
	int *p = new int(10);
	unique_ptr<int> sp(p);
	cout<<"*sp = "<<*sp<<endl;

	unique_ptr<int> sp1;
	sp1 = sp;
}

/*
void main()
{
	int *p = new int(10);
	shared_ptr<int> sp;
	cout<<"use_count = "<<sp.use_count()<<endl;
	sp.reset(p);
	cout<<"*sp = "<<*sp<<endl;
	cout<<"use_count = "<<sp.use_count()<<endl;

	shared_ptr<int> sp1 = sp;
	cout<<"use_count = "<<sp.use_count()<<endl;

	if(sp.unique())
		cout<<"is unique."<<endl;
	else
		cout<<"is not unique."<<endl;

}

/*
#include<boost/smart_ptr.hpp>
using namespace boost;

void main()
{
	int *p = new int(10);
	boost::shared_ptr<int> sp(p);

	cout<<"*sp = "<<*sp<<endl;
	cout<<"use_count = "<<sp.use_count()<<endl;

	boost::shared_ptr<int> sp1 = sp;
	cout<<"use_count = "<<sp.use_count()<<endl;

	{
		boost::shared_ptr<int> spx = sp;
		cout<<"use_count = "<<sp.use_count()<<endl;
	}
	cout<<"use_count = "<<sp.use_count()<<endl;


	boost::shared_ptr<int> sp2;
	sp2 = sp1;
	cout<<"use_count = "<<sp.use_count()<<endl;
}

/*
namespace bit
{
	template<class T>
	class scoped_ptr 
	{
		 typedef scoped_ptr<T> this_type;
	public:
		explicit scoped_ptr(T * p = 0) : px(p) 
		{}
		~scoped_ptr() // never throws
		{
			delete px;
		}
	public:
		void reset(T * p = 0) // never throws
		{
			this_type(p).swap(*this);
		}
		void swap(scoped_ptr & b) // never throws
		{
			T * tmp = b.px;
			b.px = px;
			px = tmp;
		}
	public:
		T & operator*() const 
		{
			return *px;
		}
		T * operator->() const 
		{
			return px;
		}
		T * get() const 
		{
			return px;
		}
	private:
		scoped_ptr(scoped_ptr const &);
		scoped_ptr & operator=(scoped_ptr const &);
		void operator==(scoped_ptr const&) const;
		void operator!=(scoped_ptr const&) const;
	private:
		T * px;
	};

	template<class T> 
	class scoped_array
	{
		typedef scoped_array<T> this_type;
	public:
		explicit scoped_array( T * p = 0 ) : px( p ) 
		{}
		~scoped_array() // never throws
		{
			delete []px;
		}
	public:
		T & operator[](size_t i) const
		{
			return px[i];
		}
	private:
		T * px;

		scoped_array(scoped_array const &);
		scoped_array & operator=(scoped_array const &);
		void operator==(scoped_array const&) const;
		void operator!=(scoped_array const&) const;
	};
};

void main()
{
	int *p = new int[10]{1,2,3,4,5,6,7,8,9,10};
	bit::scoped_array<int> sp(p);
	for(int i=0; i<10; ++i)
		cout<<sp[i]<<" ";
	cout<<endl;
}

/*
void main()
{
	int *p = new int(10);
	int *q = new int(20);

	bit::scoped_ptr<int> sp(p);  //不允许拥有权发生转移
	cout<<"*sp = "<<*sp<<endl;

	sp.reset(q);
	cout<<"*sp = "<<*sp<<endl;
}

/*
void main()
{
	int *p = new int(10);
	bit::scoped_ptr<int> sp(p);  //不允许拥有权发生转移
	cout<<"*sp = "<<*sp<<endl;

	bit::scoped_ptr<string> sp1(new string("HelloBoost"));
	cout<<sp1->size()<<endl;

	//bit::scoped_ptr<int> sp2 = sp;
	//sp2 = sp;
}

/*
namespace bit
{
	template<class _Ty>
	class auto_ptr
	{
		typedef auto_ptr<_Ty> _Myt;
	public:
		explicit auto_ptr(_Ty *_Ptr = 0) : _Myptr(_Ptr)
		{}
		auto_ptr(_Myt& _Right) : _Myptr(_Right.release())
		{}
		_Myt& operator=(_Myt& _Right)
		{
			if(this != &_Right)
				reset(_Right.release());
			return (*this);
		}
		~auto_ptr()
		{	
			delete _Myptr;
		}
	public:
		_Ty& operator*() const
		{	
			return (*get());
		}
		_Ty *operator->() const 
		{	
			return (get());
		}
		_Ty *get() const
		{	
			return (_Myptr);
		}
	public:
		_Ty *release() 
		{	
			_Ty *_Tmp = _Myptr;
			_Myptr = 0;
			return (_Tmp);
		}
		void reset(_Ty *_Ptr = 0)
		{
			if (_Ptr != _Myptr)
				delete _Myptr;
			_Myptr = _Ptr;
		}
	private:
		_Ty *_Myptr;
	};
};

void main()
{
	int *p = new int[10];
	bit::auto_ptr<int> ap(p);
}

/*
void main()
{
	int *p = new int(10);
	int *q = new int(100);

	bit::auto_ptr<int> ap(p);  //RAII
	cout<<"*ap = "<<*ap<<endl;
	ap.reset(q);

	bit::auto_ptr<int> ap1;
	ap1 = ap;
}

/*
void main()
{
	int *p = new int(10);
	bit::auto_ptr<int> ap(p);  //RAII
	cout<<"*ap = "<<*ap<<endl;

	bit::auto_ptr<string> ap1(new string("abc"));
	cout<<ap1->size()<<endl;

	bit::auto_ptr<int> ap2 = ap;

}

//VC 6.0
/*
namespace bit
{
	template<class _Ty>
	class auto_ptr
	{
	public:
		auto_ptr(_Ty *_P=0) : _Owns(_P!=0), _Ptr(_P)
		{}
		auto_ptr(const auto_ptr<_Ty> &_Y):_Owns(_Y._Owns),_Ptr(_Y.release())
		{}
		auto_ptr<_Ty>& operator=(const auto_ptr<_Ty> &_Y)
		{
			if(this != &_Y)
			{
				if(_Ptr != _Y._Ptr)
				{
					if(_Owns)
						delete _Ptr;
					_Owns = _Y._Owns;
				}
				else if(_Y._Owns)
					_Owns = true;

				_Ptr = _Y.release();
			}
			return *this;
		}
		~auto_ptr()
		{
			if(_Owns)
				delete _Ptr;
		}
	public:
		_Ty& operator*()const
		{
			return *get();
		}
		_Ty* operator->()const
		{
			return get();
		}
		_Ty* get()const
		{
			return _Ptr;
		}
	public:
		//const auto_ptr<_Ty> * const this
		_Ty* release()const
		{
			((auto_ptr<_Ty> * const)this)->_Owns = false;

			_Ty *_Tmp = _Ptr;
			((auto_ptr<_Ty> * const)this)->_Ptr = nullptr;

			return _Tmp;
		}
	private:
		bool _Owns;
		_Ty *_Ptr;
	};
};

void main()
{
	int *p = new int(10);
	bit::auto_ptr<int> ap(p);  //RAII
	cout<<"*ap = "<<*ap<<endl;
	//ap.release();

	int *q = new int(20);
	bit::auto_ptr<int> ap1(q);
	ap1 = ap;
}


/*
void main()
{
	int *p = new int(10);
	bit::auto_ptr<int> ap(p);  //RAII
	cout<<"*ap = "<<*ap<<endl;

	bit::auto_ptr<int> ap1 = ap; //拥有权的转移问题 -->
	cout<<"*ap1 = "<<*ap1<<endl;
	//cout<<"*ap = "<<*ap<<endl;   //不想让其能够访问

	int *q = new int(20);
	bit::auto_ptr<int> ap2(q);
	ap2 = ap1;  //赋值
	cout<<"*ap2 = "<<*ap2<<endl;
}

/*
void main()
{
	int *p = new int(10);
	bit::auto_ptr<int> ap(p);  //RAII
	cout<<"*p = "<<*p<<endl;
	cout<<"*ap = "<<*ap<<endl;
	bit::auto_ptr<string> ap1(new string("Hello"));
	cout<<ap1->size()<<endl;
}
*/