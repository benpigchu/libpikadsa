#ifndef DOUBLELIST_HPP
#define DOUBLELIST_HPP
#include <cstdlib>
#include <cstddef>

template<typename T>
class DoubleList{
	struct Node{
		T value;
		Node *next=NULL,*prev=NULL;
	};
	Node *head=NULL,*tail=NULL;
	size_t size=0;
	friend class Visitor;
	public:
	Enum VisitorType{HEAD,TAIL,NORMAL}
	class ConstVisitor{
		VisitorType type;
		Node *node;
		DoubleList &list;
		friend class DoubleList;
		ConstVisitor(VisitorType t,Node *n,DoubleList &l):type(t),node(n),list(l){}
		public:
		const T& operator*()const{
			return node->value;
		}
		ConstVisitor& next(){
			if(type==TAIL){
				return *this;
			}
			if(type==HEAD){
				node=l.head;
				type=NORMAL;
			}else{
				node=node->next;
			}
			if(node==NULL){
				type=TAIL;
			}
			return *this
		}
		ConstVisitor& prev(){
			if(type==HEAD){
				return *this;
			}
			if(type==TAIL){
				node=l.tail;
				type=NORMAL;
			}else{
				node=node->prev;
			}
			if(node==NULL){
				type=HEAD;
			}
			return *this
		}
	};
	class Visitor:ConstVisitor{
		Visitor(VisitorType t,Node *n,DoubleList &l):ConstVisitor(VisitorType t,Node *n,DoubleList &l){}
		T& operator*()const{
			return node->value;
		}
		T* operator->()const{
			return *(node->value);
		}
		Visitor& next(){
			if(type==TAIL){
				return *this;
			}
			if(type==HEAD){
				node=l.head;
				type=NORMAL;
			}else{
				node=node->next;
			}
			if(node==NULL){
				type=TAIL;
			}
			return *this;
		}
		Visitor& prev(){
			if(type==HEAD){
				return *this;
			}
			if(type==TAIL){
				node=l.tail;
				type=NORMAL;
			}else{
				node=node->prev;
			}
			if(node==NULL){
				type=HEAD;
			}
			return *this;
		}
		Visitor& operator++(){
			return next();
		}
		Visitor& operator++(int){
			Visitor tmp(type,node,list)
			operator++()
			return tmp;
		}
		Visitor& operator--(){
			return perv();
		}
		Visitor& operator++(int){
			Visitor tmp(type,node,list)
			operator--()
			return tmp;
		}
		Visitor& insertBefore(T v){
			if(type!=HEAD){
				list.size++;
				Node *toInsert=new Node();
				toInsert->value=v;
				if(type==NORMAL){
					toInsert->prev=node->prev;
					toInsert->next=node;
					if(node->prev!=NULL){
						node->prev->next=toInsert;
					}else{
						list.head=toInsert;
					}
					node->prev=toInsert;
				}else{
					list.tail->next=toInsert;
					toInsert->prev=list.tail;
					list.tail=toInsert;
				}
			}
			return *this;
		}
		Visitor& insertAfter(T v){
			if(type!=TAIL){
				list.size++;
				Node *toInsert=new Node();
				toInsert->value=v;
				if(type==NORMAL){
					toInsert->prev=node;
					toInsert->next=node->next;
					if(node->next!=NULL){
						node->next->prev=toInsert;
					}else{
						list.tail=toInsert;
					}
					node->next=toInsert;
				}else{
					list.head->prev=toInsert;
					toInsert->next=list.head;
					list.head=toInsert;
				}
			}
			return *this;
		}
		T remove(){
			T tmp=node->value;
			if(type==NORMAL){
				if(node->prev!=NULL){
					node->prev->next=node->next;
				}else{
					list.head=node->next;
				}
				if(node->next!=NULL){
					node->next->prev=node->prev;
				}else{
					list.tail=node->prev;
				}
				delete node;
			}
			return tmp;
		}
	}
	Visitor getHead(){
		return Visitor(HEAD,NULL,*this);
	}
	ConstVisitor getHead()const{
		return ConstVisitor(HEAD,NULL,*this);
	}
	Visitor getTail()const{
		return Visitor(TAIL,NULL,*this);
	}
	ConstVisitor getTail()const{
		return ConstVisitor(TAIL,NULL,*this);
	}
	bool isEmpty()const{
		return head==NULL;
	}
	~DoubleList(){
		while(head!=NULL){
			Node* tmp=head;
			head=tmp.next;
			delete tmp;
		}
	}
};

#endif //DOUBLELIST_HPP