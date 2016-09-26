/*
 * Stack with linked list
 *
 * Notice: do not pop element from empty stack
 *
 */

#ifndef STACK_HPP
#define STACK_HPP
#include <cstdlib>

template<typename T>
class Stack{
	struct Node{
		T value;
		Node *next=NULL;
		Node(T val,Node *ne=NULL):value(val),next(ne){}
		~Node(){}
	};
	Node *head=NULL;
	public:
	void push(T v){
		head=new Node(v,head);
	}
	T pop(){
		T v=head->value;
		Node *n=head->next;
		delete head;
		head=n;
		return v;
	}
	bool isEmpty()const{
		return head==NULL;
	}
	~Stack(){
		while(head!=NULL){
			pop();
		}
	}
};

#endif //STACK_HPP
