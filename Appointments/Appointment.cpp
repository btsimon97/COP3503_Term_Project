/*
Author: J Sheldon
Description: Functions to manipulate an appointment object.
*/

#include "Appointment.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Visitor* Appointment::getVisitor(){
	return visitor;
}

Worker* Appointment::getWorker(){
	return worker;
}

int Appointment::getDay(){
	return day;
}

int Appointment::getMonth(){
	return month;
}

int Appointment::getAppointmentID(){
	return appointmentID;
}

int Appointment::getYear(){
	return year;
}

bool Appointment::getOffDay(){
	return offDay;
}

int Appointment::getAppointmentTime(){
	return appointmentTime;
}

void Appointment::printAppointmentTimeAndVisitor(){
	cout << "Appointment Time: " << appointmentTime << " hours" << endl;
	cout << endl;
	if(!offDay){
		cout << "Visitor Name: " << visitor->getVisitorName() << endl;
		cout << "Visitor ID Number: " << visitor->getVisitorID() << endl;
		cout << endl;
	}
	else{
		cout << "Scheduled time off " << endl;
		cout << endl;
	}
	return;
}

void Appointment::printAppointmentWorkerAndVisitor(){
	if(!offDay){
		cout << "Worker Name: "  << worker->getWorkerName() << endl;
		cout << "Worker ID Number " << worker->getWorkerID() << endl;
		cout << "Visitor Name: " << visitor->getVisitorName() << endl;
		cout << "Visitor ID Number: " << visitor->getVisitorID() << endl;
		cout << endl;
	}
	else{
		cout << "Scheduled time off " << endl;
		cout << endl;
	}
	return;
}

void Appointment::printAppointmentVisitor(){
	cout << endl;
	if(!offDay){
		cout << "Visitor Name: " << visitor->getVisitorName() << endl;
		cout << "Visitor ID Number: " << visitor->getVisitorID() << endl;
		cout << endl;
	}
	else{
		cout << "Scheduled time off " << endl;
		cout << endl;
	}
	return;
}

void Appointment::printAppointmentDateTimeAndWorker(){
	cout << "Appointment Time: " << appointmentTime << " hours" << endl;
	cout << "Appointment Date: " << month << "//";
	int dayLength = to_string(day).length();
	if(dayLength == 1){
		//For formatting consistency.
		cout << "0";
	}
	cout << day << "//" << year << endl;
	cout << endl;
	if(!offDay){
		cout << "Worker Name: " << worker->getWorkerName() << endl;
		cout << "Worker ID Number: " << worker->getWorkerID() << endl;
		cout << endl;
	}
	else{
		cout << "Scheduled time off " << endl;
		cout << endl;
	}
	return;
}

void Appointment::printAppointmentTimeDateAndVisitor(){
	cout << "Appointment Time: " << appointmentTime << " hours" << endl;
	cout << "Appointment Date: " << month << "//";
	int dayLength = to_string(day).length();
	if(dayLength == 1){
		//For formatting consistency.
		cout << "0";
	}
	cout << day << "//" << year << endl;
	cout << endl;
	if(!offDay){
		cout << "Visitor Name: " << visitor->getVisitorName() << endl;
		cout << "Visitor ID Number: " << visitor->getVisitorID() << endl;
		cout << endl;
	}
	else{
		cout << "Scheduled time off " << endl;
		cout << endl;
	}
	return;
}

Appointment::Appointment(bool offDay, int day, int month, int year, int appointmentTime, Worker* worker, string visitorName, int visitorID){
	this->offDay = offDay;
	this->day = day;
	this->month = month;
	this->year = year;
	this->worker = worker;
	this->appointmentTime = appointmentTime;
	this->appointmentID = appointmentID;
	this->visitor = new Visitor(visitorID, visitorName);
}

Appointment::~Appointment(){
	//Do not delete the worker because it may be attached to other appointments.
	delete visitor;
}
