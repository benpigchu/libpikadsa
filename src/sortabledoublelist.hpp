/*
 * Double List with sort operation
 *
 * Notice: sort first before other operation
 *
 */

#ifndef SORTABLEDOUBLELIST_HPP
#define SORTABLEDOUBLELIST_HPP
#include <cstdlib>
#include <cstddef>
#include "compare.hpp"
#include "stack.hpp"
#include "doublelist.hpp"

#include <iostream>

template<typename T>
class SortableDoubleList:public DoubleList<T>{
	typedef int(*VoidComparer)(const void*,const void*);
	typedef int(*Comparer)(const T&,const T&);
	typedef typename DoubleList<T>::Visitor visitor_t;
	enum MergeSortTaskType{MERGE,MERGESORT};
	struct MergeSortTask{
		MergeSortTaskType type;
		ptrdiff_t from,to,mid;
	};
	void merge(ptrdiff_t from,ptrdiff_t to,ptrdiff_t mid,Comparer compare=defaultCompare<T>){
		visitor_t vLeft=this->getHead();
		ptrdiff_t rank=-1;
		while(rank<from){
			vLeft++;
			rank++;
		}
		visitor_t vRight=vLeft;
		while(rank<mid){
			vRight++;
			rank++;
		}
		ptrdiff_t lLeft=mid-from,lRight=to-mid,rLeft=0,rRight=0;
		while(rLeft<lLeft){
			if(rRight<lRight){
				while(rRight<lRight&&compare(*vLeft,*vRight)>0){
					visitor_t vTmp=vRight;
					vRight++;
					rRight++;
					vTmp.moveToBefore(vLeft);
				}
			}
			vLeft++;
			rLeft++;
		}
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

#endif //SORTABLEDOUBLELIST_HPP