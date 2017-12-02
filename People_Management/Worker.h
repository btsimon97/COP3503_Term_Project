/*
 * Worker.h
 *
 *  Created on: Nov 3, 2017
 *      Author: David
 */
#include <iostream>
#include <string>
using namespace std;
#ifndef WORKER_H_
#define WORKER_H_

class Worker {
private:
	string workerName;
	int workerID;
	string workingDays;
public:
	string getWorkerName();
	string getWorkingDays();
	void giveDayOff(char day);
	int getWorkerID();
	Worker(string name, int id);
};

