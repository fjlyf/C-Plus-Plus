#ifndef _SEQ_LIST_H_
#define _SEQ_LIST_H_

#include"common.h"

template<class Type>
class SeqList
{
pubilc:
	SeqList(int sz = SEQLIST_DEFAULT_SIZE);
private:
	enum { SEQLIST_DEFAULT_SIZE = 20 };
private:
	Type * base;
	size_t capacity;
	size_t size;
};

////////////////////////////////////////////
//˳����ʵ��
template<class Type>
SeqList<Type>::SeqList(int sz)
{
	capacity = sz > SEQLIST_DEFAULT_SIZE ? sz : SEQLIST_DEFAULT_SIZE;
	base = new Type[capacity + 1];   //��һ���ռ���ʱ�����κ�����
	size = 0;
}


#endif /*_SEQ_LIST_H_*/