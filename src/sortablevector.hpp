/*
 * Vector with sort operation
 *
 * Notice: sort first before other operation
 *
 */

#ifndef SORTABLEVECTOR_HPP
#define SORTABLEVECTOR_HPP
#include <cstdlib>
#include "compare.hpp"
#include "vector.hpp"

template<typename T,size_t initCapacity=1024>
class SortableVector:public Vector<T,initCapacity>{
	public:
	void qSort(int(*compare)(const void*,const void*)=compareWarper<T,defaultCompare<T> >){
		qsort(this->buffer,this->size,sizeof *(this->buffer),compare);
	}
	size_t bSearch(T v,int(*compare)(const void*,const void*)=compareWarper<T,defaultCompare<T> >){
		void *ptr=bsearch(&v,this->buffer,this->size,sizeof *(this->buffer),compare);
		if(ptr==NULL){
			return -1;
		}
		return static_cast<const T*>(ptr)-this->buffer;
	}
};

#endif //SORTABLEVECTOR_HPP