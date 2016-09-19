/*
 * Queue with linked list
 *
 * Notice: do not put out element from empty queue
 *
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

template<typename T>
class Queue{
	struct Node{
		T value;
		Node *next=0;
		Node(T val,Node *ne=0):value(val),next(ne){}
		~Node(){}
	};
	Node *head=0;
	Node *tail=0;
	public:
	void putIn(T v){
		if(head==0){
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
		if(head==0){
			tail==0;
		}
		return v;
	}
	bool isEmpty(){
		return head==0;
	}
	~Queue(){
		while(head!=0){
			putOut();
		}
	}
};

#endif //QUEUE_HPP