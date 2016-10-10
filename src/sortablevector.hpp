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
#include "stack.hpp"
#include "vector.hpp"

template<typename T,size_t initCapacity=1024>
class SortableVector:public Vector<T,initCapacity>{
	typedef int(*VoidComparer)(const void*,const void*);
	typedef int(*Comparer)(const T&,const T&);
	public:
	void qSort(VoidComparer compare=compareWarper<T,defaultCompare<T> >){
		qsort(this->buffer,this->size,sizeof *(this->buffer),compare);
	}
	ptrdiff_t bSearch(T v,VoidComparer compare=compareWarper<T,defaultCompare<T> >){
		void *ptr=bsearch(&v,this->buffer,this->size,sizeof *(this->buffer),compare);
		if(ptr==NULL){
			return -1;
		}
		return static_cast<const T*>(ptr)-this->buffer;
	}
	bool sorted(Comparer compare=defaultCompare<T>){
		for(ptrdiff_t i=0;i<this->size-1;i++){
			if(compare(this->buffer[i],this->buffer[i+1])>0){
				return false;
			}
		}
		return true;
	}
	ptrdiff_t binarySearch(T v,Comparer compare=defaultCompare<T>){
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
	ptrdiff_t binaryFind(T v,Comparer compare=defaultCompare<T>){
		ptrdiff_t result=binarySearch(v,compare);
		if(result>=this->size){
			return -1;
		}
		return (this->buffer[result]==v)?result:-1;
	}
	private:
	enum MergeSortTaskType{MERGE,MERGESORT};
	struct MergeSortTask{
		MergeSortTaskType type;
		ptrdiff_t from,to,mid;
	};
	void merge(ptrdiff_t from,ptrdiff_t to,ptrdiff_t mid,Comparer compare=defaultCompare<T>){
		T* tmp=new T[to-from];
		ptrdiff_t left=from,right=mid,neo=0;
		while(left<mid&&right<to){
			if(compare(this->buffer[left],this->buffer[right])<=0){
				tmp[neo]=this->buffer[left];
				left++;
			}else{
				tmp[neo]=this->buffer[right];
				right++;
			}
			neo++;
		}
		while(left<mid){
			tmp[neo]=this->buffer[left];
			left++;
			neo++;
		}
		while(right<to){
			tmp[neo]=this->buffer[right];
			right++;
			neo++;
		}
		for(ptrdiff_t i=from;i<to;i++){
			this->buffer[i]=tmp[i-from];
		}
		delete[] tmp;
	}
	public:
	void mergeSort(Comparer compare=defaultCompare<T>){
		Stack<MergeSortTask> tasks;
		tasks.push({MERGESORT,0,this->size,0});
		while(!tasks.isEmpty()){
			MergeSortTask task=tasks.pop();
			if(task.type==MERGE){
				merge(task.from,task.to,task.mid,compare);
			}else{
				if(task.to-task.from>1){
					ptrdiff_t mid=(task.from+task.to)>>1;
					tasks.push({MERGE,task.from,task.to,mid});
					tasks.push({MERGESORT,task.from,mid,0});
					tasks.push({MERGESORT,mid,task.to,0});
				}
			}
		}
	}
};

#endif //SORTABLEVECTOR_HPP