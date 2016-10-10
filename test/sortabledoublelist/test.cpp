#include "doublelist.hpp"
#include "sortabledoublelist.hpp"
#include <iostream>

int main(){
	SortableDoubleList<int> l;
	DoubleList<int>::Visitor v=l.getHead();
	v.insertAfter(6).insertAfter(1).insertAfter(2).insertAfter(5).insertAfter(3).insertAfter(7).insertAfter(4);
	l.mergeSort();
	v.next();
	std::cout<<((*v==1)?"pass":"fail")<<std::endl;
	v.next();
	std::cout<<((*v==2)?"pass":"fail")<<std::endl;
	v.next();
	std::cout<<((*v==3)?"pass":"fail")<<std::endl;
	v.next();
	std::cout<<((*v==4)?"pass":"fail")<<std::endl;
	v.next();
	std::cout<<((*v==5)?"pass":"fail")<<std::endl;
	v.next();
	std::cout<<((*v==6)?"pass":"fail")<<std::endl;
	v.next();
	std::cout<<((*v==7)?"pass":"fail")<<std::endl;
}