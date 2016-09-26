/*
 * Vector without sort operation
 *
 * Notice: do not access invalid index
 *
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstdlib>

template<typename T,size_t initCapacity=1024>
class Vector{
	protected:
	T *buffer;
	size_t size=0;
	size_t capacity=initCapacity;
	public:
	Vector(){
		buffer=new T[capacity];
	}
	void expand(){
		capacity<<=1;
		T *newBuffer=new T[capacity];
		for(size_t i=0;i<size;i++){
			newBuffer[i]=buffer[i];
		}
		delete[] buffer;
		buffer=newBuffer;
	}
	void expandTo(size_t s){
		if(capacity>=s){
			return;
		}
		capacity=s;
		T *newBuffer=new T[capacity];
		for(size_t i=0;i<size;i++){
			newBuffer[i]=buffer[i];
		}
		delete[] buffer;
		buffer=newBuffer;
	}
	void shrink(){
		size_t newCapacity=capacity;
		while((newCapacity>>1)>=size){
			newCapacity>>=1;
		}
		capacity=newCapacity;
		T *newBuffer=new T[newCapacity];
		for(size_t i=0;i<size;i++){
			newBuffer[i]=buffer[i];
		}
		delete[] buffer;
		buffer=newBuffer;
	}
	void addToEnd(T v){
		if(size>=capacity){
			expand();
		}
		buffer[size]=v;
		size++;
	}
	T removeEnd(){
		size--;
		return buffer[size];
	}
	void insert(size_t n,T v){
		if(size>=capacity){
			expand();
		}
		for(size_t i=size;i>=n;i--){
			buffer[i+1]=buffer[i];
		}
		size++;
		buffer[n]=v;
	}
	T remove(size_t n){
		T v=buffer[n];
		for(size_t i=n+1;i<size;i++){
			buffer[i-1]=buffer[i];
		}
		size--;
		return v;
	}
	T& operator[](size_t n){
		return buffer[n];
	}
	const T& operator[](size_t n)const{
		return buffer[n];
	}
	bool isEmpty()const{
		return size==0;
	}
	size_t getSize()const{
		return size;
	}
	size_t getCapacity()const{
		return capacity;
	}
	~Vector(){
		delete[] buffer;
	}
};

#endif //VECTOR_HPP
