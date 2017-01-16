#include "heap.hpp"
#include <iostream>

int main(){
	Heap<int> h;
	h.insert(10);
	h.insert(3);
	h.insert(7);
	h.insert(15);
	std::cout<<((h.getSize()==4)?"pass":"fail")<<std::endl;
	std::cout<<((h.getSize()==4)?"pass":"fail")<<std::endl;
	std::cout<<((h.pop()==15)?"pass":"fail")<<std::endl;
	std::cout<<((h.pop()==10)?"pass":"fail")<<std::endl;
	h.insert(15);
	std::cout<<((h.pop()==15)?"pass":"fail")<<std::endl;
	return 0;
}