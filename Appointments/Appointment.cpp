#include "Appointment.h"
#include <iostream>
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

void Appointment::printAppointment(){
	cout << "Appointment Time: " << appointmenTime << " hours" << endl;
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
	//Seed for random number generator with time.
	srand(time(NULL));
	this->offDay = offDay;
	this->day = day;
	this->month = month;
	this->year = year;
	this->worker = worker;
	this->appointmentTime = appointmentTime;
	this->visitor = new Visitor(visitorName, visitorID);
	this->appointmentID = 0;
	//Need a countAppointments function here.
	while(countMatchingAppointments(appointmentID) != 0){
		appointmentID = rand();
	}
}

Appointment::~Appointment(){
	//Do not delete the worker because it may be attached to other appointments.
	delete visitor;
}
