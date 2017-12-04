/*
 * Worker.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: David
 */

#include "Worker.h"
#include <iostream>
#include <string>
using namespace std;
Worker::Worker(string name, int id, int startTime, int stopTime, string workingDays){
	this->workerName = name;
	this->workerID = id;
	this->workingDays = workingDays;
	this->startTime = startTime;
	this->stopTime = stopTime;
}

string Worker::getWorkerName(){
	return workerName;
}

int Worker::getWorkerID(){
	return workerID;
}

string Worker::getWorkingDays(){
	return workingDays;
}

void Worker::giveDayOff(char day){
	if( day == 'M' || day == 'T' || day == 'W' || day == 'R' || day == 'F' || day == 'S' || day == 'U'){
		//Possibly use DB Function here;
	}
	else{
		cout << "Please input a valid day." << endl;
	}
	return;
}
