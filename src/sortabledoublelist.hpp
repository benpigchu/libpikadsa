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
#include "double.hpp"

template<typename T>
class SortDoubleList:public DoubleList<T>{
	typedef int(*VoidComparer)(const void*,const void*);
	typedef int(*Comparer)(const T&,const T&);
	// enum MergeSortTaskType{MERGE,MERGESORT};
	// struct MergeSortTask{
	// 	MergeSortTaskType type;
	// 	Visitor leftFirst,rightFirst;
	// 	ptrdiff_t leftLength,rightLength;
	// };
	// void merge(Visitor leftFirst,Visitor rightFirst,ptrdiff_t leftLength,ptrdiff_t rightLength,Comparer compare=defaultCompare<T>){

	// }
	public:
	// void mergeSort(Comparer compare=defaultCompare<T>){
	// 	Stack<MergeSortTask> tasks;
	// 	tasks.push({MERGESORT,0,this->size,0});
	// 	while(!tasks.isEmpty()){
	// 		MergeSortTask task=tasks.pop();
	// 		if(task.type==MERGE){
	// 			merge(task.leftFirst,task.rightFirst,task.leftLength,task.rightLength,compare);
	// 		}else{
	// 			if(task.leftLength>1){
	// 				ptrdiff_t mid=task.leftLength>>1;
	// 				Visitor right=task.leftFirst;
	// 				for(ptrdiff_t i=0;i<mid;i++){
	// 					right++;
	// 				}
	// 				tasks.push({MERGE,task.leftFirst,right,mid,task.leftLength-mid});
	// 				tasks.push({MERGESORT,task.leftFirst,NULL,mid,0});
	// 				tasks.push({MERGESORT,right,NULL,task.leftLength-mid,0});
	// 			}
	// 		}
	// 	}
	// }
};

#endif //SORTABLEDOUBLELIST_HPP