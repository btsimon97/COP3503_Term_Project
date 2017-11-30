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
public:
	Worker();
	Worker* getNextWorker();
	void addAppointment(string name,int id:);
	void cancelAppointment(string name, int id);
	void cancelAppointment(int day, int month,int time);
	void printVistorInfo(int month,int day,int time );
	void setDayOffOnce(int day);

};

