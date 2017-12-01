/*
 * Worker.h
 *
 *  Created on: Nov 3, 2017
 *      Author: David
 */

#ifndef WORKER_H_
#define WORKER_H_
#include <iostream>
#include <string>

class Worker {
private:
	Worker* nextWorkerInList;
	std::string workerName;
	int workerID;
	int daysOff;
	int timeSlotOff;
		AppointmentLinkedList appointments;
public:
	Worker* getNextWorker();
	void setDayOffOnce(int day);
	void setDayOffRegular(int day);
	void setTimeOffOnce(int time);
	void setTimeOffRegular(int time);
	Worker(std::string name, int id);
	virtual ~Worker();

		AppointmentLinkedList getAppointments() const {
			return appointments;
		}

		void setAppointments(AppointmentLinkedList appointments) {
			this->appointments = appointments;
		}

	const Worker*& getNextWorkerInList() const {
		return nextWorkerInList;
	}

	void setNextWorkerInList(const Worker*& nextWorkerInList) {
		this->nextWorkerInList = nextWorkerInList;
	}

	int getWorkerId() const {
		return workerID;
	}

	void setWorkerId(int workerId) {
		workerID = workerId;
	}

	const std::string& getWorkerName() const {
		return workerName;
	}

	void setWorkerName(const std::string& workerName) {
		this->workerName = workerName;
	}
};

