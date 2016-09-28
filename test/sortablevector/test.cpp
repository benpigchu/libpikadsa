#include "sortablevector.hpp"
#include <iostream>

int main(){
	SortableVector<int,8> v;
	v.addToEnd(7);
	v.addToEnd(2);
	v.addToEnd(6);
	v.addToEnd(3);
	v.qSort();
	std::cout<<((v[0]==2)?"pass":"fail")<<std::endl;
	std::cout<<((v[1]==3)?"pass":"fail")<<std::endl;
	std::cout<<((v[2]==6)?"pass":"fail")<<std::endl;
	std::cout<<((v[3]==7)?"pass":"fail")<<std::endl;
	std::cout<<((v.bSearch(4)==-1)?"pass":"fail")<<std::endl;
	std::cout<<((v.bSearch(6)==2)?"pass":"fail")<<std::endl;
	return 0;
}