#include "cellList.h"

CellList::CellList() {
	this->first = NULL;
	this->last = NULL;
}

void CellList::remove(CellNode* node) {
	CellNode* prev = node->getPrev();
	CellNode* next = node->getNext();
	if(prev != NULL) {
		prev->setNext(next);
	}

	if(next != NULL) {
		next->setPrev(prev);
	}

	if(prev == NULL) {
		this->setFirst(next);
	}

	if(next == NULL) {
		this->setLast(prev);
	}

	node->setPrev(NULL);
	node->setNext(NULL);
} 

void CellList::pushBack(Cell* c) {
	CellNode* node = new CellNode(c);
	this->pushBack(node);
}

void CellList::pushBack(CellNode* node) {
	if(this->first == NULL) {
		node->setPrev(NULL);
		node->setNext(NULL);
		this->first = node;
		this->last = node;
		return;
	}

	this->last->setNext(node);
	node->setPrev(this->last);
	node->setNext(NULL);
	this->last = node;
}

CellNode* CellList::popFront() {
	if(this->first == NULL) {
		return NULL;
	}

	CellNode* node = this->first;
	CellNode* next = this->first->getNext();
	if(next != NULL) {
		next->setPrev(NULL);
	} else {
		this->last = NULL;
	}
	this->first = this->first->getNext();
	return node;
}

CellNode* CellList::popLast() {
	CellNode* node = this->last;
	CellNode* prev = this->last->getPrev();
	if(prev != NULL) {
		prev->setNext(NULL);
	} else {
		this->first = NULL;
	}
	this->last = this->last->getPrev();
	return node;
}


CellNode::CellNode(Cell* c) {
	this->cell = c;
}

