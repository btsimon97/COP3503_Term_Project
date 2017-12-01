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
	Worker* NextWorkerInList;
	std::string WorkerName;
	int workerID;
	//	AppointmentLinkedList appointments;
public:
	Worker* getNextWorker();
	void addAppointment(std::string name,int id);
	void cancelAppointment(std::string name, int id);
	void cancelAppointment(int day, int month,int time);
	void printVistorInfo(int month,int day,int time );
	void setDayOffOnce(int day);
	void setDayOffRegular(int day);
	void setTimeOffOnce(int time);
	void setTimeOffRegular(int time);
	Worker(std::string name, int id);
	virtual ~Worker();

	//	AppointmentLinkedList getAppointments() const {
	//		return appointments;
	//	}
	//
	//	void setAppointments(AppointmentLinkedList appointments) {
	//		this->appointments = appointments;
	//	}

	const Worker*& getNextWorkerInList() const {
		return NextWorkerInList;
	}

	void setNextWorkerInList(const Worker*& nextWorkerInList) {
		NextWorkerInList = nextWorkerInList;
	}

	int getWorkerId() const {
		return workerID;
	}

	void setWorkerId(int workerId) {
		workerID = workerId;
	}

	const std::string& getWorkerName() const {
		return WorkerName;
	}

	void setWorkerName(const std::string& workerName) {
		WorkerName = workerName;
	}
};

