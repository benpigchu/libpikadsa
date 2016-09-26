/*
 * Queue with linked list
 *
 * Notice: do not put out element from empty queue
 *
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstdlib>

template<typename T>
class Queue{
	struct Node{
		T value;
		Node *next=NULL;
		Node(T val,Node *ne=NULL):value(val),next(ne){}
		~Node(){}
	};
	Node *head=NULL;
	Node *tail=NULL;
	public:
	void putIn(T v){
		if(head==NULL){
			tail=new Node(v);
			head=tail;
		}else{
			tail->next=new Node(v);
			tail=tail->next;
		}
	}
	T putOut(){
		T v=head->value;
		Node *n=head->next;
		delete head;
		head=n;
		if(head==NULL){
			tail==NULL;
		}
		return v;
	}
	bool isEmpty()const{
		return head==NULL;
	}
	~Queue(){
		while(head!=NULL){
			putOut();
		}
	}
};

#endif //QUEUE_HPP