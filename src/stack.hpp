#ifndef STACK_HPP
#define STACK_HPP

template<typename T>
class Stack{
	struct Node{
		T value;
		Node *next=0;
		Node(T val,Node *ne=0):value(val),next(ne){}
		~Node(){}
	};
	Node *head=0;
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
	bool isEmpty(){
		return head==0;
	}
	~Stack(){
		while(head!=0){
			pop();
		}
	}
};

#endif //STACK_HPP
