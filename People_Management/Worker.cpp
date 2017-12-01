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
	Worker* NextWorkerInList;
	std::string WorkerName;
	int workerID;
	//	AppointmentLinkedList appointments;
public:
	Worker* getNextWorker(){
		return NextWorkerInList;
	}
	void addAppointment(std::string name,int id){

	}
	void cancelAppointment(std::string name, int id){

	}
	void cancelAppointment(int day, int month,int time){

	}
	void printVistorInfo(int month,int day,int time ){

	}
	void setDayOffOnce(int day){

	}
	void setDayOffRegular(int day);
	void setTimeOffOnce(int time);
	void setTimeOffRegular(int time);
	Worker(std::string name, int id);
	virtual ~Worker();
};


