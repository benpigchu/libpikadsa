#include "doublelist.hpp"
#include <iostream>

int main(){
	DoubleList<int> l;
	DoubleList<int>::Visitor v=l.getHead();
	std::cout<<(l.isEmpty()?"pass":"fail")<<std::endl;
	std::cout<<(v.isHead()?"pass":"fail")<<std::endl;
	v.insertAfter(1).insertAfter(2).insertAfter(5).insertAfter(7).insertAfter(4);
	v.next();
	std::cout<<((*v==4)?"pass":"fail")<<std::endl;
	std::cout<<((!v.isHead())?"pass":"fail")<<std::endl;
	std::cout<<((!v.isTail())?"pass":"fail")<<std::endl;
	v.next().next().next().next();
	v.removeToLeft();
	std::cout<<((*v==2)?"pass":"fail")<<std::endl;
	v.prev();
	std::cout<<((*v==5)?"pass":"fail")<<std::endl;
	v.removeToRight();
	std::cout<<((*v==2)?"pass":"fail")<<std::endl;
	v.next();
	std::cout<<(v.isTail()?"pass":"fail")<<std::endl;
	std::cout<<((l.getSize()==3)?"pass":"fail")<<std::endl;
	std::cout<<((!l.isEmpty())?"pass":"fail")<<std::endl;
	v.insertBefore(9);
	v--;
	std::cout<<((v)?"pass":"fail")<<std::endl;
	std::cout<<((*v==9)?"pass":"fail")<<std::endl;
	v++;
	std::cout<<(v.isTail()?"pass":"fail")<<std::endl;
	std::cout<<((!v)?"pass":"fail")<<std::endl;
	v--;
	DoubleList<int>::Visitor vh=l.getHead();
	v.moveToAfter(vh);
	v--;
	std::cout<<(v.isHead()?"pass":"fail")<<std::endl;
	v++;
	DoubleList<int>::Visitor vt=l.getTail();
	std::cout<<(vt.isTail()?"pass":"fail")<<std::endl;
	v.moveToBefore(vt);
	v++;
	std::cout<<(v.isTail()?"pass":"fail")<<std::endl;
}