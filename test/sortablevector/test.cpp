#include "sortablevector.hpp"
#include <iostream>

int main(){
	SortableVector<int,8> v;
	v.addToEnd(7);
	v.addToEnd(2);
	v.addToEnd(6);
	v.addToEnd(3);
	std::cout<<(!v.sorted()?"pass":"fail")<<std::endl;
	v.qSort();
	std::cout<<((v[0]==2)?"pass":"fail")<<std::endl;
	std::cout<<((v[1]==3)?"pass":"fail")<<std::endl;
	std::cout<<((v[2]==6)?"pass":"fail")<<std::endl;
	std::cout<<((v[3]==7)?"pass":"fail")<<std::endl;
	std::cout<<(v.sorted()?"pass":"fail")<<std::endl;
	std::cout<<((v.bSearch(4)==-1)?"pass":"fail")<<std::endl;
	std::cout<<((v.bSearch(6)==2)?"pass":"fail")<<std::endl;
	v.addToEnd(7);
	v.addToEnd(7);
	v.addToEnd(7);
	v.addToEnd(7);
	v.addToEnd(7);
	v.addToEnd(7);
	v.addToEnd(7);
	v.addToEnd(7);
	v[2]=5;
	std::cout<<((v.binarySearch(7)==3)?"pass":"fail")<<std::endl;
	std::cout<<((v.binarySearch(6)==3)?"pass":"fail")<<std::endl;
	std::cout<<((v.binaryFind(7)==3)?"pass":"fail")<<std::endl;
	std::cout<<((v.binaryFind(8)==-1)?"pass":"fail")<<std::endl;
	return 0;
}