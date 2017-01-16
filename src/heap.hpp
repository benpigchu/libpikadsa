#ifndef HEAP_HPP
#define HEAP_HPP
#include <cstdlib>
#include <cstddef>
#include "compare.hpp"
#include "vector.hpp"

template<typename T,int(*compare)(const T&,const T&)=defaultCompare<T>>
class Heap{
	Vector<T> vector;
	public:
	void insert(T v){
		ptrdiff_t newPos=vector.getSize();
		vector.addToEnd(v);
		while(newPos>0){
			if(compare(vector[newPos],vector[(newPos-1)>>1])>0){
				vector[newPos]=vector[(newPos-1)>>1];
				newPos=(newPos-1)>>1;
				vector[newPos]=v;
			}else{
				break;
			}
		}
	}
	T pop(){
		T v=vector[0];
		ptrdiff_t currentPos=0;
		while((currentPos<<1)+2<=vector.getSize()){
			if((currentPos<<1)+2==vector.getSize()){
				vector[currentPos]=vector[(currentPos<<1)+1];
				currentPos=(currentPos<<1)+1;
			}else{
				if(compare(vector[(currentPos<<1)+1],vector[(currentPos<<1)+2])>0){
					vector[currentPos]=vector[(currentPos<<1)+1];
					currentPos=(currentPos<<1)+1;
				}else{
					vector[currentPos]=vector[(currentPos<<1)+2];
					currentPos=(currentPos<<1)+2;
				}
			}
		}
		T fill=vector.removeEnd();
		if(currentPos!=vector.getSize()){
			vector[currentPos]=fill;
			while(currentPos>0){
				if(compare(vector[currentPos],vector[(currentPos-1)>>1])>0){
					vector[currentPos]=vector[(currentPos-1)>>1];
					currentPos=(currentPos-1)>>1;
					vector[currentPos]=fill;
				}else{
					break;
				}
			}
		}
		return v;
	}
	size_t getSize(){
		return vector.getSize();
	}
	size_t isEmpty(){
		return vector.isEmpty();
	}
};

#endif //HEAP_HPP