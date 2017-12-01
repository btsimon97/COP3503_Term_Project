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
	AppointmentLinkedList appointments;
public:
	Worker* getNextWorker(){
		return nextWorkerInList;
	}
	void setDayOffOnce(int day);
	void setDayOffRegular(int day);
	void setTimeOffOnce(int time);
	void setTimeOffRegular(int time);
	Worker(std::string name, int id);
	virtual ~Worker();

	const AppointmentLinkedList& getAppointments() const {
		return appointments;
	}

	void setAppointments(const AppointmentLinkedList& appointments) {
		this->appointments = appointments;
	}

	const Worker*& getNextWorkerInList() const {
		return nextWorkerInList;
	}

	void setNextWorkerInList(const Worker*& nextWorkerInList) {
		this->nextWorkerInList = nextWorkerInList;
	}

	int getWorkerID() const {
		return workerID;
	}

	void setWorkerID(int workerId) {
		workerID = workerId;
	}

	const std::string& getWorkerName() const {
		return workerName;
	}

	void setWorkerName(const std::string& workerName) {
		this->workerName = workerName;
	}
};


