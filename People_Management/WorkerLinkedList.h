/*
 * WorkerLinkedList.h
 *
 *  Created on: Nov 30, 2017
 *      Author: David
 */

#ifndef WORKERLINKEDLIST_H_
#define WORKERLINKEDLIST_H_
#include <iostream>
#include <string>

namespace std {
struct node
{
	Worker Worker;
	node *next;
};
class WorkerLinkedList {
private:
	node *head;
	node *tail;
public:
	void printWorkerWeekSchedule(std::string name, int month, int weekOfMonth);
	Worker* getHeadWorker();
	Worker* getTailWorker();
	WorkerLinkedList();
	virtual ~WorkerLinkedList();

	const node*& getHead() const {
		return head;
	}

	void setHead(const node*& head) {
		this->head = head;
	}

	const node*& getTail() const {
		return tail;
	}

	void setTail(const node*& tail) {
		this->tail = tail;
	}
};
}
#endif /* WORKERLINKEDLIST_H_ */
