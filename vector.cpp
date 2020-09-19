#define _CRT_SECURE_N0_WARNINGS
#include<iostream>
#include<vector>
using namespace std;

namespace fj
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
	public:
		vector() :_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{}
		~vector()
		{
			if (_start)
				delete[]_start;
			_start = _finish = _end_of_storage = nullptr;
		}
	public:
		iterator begin()const
		{
			return _start;
		}
		iterator end()const
		{
			return _finish;
		}
	public:
		size_t size()const
		{
			return _finish - _start;
		}
		size_t capacity()const
		{
			return _end_of_storage - _start;
		}
		bool empty()const
		{
			return _start == _finish;
		}
	public:
		iterator insert(iterator pos, const T &x)
		{
			if (size() >= capacity())
			{
				//À©ÈÝ
			}
			iterator end = _finish;
			while (end > pos)
			{
				*end = *(end - 1);
				end--;
			}
			*pos = x;
			++_finish;
			return pos;
		}
	public:
		//À©ÈÝ
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t old_sz = size();
				T *new_start = new T[n];
				for (int i = 0; i< old_sz; ++i)
					new_start[i] = _start[i];
				delete[]_start;
				_start = new_start;
				_finish = _start + old_sz;
				_end_of_storage = _start + n;
			}
		}
	private:
		iterator _start;              //ÆðÊ¼Î»ÖÃ
		iterator _finish;             //Ä©Î²Î»ÖÃ
		iterator _end_of_storage;     //ÈÝÁ¿
	};
}


void main()
{
	fj::vector<int> iv;
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

	iv.reserve(10);
	iv.insert(iv.begin(), 1);
	cout << "size=" << iv.size() << endl;
	cout << "capacity=" << iv.capacity() << endl;

}