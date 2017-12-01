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
class WorkerLinkedList {
private:
	Worker *head;
	Worker *tail;
public:
	void printWorkerWeekSchedule(std::string name, int month,int year, int weekOfMonth);
	Worker* getHeadWorker();
	Worker* getTailWorker();
	WorkerLinkedList();
	virtual ~WorkerLinkedList();

	const Worker*& getHead() const {
		return head;
	}

	void setHead(const Worker*& head) {
		this->head = head;
	}

	const Worker*& getTail() const {
		return tail;
	}

	void setTail(const Worker*& tail) {
		this->tail = tail;
	}
};
}
#endif /* WORKERLINKEDLIST_H_ */
