#ifndef CELL_LIST_H
#define CELL_LIST_H

#include <stdlib.h>
#include "../world/cell.h"

/*
*	Simple implementation of a doubly-linked list for cells
*/

// Container nodes
class CellNode {
public:
	CellNode(Cell*);

	CellNode* getPrev() {
		return this->prev;
	};
	CellNode* setPrev(CellNode* prev) {
		this->prev = prev;
		return this;
	};

	CellNode* getNext() {
		return this->next;
	};
	CellNode* setNext(CellNode* next) {
		this->next = next;
		return this;
	}

	Cell* getCell() {
		return this->cell;
	};
	void setCell(Cell* c) {
		this->cell = c;
	};

private:
	CellNode* prev;
	CellNode* next;
	Cell* cell;
};

// Root node for record keeping
class CellList {
public:
	CellList();

	void remove(CellNode*);

	void pushBack(Cell*);
	void pushBack(CellNode*);

	CellNode* popFront();
	CellNode* popLast();

	CellNode* getFirst() {
		return this->first;
	};

	CellNode* getLast() {
		return this->last;
	};

	void setFirst(CellNode* node) {
		this->first = node;
	}

	void setLast(CellNode* node) {
		this->last = last;
	}

private:
	CellNode* first;
	CellNode* last;
};

#endif