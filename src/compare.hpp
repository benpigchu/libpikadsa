#ifndef COMPARE_HPP
#define COMPARE_HPP
#include <cstddef>
#include <cstdlib>

template<typename T,int(*compare)(const T&,const T&)>
int compareWarper(const void *a,const void *b){
	const T* av=static_cast<const T*>(a);
	const T* bv=static_cast<const T*>(b);
	return compare(*av,*bv);
}

template<typename T>
int defaultCompare(const T &a,const T &b){
	if(a>b){
		return 1;
	}
	if(a<b){
		return -1;
	}
	return 0;
}

template<typename T,int(*compare)(const T&,const T&)>
int RevesedCompare(const T &a,const T & b){
	return -compare(a,b);
}

#endif //COMPARE_HPP