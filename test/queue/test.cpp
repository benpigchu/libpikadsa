#include "queue.hpp"
#include <iostream>

int main(){
	Queue<int> s;
	s.putIn(100);
	s.putIn(1);
	s.putIn(2);
	std::cout<<((s.putOut()==100)?"pass":"fail");
	return 0;
}