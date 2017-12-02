/*
 * Worker.h
 *
 *  Created on: Nov 3, 2017
 *      Author: David
 */
#include <iostream>
#include <string>
#ifndef WORKER_H_
#define WORKER_H_

class Worker {
private:
	std::string workerName;
	int workerID;
	std:: string workingDays;
public:
	std::string getWorkerName();
	std::string getWorkingDays();
	void giveDayOff(char day);
	int getWorkerID();
	Worker(std::string name, int id);
};

