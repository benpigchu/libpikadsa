#include "binarytree.hpp"
#include <iostream>

int main(){
	BinaryTree<int> bt;
	BinaryTree<int>::Visitor v=bt.getRoot();
	v.tryInsertLeftChild(1);
	v.changeToLeftChild();
	v.tryInsertLeftChild(2);
	v.tryInsertRightChild(3);
	v.rotateRight();
	std::cout<<((*v==2)?"pass":"fail")<<std::endl;
	v.rotateLeft();
	std::cout<<((*v==1)?"pass":"fail")<<std::endl;
	v.rotateLeft();
	std::cout<<((*v==3)?"pass":"fail")<<std::endl;
	v.rotateRight();
	std::cout<<((*v==1)?"pass":"fail")<<std::endl;
}