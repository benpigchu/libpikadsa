#include "stack.hpp"
#include <iostream>

int main(){
	Stack<int> s;
	s.push(100);
	s.push(1);
	s.push(2);
	std::cout<<((s.pop()==2)?"pass":"fail");
	return 0;
}