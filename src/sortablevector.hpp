/*
 * Vector with sort operation
 *
 * Notice: sort first before other operation
 *
 */

#ifndef SORTABLEVECTOR_HPP
#define SORTABLEVECTOR_HPP
#include <cstdlib>
#include "vector.hpp"

template<typename T>
int defaultCompare(const void *a,const void *b){
	T av=*static_cast<const T*>(a);
	T bv=*static_cast<const T*>(b);
	if(av>bv){
		return 1;
	}
	if(av<bv){
		return -1;
	}
	return 0;
}

template<typename T>
int defaultRevesedCompare(const void *a,const void *b){
	T av=*static_cast<const T*>(a);
	T bv=*static_cast<const T*>(b);
	if(av<bv){
		return 1;
	}
	if(av>bv){
		return -1;
	}
	return 0;
}

template<typename T,size_t initCapacity=1024>
class SortableVector:public Vector<T,initCapacity>{
	public:
	void sort(int(*compare)(const void*,const void*)=defaultCompare<T>){
		qsort(this->buffer,this->size,sizeof *(this->buffer),compare);
	}
	size_t binarySearch(T v,int(*compare)(const void*,const void*)=defaultCompare<T>){
		void *ptr=bsearch(&v,this->buffer,this->size,sizeof *(this->buffer),compare);
		if(ptr==NULL){
			return -1;
		}
		return static_cast<const T*>(ptr)-this->buffer;
	}
};

#endif //SORTABLEVECTOR_HPP