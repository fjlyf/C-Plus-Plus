#define _CRT_SECURE_N0_WARNINGS
#include<iostream>
#include<string>
using namespace std;
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
