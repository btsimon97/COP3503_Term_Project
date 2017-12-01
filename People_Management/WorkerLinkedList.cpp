/*
 * WorkerLinkedList.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: David
 */

#include "WorkerLinkedList.h"

namespace std {
class WorkerLinkedList {
private:
	node *head;
	node *tail;
public:
	void printWorkerWeekSchedule(std::string name,int id, int month, int weekOfMonth){

	};
	Worker* getHeadWorker(){
		return head;
	}
	Worker* getTailWorker(){
		return tail;
	}
	WorkerLinkedList(){
		head= NULL;
		tail= NULL;
	}
};

}
