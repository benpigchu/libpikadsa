/*
 * Vector with sort operation
 *
 * Notice: sort first before other operation
 *
 */

#ifndef SORTABLEVECTOR_HPP
#define SORTABLEVECTOR_HPP
#include <cstdlib>
#include <cstddef>
#include "compare.hpp"
#include "vector.hpp"

template<typename T,size_t initCapacity=1024>
class SortableVector:public Vector<T,initCapacity>{
	public:
	void qSort(int(*compare)(const void*,const void*)=compareWarper<T,defaultCompare<T> >){
		qsort(this->buffer,this->size,sizeof *(this->buffer),compare);
	}
	ptrdiff_t bSearch(T v,int(*compare)(const void*,const void*)=compareWarper<T,defaultCompare<T> >){
		void *ptr=bsearch(&v,this->buffer,this->size,sizeof *(this->buffer),compare);
		if(ptr==NULL){
			return -1;
		}
		return static_cast<const T*>(ptr)-this->buffer;
	}
	bool sorted(int(*compare)(const T&,const T&)=defaultCompare<T>){
		for(ptrdiff_t i=0;i<this->size-1;i++){
			if(compare(this->buffer[i],this->buffer[i+1])>0){
				return false;
			}
		}
		return true;
	}
	ptrdiff_t binarySearch(T v,int(*compare)(const T&,const T&)=defaultCompare<T>){
		ptrdiff_t l=0;
		ptrdiff_t r=this->size;
		while(r-l>0){
			ptrdiff_t mid=(l+r)>>1;
			if(compare(this->buffer[mid],v)<0){
				l=mid+1;
			}else{
				r=mid;
			}
		}
		return l;
	}
	ptrdiff_t binaryFind(T v,int(*compare)(const T&,const T&)=defaultCompare<T>){
		ptrdiff_t result=binarySearch(v,compare);
		if(result>=this->size){
			return -1;
		}
		return (this->buffer[result]==v)?result:-1;
	}
};

#endif //SORTABLEVECTOR_HPP