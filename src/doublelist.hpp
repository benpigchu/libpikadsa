#ifndef DOUBLELIST_HPP
#define DOUBLELIST_HPP
#include <cstdlib>
#include <cstddef>

template<typename T>
class DoubleList{
	struct Node{
		T v;
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
			return node->v;
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
		Visitor(VisitorType t,Node *n,DoubleList &l):ConstVisitor(VisitorType t,Node *n,DoubleList &l)
		T& operator*()const{
			return node->v;
		}
		T* operator->()const{
			return *(node->v);
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
			return *this
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
			return *this
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
};

#endif //DOUBLELIST_HPP