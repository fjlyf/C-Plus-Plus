#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
using namespace std;

//继承
class Base
{
public:
	void show()
	{
		cout << "Base::show()" << endl;
	}
};
class A :public Base
{
public:
	void Print()
	{
		cout << "A::Print()" << endl;
	}
private:
	int m_a = 0;
};

void main()
{
	Base b;
	A a;
	b = a;
	a.show();
	a.Print();
}



/*
//赋值运算符重载
class Int;
ostream& operator<<(ostream &out,const Int &i);
istream& operator>>(istream &in, Int &i);

class Int
{
	friend ostream& operator<<(ostream &out, const Int &i);
	friend istream& operator>>(istream &in, Int &i);
public:
	Int(int i = 0) :m_i(i)
	{}
	~Int()
	{}
public:
	Int operator++(int) //后++
	{
		Int tmp = *this;
		//m_i++;
		++*this;
		return tmp;
	}
	Int& operator++()   //前++
	{
		m_i++;
		return *this;
	}
	Int operator--(int)
	{
		Int tmp = *this;
		//m_i--;
		--*this;
		return tmp;
	}
	Int& operator--()   
	{
		m_i--;
		return *this;
	}
public:
	Int operator+(const Int &i)
	{
		return Int(m_i + i.m_i);
	}
	Int operator-(const Int &i)
	{
		return Int(m_i - i.m_i);
	}
	Int operator*(const Int &i)
	{
		return Int(m_i * i.m_i);
	}
	Int operator/(const Int &i)
	{
		return Int(m_i / i.m_i);
	}
	Int operator%(const Int &i)
	{
		return Int(m_i % i.m_i);
	}
public:
	Int& operator+=(const Int &i)
	{
		m_i += i.m_i;
		return *this;
	}
	Int& operator-=(const Int &i)
	{
		m_i -= i.m_i;
		return *this;
	}
	Int& operator*=(const Int &i)
	{
		m_i *= i.m_i;
		return *this;
	}
	Int& operator/=(const Int &i)
	{
		m_i /= i.m_i;
		return *this;
	}
	Int& operator%=(const Int &i)
	{
		m_i %= i.m_i;
		return *this;
	}
public:
	Int operator>>(int offset)
	{
		return Int(m_i >> offset);
	}
	Int operator<<(int offset)
	{
		return Int(m_i << offset);
	}
	Int& operator>>=(int offset)
	{
		m_i >>= offset;
		return *this;
	}
	Int& operator<<=(int offset)
	{
		m_i <<= offset;
		return *this;
	}
public:
	bool operator==(const Int &i)
	{return m_i == i.m_i;}
	bool operator!=(const Int &i)
	{return !(*this==i);}
private:
	int m_i;
};

ostream& operator<<(ostream &out, const Int &i)
{
	out << i.m_i;
	return out;
}
istream& operator>>(istream &in, Int &i)
{
	in >> i.m_i;
	return in;
}

void main()
{
	Int a = 1;
	Int b = 2;
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	if (a == b)
		cout << "a==b" << endl;
	else
		cout << "a!=b" << endl;

}

/*
//重载为友元函数
class Complex;
Complex operator+(int real, const Complex &c);
ostream& operator<<(ostream &out, const Complex &c);
istream& operator>>(istream &in, Complex &c);
//复数
class Complex
{
	friend Complex operator+(int real, const Complex &c);
	friend ostream& operator<<(ostream &out, const Complex &c);
	friend istream& operator>>(istream &in, Complex &c);
public:
	Complex(int real = 0, int imag = 0) :m_real(real), m_imag(imag)
	{
		cout << "Create Complex obj:" << this << endl;
	}
	Complex(const Complex &c)
	{
		cout << "Copy Complex obj:" << this << endl;
		m_real = c.m_real;
		m_imag = c.m_imag;
	}
	Complex& operator=(const Complex &c)
	{
		cout << "Assign:" << this << endl;
		if (this != &c)
		{
			m_real = c.m_real;
			m_imag = c.m_imag;
		}
		return *this;
	}
	~Complex()
	{
		cout << "Free Complex obj:" << this << endl;
	}
public:
	void PrintComplex()const
	{
		cout << "(" << m_real << "," << m_imag << ")" << endl;
	}
public:
	//重载为成员方法
	Complex operator+(const Complex &c)
	{
		return Complex(this->m_real + c.m_real, this->m_imag + c.m_imag);
	}
	Complex operator+(int real)
	{
		return Complex(m_real + real, m_imag);
	}
private:
	int m_real;
	int m_imag;
};
Complex operator+(int real, const Complex &c)
{
	return Complex(real + c.m_real, c.m_real);
}
ostream& operator<<(ostream &out, const Complex &c)
{
	out <<"("<< c.m_real << "," << c.m_imag<<")";
	return out;
}
istream& operator>>(istream &in, Complex &c)
{
	in >> c.m_real >> c.m_imag;
	return in;
}
int main()
{
	Complex c1(1,2);
	Complex c2(3,4);
	cout << c1 << endl;
	Complex c;
	cin >> c;
	cout << c << endl;
}
/*
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date a;
	Date d(a);
	a = d;
	return 0;
}

/*
class A
{ 
public:    
	A(int a) 
		:_a1(a)
		, _a2(_a1)    
	{}        
	void Print() 
	{ 
		cout << _a1 << " " << _a2 << endl; 
	} 
private:   
	int _a2;    
	int _a1;
};

int main() 
{ 
	A aa(1);    //先初始化a2，初始化列表中初始化a2的方法为a2(a1),此时a1为随机值；在初始化a1,初始化列表中初始化a1的方法为a1(a),此时a的值为1。
	aa.Print(); //输出 1 随机值
}

/*
//拷贝构造函数
//拷贝构造函数是构造函数的一个重载形式
//拷贝构造函数的参数只有一个且必须使用引用传参，使用传值方式会引发无穷递归调用

class String
{
public:
	String(const char* str = "jack")
	{
		_str = (char*)malloc(strlen(str) + 1);
		strcpy(_str, str);
	}
	~String()
	{
		cout << "~String()" << endl;
		free(_str);
	}
private:
	char* _str;
};
int main()
{
	String s1("hello");
	String s2(s1);
	return 0;
}

/*
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		cout << "Date()" << endl;
		_year = year;
		_month = month;
		_day = day;
	}
	Date(const Date& d)//const修饰,引用传参
	{
		cout << "Date(const Date&)" << endl;
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	~Date()
	{
		cout << "~Date()" << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1;
	Date d2(d1);
	return 0;
}

/*
//析构函数
typedef int DateType;
class Seqlist
{
public:
	Seqlist(int capacity = 10)
	{
		_pDate = (DateType*)malloc(capacity * sizeof(DateType));
		assert(_pDate);
		_size = 0;
		_capacity = capacity;
	}
	~Seqlist()
	{
		cout << "~Seqlist()" << endl;
		if (_pDate)
		{
			free(_pDate);
			_pDate = NULL;
			_capacity = 0;
			_size = 0;
		}
	}
private:
	int* _pDate;
	size_t _size;
	size_t _capacity;
};
void main()
{
	Seqlist q1;
}

/*
//构造函数函数
//只有单个形参，该形参是对本类类型对象的引用(一般常用const修饰)，在用已存在的类类型对象 创建新对象时由编译器自动调用
class Date {
public:   
	Date()    
	{
		_year = 1900;      
		_month = 1;        
		_day = 1;
	}        
	Date(int year = 1900, int month = 1, int day = 1)    
	{
		_year = year; 
		_month = month;      
		_day = day;
	}

private:    
	int _year;  
	int _month;   
	int _day;
};

//无参的构造函数和全缺省的构造函数都称为默认构造函数，并且默认构造函数只能有一个。注意：无参 构造函数、全缺省构造函数、我们没写编译器默认生成的构造函数，都可以认为是默认成员函数。
int main()
{
	Date d1;//错误	2	error C2668: “Date::Date”: 对重载函数的调用不明确	
}

/*
class Date
{
public:
	Date()
	{}
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
private:
	int _year;
	int _month;
	int _day;
};
void main()
{
	Date d1;
	//Date d2(2015, 1, 1);
	Date d3;
}
/*
class Date
{
public:
	void SetDate(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	void Display()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1, d2;
	d1.SetDate(2020, 8, 1);
	d1.Display();
	//析构函数是一个特殊的成员函数，名字与类名相同，创建类类型对象时由编译器自动调用，保证每个数据成员都有一个合适的初始值，并且在对象的生命周期内只调用一次。
	//Date d2;
	d2.SetDate(2020, 8, 15);
	d2.Display();
	return 0;
}
/*
//this指针
class A
{
	friend class Date;
public:
	void PrintA()
	{
		cout << _a << endl;
	}
	void Show()
	{
		cout << "Show()" << endl;
	}
private:
	int _a;
};
int main()
{
	A* p = NULL;
	p->PrintA();
	p->Show();
}

class Date
{
	
public:
	void Display()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
	void SetDate(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
private:
	int _year;
	int _month;
	int _day;
};
/*
int main()
{
	Date d1, d2;
	d1.SetDate(2020, 8, 11);
	d2.SetDate(2020, 8, 10);
	d1.Display();
	d2.Display();
	return 0;
}

/*
//类与对象
class Person
{
public:
	void PrintPersonInfo()
	{
		cout << _name << "" << _gender << "" << _age << endl;
	}
private:
	char _name[20];
	char _gender[3];
	int _age;
};

class A
{
public:
	void PrintA()
	{
		cout << _a << endl;
	}
private:
	char _a;
};

//类中既有成员变量，又有成员函数
class A1
{
public:
	void f1(){}
private:
	int _a;
};

//类中仅有成员函数
class A2
{
public:
	void f2(){}
};

//类中什么也没有（空类）
class A3
{};

/*

struct Student
{
	void SetStudentInfo(const char* name, const char* gender, int age)
	{
		strcpy(_name, name);
		strcpy(_gender, gender);
		_age = age;
	}
	void PrintStudentInfo()
	{
		cout << _name << " " << _gender << " " << _age << endl;
	}

	char _name[20];
	char _gender[3];
	int _age;
};

int main()
{
	Student s;
	s.SetStudentInfo("Peter", "男", 18);
	s.PrintStudentInfo();
	return 0;
}


/*
//指针空值
void TestPtr()
{
	int* p1 = NULL;
	int* p2 = 0;
}
void f(int)
{
	cout << "f(int)" << endl;
}
void f(int*)
{
	cout << "f(int*)" << endl;
}

int main()
{
	f(0);
	f(NULL);
	f((int*)NULL);
	return 0;
}

/*
//for循环
void TestFor()
{
	int array[] = { 1, 2, 3, 4, 5 };
	for (auto& e:array)
		e *= 2;
	for (auto e:array)
		cout << e << " ";
}
int main()
{
	TestFor();
	return 0;
}
/*
void TestFor()
{
	int array[] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
		array[i] *= 2;
	for (int* p = array; p < array + sizeof(array) / sizeof(array[0]); ++p)
		cout << *p << endl;
}

/*
//auto关键字
int main()
{
	int x = 10;
	auto a = &x;
	auto* b = &x;
	auto& c = x;
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;

	*a = 20;
	*b = 30;
	c = 40;
	return 0;
}

/*
int TestAuto()
{
	return 10;
}

int main()
{
	int a = 10;
	auto b = a;
	auto c = 'a';
	auto d = TestAuto();
	//typeid().name()用于输出变量类型
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;
	cout << typeid(d).name() << endl;

	return 0;
}

/*
//传值引用
#include<time.h>
struct A
{
	int a[10000];
};
void TestFunc1(A a)
{
}
void TestFunc2(A& a)
{
}
void TestRefandvalue()
{
	A a;
	//以值作为函数参数
	size_t begin1 = clock();
	for (size_t i = 0; i < 10000; ++i)
		TestFunc1(a);
	size_t end1 = clock();

	//以引用作为函数参数
	size_t begin2 = clock();
	for (size_t i = 0; i < 10000; ++i)
		TestFunc2(a);
	size_t end2 = clock();

	//分别计算两个函数运行结束后的时间
	cout << "TestFunc1(A)-time:" << end1 - begin1 << endl;
	cout << "TestFunc2(A&)-time:" << end2 - begin2 << endl;
}

int main()
{
	int a = 10;
	int& ra = a;
	ra = 20;
	int* pa = &a;
	*pa = 20;
	return 0;
	//cout << "&a=" << &a << endl;
	//cout << "&ra=" << &ra << endl;
	return 0;
}
/*
//引用
void TestRef()
{
	int a = 10;
	int& ra = a;
	printf("%p\n", &a);
	printf("%p\n", &ra);
}
//做参数引用
void Swap(int& left, int& right)
{
	int tmp = left;
	left = right;
	right = tmp;
}
//做返回值
int& Count()
{
	static int n = 0;
	n++;
	return n;
}
int& Add(int a, int b)
{
	int c = a + b;
	return c;
}

int main()
{
	int& ret = Add(1, 2);
	Add(3, 4);
	cout << "Add(1,2)is:" << ret << endl;
	return 0;
	//输出为7，因为Add(3,4)改变了原来的返回对象
}

/*
//重载
int Add(int left, int right)
{
	return left + right;
}
double Add(double left, double right)
{
	return left + right;
}
long Add(long left, long right)
{
	return left + right;
}
int main()
{
	Add(10, 20);
	Add(10.0, 20.0);
	Add(10L, 20L);

	return 0;
}
/*
//半缺省参数
void TestFunc1(int a, int b, int c =20)
{
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "c=" << c << endl;
}
int main()
{
	TestFunc1(1,4);
	TestFunc1(8,1);
}

/*
//缺省参数
void TestFunc(int a = 0)
{
	cout << a << endl;
}

int main()
{
	TestFunc();    //没有传参时，使用参数的默认值
	TestFunc(10);  //传参时，使用指定的实参
}

/*
int main()
{
	int a;
	double b;
	char c;
	cin >> a;
	cin >> b >> c;
	cout << a << endl;
	cout << b << " " << c << endl;
	return 0;
}

/*
int main()
{
	cout << "hello world" <<endl;
	return 0;
}
/*
namespace N1
{
	int a=1;
	int Add(int left, int right)
	{
		return left + right;
	}
}

namespace N2
{
	int a;
	int b;
	int Add(int left, int right)
	{
		return left + right;
	}
	namespace N3
	{
		int c;
		int d;
		int Sub(int left, int right)
		{
			return left + right;
		}
	}
}

namespace N1
{
	int Mul(int left, int right)
	{
		return left + right;
	}
}
#include<stdio.h>
using namespace N1;

int main()
{
	printf("%d\n",a);
	return 0;
}
*/