/*
 * Worker.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: David
 */

#include "Worker.h"
#include <iostream>
#include <string>
class Worker{
private:
	Worker* nextWorkerInList;
	std::string workerName;
	int workerID;
	//	AppointmentLinkedList appointments;
public:
	Worker* getNextWorker(){
		return nextWorkerInList;
	}
	void setDayOffOnce(int day){

	}
	void setDayOffRegular(int day);
	void setTimeOffOnce(int time);
	void setTimeOffRegular(int time);
	Worker(std::string name, int id);
	virtual ~Worker();
};


