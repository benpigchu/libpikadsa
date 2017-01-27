#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP
#include <cstdlib>
#include <cstddef>
#include "stack.hpp"

enum VoidExtendInfo{NOINFO};

template<typename T,typename ExtendInfo=VoidExtendInfo>
class BinaryTree{
	protected:
	struct Node{
		T value;
		Node *parent=NULL,*leftChild=NULL,*rightChild=NULL;
		ExtendInfo info;
	};
	Node *root=NULL;
	friend class Visitor;
	friend class ConstVisitor;
	public:
	enum VisitorType{ROOT,LEFTCHILD,RIGHTCHILD,NORMAL};
	class ConstVisitor{
		VisitorType type;
		Node *node;
		BinaryTree &tree;
		friend class BinaryTree;
		public:
		ConstVisitor(VisitorType t,Node *n,BinaryTree &tr):type(t),node(n),tree(tr){}
		const T& operator*()const{
			return node->value;
		}
		bool isRoot()const{
			return type==ROOT;
		}
		bool isLeaf()const{
			return (type==LEFTCHILD)||(type==RIGHTCHILD);
		}
		bool isLeftChild()const{
			if(type==LEFTCHILD){
				return true;
			}else{
				if(type!=NORMAL||node->parent==NULL){
					return false;
				}else{
					return node->parent->leftChild==node;
				}
			}
		}
		bool isRightChild()const{
			if(type==RIGHTCHILD){
				return true;
			}else{
				if(type!=NORMAL||node->parent==NULL){
					return false;
				}else{
					return node->parent->rightChild==node;
				}
			}
		}
		operator bool()const{
			return !(isRoot()||isLeaf());
		}
		ConstVisitor& changeToParent(){
			if(type!=ROOT){
				if(type==NORMAL){
					node=node->parent;
					if(node==NULL){
						type=ROOT;
					}
				}else{
					if(node==NULL){
						type=ROOT;
					}else{
						type=NORMAL;
					}
				}
			}
			return *this;
		}
		ConstVisitor& changeToLeftChild(){
			if(type!=LEFTCHILD&&type!=RIGHTCHILD){
				if(type==NORMAL){
					if(node->leftChild==NULL){
						type=LEFTCHILD;
					}else{
						node=node->leftChild;
					}
				}else{
					if(tree.root==NULL){
						type=LEFTCHILD;
					}else{
						node=tree.root;
						type=NORMAL;
					}
				}
			}
			return *this;
		}
		ConstVisitor& changeToRightChild(){
			if(type!=LEFTCHILD&&type!=RIGHTCHILD){
				if(type==NORMAL){
					if(node->rightChild==NULL){
						type=RIGHTCHILD;
					}else{
						node=node->rightChild;
					}
				}else{
					if(tree.root==NULL){
						type=RIGHTCHILD;
					}else{
						node=tree.root;
						type=NORMAL;
					}
				}
			}
			return *this;
		}
	};
	class Visitor:public ConstVisitor{
		friend class BinaryTree;
		Visitor(VisitorType t,Node *n,BinaryTree &tr):ConstVisitor(t,n,tr){}
		public:
		T& operator*()const{
			return this->node->value;
		}
		T* operator->()const{
			return &(this->node->value);
		}
		Visitor& changeToParent(){
			if(this->type!=ROOT){
				if(this->type==NORMAL){
					this->node=this->node->parent;
					if(this->node==NULL){
						this->type=ROOT;
					}
				}else{
					if(this->node==NULL){
						this->type=ROOT;
					}else{
						this->type=NORMAL;
					}
				}
			}
			return *this;
		}
		Visitor& changeToLeftChild(){
			if(this->type!=LEFTCHILD&&this->type!=RIGHTCHILD){
				if(this->type==NORMAL){
					if(this->node->leftChild==NULL){
						this->type=LEFTCHILD;
					}else{
						this->node=this->node->leftChild;
					}
				}else{
					if(this->tree.root==NULL){
						this->type=LEFTCHILD;
					}else{
						this->node=this->tree.root;
						this->type=NORMAL;
					}
				}
			}
			return *this;
		}
		Visitor& changeToRightChild(){
			if(this->type!=LEFTCHILD&&this->type!=RIGHTCHILD){
				if(this->type==NORMAL){
					if(this->node->rightChild==NULL){
						this->type=RIGHTCHILD;
					}else{
						this->node=this->node->rightChild;
					}
				}else{
					if(this->tree.root==NULL){
						this->type=RIGHTCHILD;
					}else{
						this->node=this->tree.root;
						this->type=NORMAL;
					}
				}
			}
			return *this;
		}
		Visitor& tryInsertLeftChild(T v){
			if(this->type!=LEFTCHILD&&this->type!=RIGHTCHILD){
				if(this->type==NORMAL){
					if(this->node->leftChild==NULL){
						this->node->leftChild=new Node;
						this->node->leftChild->value=v;
						this->node->leftChild->parent=this->node;
					}
				}else{
					if(this->tree.root==NULL){
						this->tree.root=new Node;
						this->tree.root->value=v;
					}
				}
			}
		}
		Visitor& tryInsertRightChild(T v){
			if(this->type!=LEFTCHILD&&this->type!=RIGHTCHILD){
				if(this->type==NORMAL){
					if(this->node->rightChild==NULL){
						this->node->rightChild=new Node;
						this->node->rightChild->value=v;
						this->node->rightChild->parent=this->node;
					}
				}else{
					if(this->tree.root==NULL){
						this->tree.root=new Node;
						this->tree.root->value=v;
					}
				}
			}
		}
		Visitor& removeSubTree(){
			if(!(this->type==LEFTCHILD&&this->type==RIGHTCHILD)){
				Node *toRemove;
				if(this->type==ROOT){
					toRemove=this->tree.root;
				}else{
					toRemove=this->node;
					if(this->isLeftChild()){
						this->type=LEFTCHILD;
					}else{
						this->type=RIGHTCHILD;
					}
					this->node=this->node->parent;
					if(this->type==LEFTCHILD){
						this->node->leftChild==NULL;
					}else{
						this->node->rightChild==NULL;
					}
				}
				Stack<Node*> taskStack;
				taskStack.push(toRemove);
				while(!taskStack.isEmpty()){
					Node* taskNode=taskStack.pop();
					if(taskNode!=NULL){
						taskStack.push(taskNode->leftChild);
						taskStack.push(taskNode->rightChild);
						delete taskNode;
					}
				}
			}
		}
		Visitor& rotateRight(){
			if(this->type==NORMAL){
				if(this->node->leftChild!=NULL){
					Node* right=this->node;
					Node* left=right->leftChild;
					Node* center=left->rightChild;
					Node* parent=right->parent;
					this->node=left;
					right->parent=left;
					right->leftChild=center;
					left->parent=parent;
					left->rightChild=right;
					if(center!=NULL){
						center->parent=right;
					}
					if(parent!=NULL){
						if(parent->leftChild==right){
							parent->leftChild=left;
						}else{
							parent->rightChild=left;
						}
					}
				}
			}
		}
		Visitor& rotateLeft(){
			if(this->type==NORMAL){
				if(this->node->rightChild!=NULL){
					Node* left=this->node;
					Node* right=left->rightChild;
					Node* center=right->leftChild;
					Node* parent=left->parent;
					this->node=right;
					left->parent=right;
					left->rightChild=center;
					right->parent=parent;
					right->leftChild=left;
					if(center!=NULL){
						center->parent=left;
					}
					if(parent!=NULL){
						if(parent->rightChild==left){
							parent->rightChild=right;
						}else{
							parent->leftChild=right;
						}
					}
				}
			}
		}
	};
	Visitor getRoot(){
		return Visitor(ROOT,NULL,*this);
	}
	ConstVisitor getRoot()const{
		return ConstVisitor(ROOT,NULL,*this);
	}
	bool isEmpty()const{
		return root==NULL;
	}
	~BinaryTree(){
		getRoot().removeSubTree();
	}
};

#endif //BINARYTREE_HPP