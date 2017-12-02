/*
 * Worker.cpp
 *
 *  Created on: Nov 3, 2017
 *      Author: David
 */

#include "Worker.h"
#include <iostream>
#include <string>
std::string Worker::Worker(std:: string name, int id){
	this->workerName = name;
	this->workerID = id;
	this->workingDays = "M,T,W,R,F,S,U";
}

std::string Worker::getWorkerName(){
	return workerName;
}

int Worker::getWorkerID(){
	return workerID;
}

std::string Worker::getWorkingDays(){
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