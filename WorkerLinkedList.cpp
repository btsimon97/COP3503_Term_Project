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
	Worker *head;
	Worker *tail;
public:
	void printWorkerWeekSchedule(std::string name,int id, int month, int weekOfMonth){
		Worker* cursor = head;
		while(cursor->workerID!=id){
			cursor = cursor->getNextWorkerInList();
		}
		if(cursor->getNextWorkerInList()==NULL){
			cout << "Could not find the worker with that id";
		}
		else{
			cout<< cursor->workerName<<"\n";
		}
	}
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
