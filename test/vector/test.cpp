#include "vector.hpp"
#include <iostream>

int main(){
	Vector<int,8> v;
	std::cout<<((v.isEmpty())?"pass":"fail")<<std::endl;
	std::cout<<((v.getCapacity()==8)?"pass":"fail")<<std::endl;
	v.addToEnd(1);
	v.addToEnd(3);
	v.addToEnd(5);
	v.addToEnd(7);
	std::cout<<((v.getSize()==4)?"pass":"fail")<<std::endl;
	v.shrink();
	std::cout<<((v.getCapacity()==4)?"pass":"fail")<<std::endl;
	std::cout<<((v.removeEnd()==7)?"pass":"fail")<<std::endl;
	v.addToEnd(9);
	v.addToEnd(11);
	std::cout<<((v.getCapacity()==8)?"pass":"fail")<<std::endl;
	std::cout<<((v[3]==9)?"pass":"fail")<<std::endl;
	v[3]=4;
	std::cout<<((v[3]==4)?"pass":"fail")<<std::endl;
	v.insert(2,2);
	std::cout<<((v[2]==2)?"pass":"fail")<<std::endl;
	std::cout<<((v[3]==5)?"pass":"fail")<<std::endl;
	std::cout<<((v.remove(3)==5)?"pass":"fail")<<std::endl;
	std::cout<<((v[3]==4)?"pass":"fail")<<std::endl;
	v.expandTo(16);
	std::cout<<((v.getCapacity()==16)?"pass":"fail")<<std::endl;
	return 0;
}