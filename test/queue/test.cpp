#include "queue.hpp"
#include <iostream>

int main(){
	Queue<int> s;
	std::cout<<((s.isEmpty())?"pass":"fail")<<std::endl;
	s.putIn(100);
	s.putIn(1);
	s.putIn(2);
	std::cout<<((s.putOut()==100)?"pass":"fail")<<std::endl;
	std::cout<<((!s.isEmpty())?"pass":"fail")<<std::endl;
	return 0;
}