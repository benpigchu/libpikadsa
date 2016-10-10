/*
 * Double List
 *
 * Notice: do not visit value of Vistor in type HEAD and TAIL
 *
 */

#ifndef DOUBLELIST_HPP
#define DOUBLELIST_HPP
#include <cstdlib>
#include <cstddef>

template<typename T>
class DoubleList{
	protected:
	struct Node{
		T value;
		Node *next=NULL,*prev=NULL;
	};
	Node *head=NULL,*tail=NULL;
	size_t size=0;
	friend class Visitor;
	friend class ConstVisitor;
	public:
	enum VisitorType{HEAD,TAIL,NORMAL};
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
		bool isHead()const{
			return type==HEAD;
		}
		bool isTail()const{
			return type==TAIL;
		}
		operator bool(){
			return !(isHead()||isTail());
		}
		ConstVisitor& next(){
			if(type==TAIL){
				return *this;
			}
			if(type==HEAD){
				node=list.head;
				type=NORMAL;
			}else{
				node=node->next;
			}
			if(node==NULL){
				type=TAIL;
			}
			return *this;
		}
		ConstVisitor& prev(){
			if(type==HEAD){
				return *this;
			}
			if(type==TAIL){
				node=list.tail;
				type=NORMAL;
			}else{
				node=node->prev;
			}
			if(node==NULL){
				type=HEAD;
			}
			return *this;
		}
		ConstVisitor& operator++(){
			return next();
		}
		ConstVisitor operator++(int){
			Visitor tmp(this->type,this->node,this->list);
			operator++();
			return tmp;
		}
		ConstVisitor& operator--(){
			return prev();
		}
		ConstVisitor operator--(int){
			Visitor tmp(this->type,this->node,this->list);
			operator--();
			return tmp;
		}
	};
	class Visitor:public ConstVisitor{
		friend class DoubleList;
		Visitor(VisitorType t,Node *n,DoubleList &l):ConstVisitor(t,n,l){}
		public:
		T& operator*()const{
			return this->node->value;
		}
		T* operator->()const{
			return *(this->node->value);
		}
		Visitor& next(){
			if(this->type==TAIL){
				return *this;
			}
			if(this->type==HEAD){
				this->node=this->list.head;
				this->type=NORMAL;
			}else{
				this->node=this->node->next;
			}
			if(this->node==NULL){
				this->type=TAIL;
			}
			return *this;
		}
		Visitor& prev(){
			if(this->type==HEAD){
				return *this;
			}
			if(this->type==TAIL){
				this->node=this->list.tail;
				this->type=NORMAL;
			}else{
				this->node=this->node->prev;
			}
			if(this->node==NULL){
				this->type=HEAD;
			}
			return *this;
		}
		Visitor& operator++(){
			return next();
		}
		Visitor operator++(int){
			Visitor tmp(this->type,this->node,this->list);
			operator++();
			return tmp;
		}
		Visitor& operator--(){
			return prev();
		}
		Visitor operator--(int){
			Visitor tmp(this->type,this->node,this->list);
			operator--();
			return tmp;
		}
		Visitor& insertBefore(T v){
			if(this->type!=HEAD){
				this->list.size++;
				Node *toInsert=new Node();
				toInsert->value=v;
				if(this->type==NORMAL){
					toInsert->prev=this->node->prev;
					toInsert->next=this->node;
					if(this->node->prev!=NULL){
						this->node->prev->next=toInsert;
					}else{
						this->list.head=toInsert;
					}
					this->node->prev=toInsert;
				}else{
					if(this->list.tail!=NULL){
						this->list.tail->next=toInsert;
						toInsert->prev=this->list.tail;
					}else{
						this->list.head=toInsert;
					}
					this->list.tail=toInsert;
				}
			}
			return *this;
		}
		Visitor& insertAfter(T v){
			if(this->type!=TAIL){
				this->list.size++;
				Node *toInsert=new Node();
				toInsert->value=v;
				if(this->type==NORMAL){
					toInsert->prev=this->node;
					toInsert->next=this->node->next;
					if(this->node->next!=NULL){
						this->node->next->prev=toInsert;
					}else{
						this->list.tail=toInsert;
					}
					this->node->next=toInsert;
				}else{
					if(this->list.head!=NULL){
						this->list.head->prev=toInsert;
						toInsert->next=this->list.head;
					}else{
						this->list.tail=toInsert;
					}
					this->list.head=toInsert;
				}
			}
			return *this;
		}
		Visitor& removeToLeft(){
			if(this->type==NORMAL){
				Node *left=this->node->prev;
				if(this->node->prev!=NULL){
					this->node->prev->next=this->node->next;
				}else{
					this->list.head=this->node->next;
				}
				if(this->node->next!=NULL){
					this->node->next->prev=this->node->prev;
				}else{
					this->list.tail=this->node->prev;
				}
				delete this->node;
				this->node=left;
				if(this->node==NULL){
					this->type=HEAD;
				}
				this->list.size--;
			}
			return *this;
		}
		Visitor& removeToRight(){
			if(this->type==NORMAL){
				Node *right=this->node->next;
				if(this->node->prev!=NULL){
					this->node->prev->next=this->node->next;
				}else{
					this->list.head=this->node->next;
				}
				if(this->node->next!=NULL){
					this->node->next->prev=this->node->prev;
				}else{
					this->list.tail=this->node->prev;
				}
				delete this->node;
				this->node=right;
				if(this->node==NULL){
					this->type=TAIL;
				}
				this->list.size--;
			}
			return *this;
		}
		Visitor& moveToBefore(Visitor &p){
			if(this->type==NORMAL&&p.type!=HEAD&&this->node!=p.node){
				if(this->node->prev!=NULL){
					this->node->prev->next=this->node->next;
				}else{
					this->list.head=this->node->next;
				}
				if(this->node->next!=NULL){
					this->node->next->prev=this->node->prev;
				}else{
					this->list.tail=this->node->prev;
				}
				if(p.type==NORMAL){
					this->node->prev=p.node->prev;
					this->node->next=p.node;
					if(p.node->prev!=NULL){
						p.node->prev->next=this->node;
					}else{
						p.list.head=this->node;
					}
					p.node->prev=this->node;
				}else{
					this->node->next=NULL;
					if(p.list.tail!=NULL){
						p.list.tail->next=this->node;
						this->node->prev=p.list.tail;
					}else{
						p.list.head=this->node;
					}
					p.list.tail=this->node;
				}
			}
			return *this;
		}
		Visitor& moveToAfter(Visitor &p){
			if(this->type==NORMAL&&p.type!=TAIL&&this->node!=p.node){
				if(this->node->prev!=NULL){
					this->node->prev->next=this->node->next;
				}else{
					this->list.head=this->node->next;
				}
				if(this->node->next!=NULL){
					this->node->next->prev=this->node->prev;
				}else{
					this->list.tail=this->node->prev;
				}
				if(p.type==NORMAL){
					this->node->prev=p.node;
					this->node->next=p.node->next;
					if(p.node->next!=NULL){
						p.node->next->prev=this->node;
					}else{
						p.list.tail=this->node;
					}
					p.node->next=this->node;
				}else{
					this->node->prev=NULL;
					if(p.list.head!=NULL){
						p.list.head->prev=this->node;
						this->node->next=p.list.head;
					}else{
						p.list.tail=this->node;
					}
					p.list.head=this->node;
				}
			}
			return *this;
		}
		Visitor& reinsertBefore(Visitor &p){
			p.moveToBefore(*this);
			return *this;
		}
		Visitor& reinsertAfter(Visitor &p){
			p.moveToAfter(*this);
			return *this;
		}
	};
	Visitor getHead(){
		return Visitor(HEAD,NULL,*this);
	}
	ConstVisitor getHead()const{
		return ConstVisitor(HEAD,NULL,*this);
	}
	Visitor getTail(){
		return Visitor(TAIL,NULL,*this);
	}
	ConstVisitor getTail()const{
		return ConstVisitor(TAIL,NULL,*this);
	}
	size_t getSize()const{
		return size;
	}
	bool isEmpty()const{
		return head==NULL;
	}
	~DoubleList(){
		while(head!=NULL){
			Node* tmp=head;
			head=tmp->next;
			delete tmp;
		}
	}
};

#endif //DOUBLELIST_HPP