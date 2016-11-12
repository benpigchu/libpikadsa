#include "binarytree.hpp"
#include <iostream>

int main(){
	BinaryTree<int> bt;
	BinaryTree<int>::Visitor v=bt.getRoot();
	std::cout<<(bt.isEmpty()?"pass":"fail")<<std::endl;
	std::cout<<(v.isRoot()?"pass":"fail")<<std::endl;
	std::cout<<((!v)?"pass":"fail")<<std::endl;
	v.tryInsertLeftChild(1);
	v.changeToLeftChild();
	std::cout<<((v)?"pass":"fail")<<std::endl;
	std::cout<<((*v==1)?"pass":"fail")<<std::endl;
	*v=2;
	std::cout<<((*v==2)?"pass":"fail")<<std::endl;
	v.tryInsertLeftChild(1);
	v.tryInsertRightChild(2);
	v.changeToLeftChild();
	std::cout<<((*v==1)?"pass":"fail")<<std::endl;
	std::cout<<(v.isLeftChild()?"pass":"fail")<<std::endl;
	v.changeToRightChild();
	std::cout<<(v.isLeaf()?"pass":"fail")<<std::endl;
	std::cout<<(v.isRightChild()?"pass":"fail")<<std::endl;
	v.changeToParent();
	v.tryInsertLeftChild(3);
	v.removeSubTree();
	std::cout<<(v.isLeaf()?"pass":"fail")<<std::endl;
	std::cout<<((!v)?"pass":"fail")<<std::endl;
}