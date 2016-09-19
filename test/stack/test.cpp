#include "stack.hpp"
#include <iostream>

int main(){
	Stack<int> s;
	std::cout<<((s.isEmpty())?"pass":"fail")<<std::endl;
	s.push(100);
	s.push(1);
	s.push(2);
	std::cout<<((s.pop()==2)?"pass":"fail")<<std::endl;
	std::cout<<((!s.isEmpty())?"pass":"fail")<<std::endl;
	return 0;
}