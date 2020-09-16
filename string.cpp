#define _CRT_SECURE_N0_WARNINGS
#include<iostream>
#include<string>
using namespace std;

namespace fj
{
	class string
	{
	public:

	private:
		friend ostream& operator<<(ostream& _cout, const fj::string& s);
		friend istream& operator>>(istream& _cin, fj::string& s);
	private:
		char* _str;
		size_t _capacity;
		size_t _size;
	};
}

/*
void main()
{
	string str;
	str.push_back(' ');
	str.append("hello ");
	str += 'm';
	str += "hx";
	cout << str << endl;
	cout << str.c_str() << endl;
	string file("string.cpp");
	size_t pos = file.rfind('.');
	string suffix(file.substr(pos, file.size() - pos));
	cout << suffix << endl;
	string ur1("http://www.cplusplus.com/reference/string/find/");
	cout << ur1 << endl;
	size_t start = ur1.find("://");
	if (start == string::npos)//npos是string里的一个静态变量（static const size_t npos=-1）
	{
		cout << "invalid ur1" << endl;
		return;
	}
	start += 3;
	size_t finish = ur1.find('/', start);
	string address = ur1.substr(start, finish - start);
	cout << address << endl;
	pos = ur1.find("://");
	ur1.erase(0, pos + 3);
	cout << ur1 << endl;
}

/*
void main()
{
	string s("hello mhx");
	//遍历
	//1.for+operator[]
	for (size_t i = 0; i < s.size(); ++i)
		cout << s[i]<<endl ;
	//2.迭代器
	string::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << endl;
		++it;
	}
	string::reverse_iterator rit = s.rbegin();
	while (rit != s.rend())
	{
		cout << *rit << endl;
		++rit;
	}
	
	//3.范围for
	for (auto ch : s)
		cout << ch << endl;
}

/*
void main()
{
	string s("hello mhx");
	const string s1("hello mhx");
	cout << s << " " << s1 << endl;
	cout << s[0] << " " << s1[0] << endl;
	s[0] = 'h';
	cout << s << endl;
}

/*
void main()
{
	string s;
	s.reserve(100);
	size_t sz = s.capacity();
	cout << s.capacity() << endl;
	cout << "making s grow;\n";
	for (int i = 0; i < 100; ++i)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed:" << sz << '\n';
		}
	}
	s.~basic_string();
	cout << s.capacity() << endl;
}

/*
//容量改变
void main()
{
	string s;
	size_t sz = s.capacity();
	cout << "making s grow;\n";
	for (int i = 0; i < 100; ++i)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed:" << sz << '\n';
		}
	}
}

/*
void main()
{
	string s("hello mhx");
	cout << s.size() << endl;
	cout << s.length() << endl;
	cout << s.capacity() << endl;
	cout << s << endl;
	s.clear();
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	cout << s << endl;
	s.resize(10, 'a');
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	cout << s << endl;
	s.resize(5);
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	cout << s << endl; 
	s.reserve(100);
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	s.reserve(50);
	cout << s.size() << endl;
	cout << s.capacity() << endl;
}

/*
//构造string类
void main()
{
	string s1;
	string s2("hello mhx");
	string s3(s2);
}

/*
namespace fj
{
	class string
	{
	public:
		string(const char *str = "")
		{
			if (str == nullptr)
			{
				_str = new char[1];
				_str[0] = '\0';
				_capacity = _size = 0;
			}
			else
			{
				_capacity = _size = strlen(str);
				_str = new char[_capacity + 1];
				strcpy(_str, str);
			}
		}
		~string()
		{
			if (_str)
			{
				delete[]_str;
				_str = nullptr;
				_capacity = _size = 0;
			}
		}
	private:
		char *_str;
		size_t _capacity;
		size_t _size;
	};
}

void main()
{
	fj::string str("abc");
}

/*
void main()
{
	string s("hello bit!!!");
	cout << s.size() << endl;
	cout << s.length() << endl;
	cout << s.capacity() << endl;
	cout << "str=" << s << endl;
}

/*
void main()
{
	string s1;
	string s2("hello bit");
	string s3(s2);
}
	*/