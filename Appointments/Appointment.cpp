#include "Appointment.h"
#include <iostream>
//To get current date and time.
#include <ctime>
using namespace std;
Appointment* Appointment::getNextAppointment(){
	return nextAppointment;
}

void Appointment::setNextAppointment(Appointment* nextAppointment){
	this->nextAppointment = nextAppointment;
	return;
}

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

int Appointment::daysInMonth(){
	switch(month){
		case 1:
		return 31;
		break;
		case 2:
		if(year%4 == 0 && (year%100 != 0 || year%400 == 0)){
			return 29;
		}
		else{
			return 28;
		}
		break;
		case 3:
		return 31;
		break;
		case 4:
		return 30;
		break;
		case 5:
		return 31;
		break;
		case 6:
		return 30;
		break;
		case 7:
		return 31;
		break;
		case 8:
		return 31;
		break;
		case 9:
		return 30;
		break;
		case 10:
		return 31;
		break;
		case 11:
		return 30;
		break;
		case 12:
		return 31;
		break;
		default:
		cout << "Invalid month." << endl;
		return -1;
		break;
	}
}

int Appointment::getYear(){
	return year;
}

bool Appointment::getOffDay(){
	return offDay;
}

int Appointment::getTimeSlot(){
	return timeSlot;
}

void Appointment::printAppointment(){
	if(!offDay){
		cout << "Appointment Information: " << endl;
		cout << endl;
		cout << "Appointment holding visitor: " << endl;
		cout << "Name: " << visitor->getVisitorName() << endl;
		cout << "ID Number: " << visitor->getVisitorID() << endl;
		cout << endl;
		cout << "Appointment holding worker: " << endl;
	//Need functions to access the worker's information.
		cout << "Name: " << worker->getWorkerName() << endl;
		cout << "ID Number: " << worker->getWorkerID() << endl;
	}
	else{
		cout << worker->getWorkerName() << " has a scheduled day off on  " << this->getDay() << "\\" << this->getMonth() << "\\" << this->getYear() << endl;
	}
	return;
}

bool Appointment:: operator == (Appointment compared){
	//Use -1 time slot for an entire day off.
	if(compared.getDay() == day && compared.getMonth() == month && compared.getYear() == year  && compared.getWorker() == worker && (compared.getTimeSlot() == timeSlot || timeSlot == -1)){
		return true;
	}
	return false;
}

Appointment::Appointment(bool offDay, int day, int month, int year, int timeSlot, Worker* worker, string visitorName, int visitorID){
	time_t t = time(0);
	struct tm* localTime = localtime(&t);
	//tm_year starts counting from 1900 and tm_mon starts months at 0.
	if(year < (localTime->tm_year + 1900) || ((year == localTime->tm_year + 1900) && month < (localTime->tm_mon + 1)) || ((month == localTime->tm_mon + 1) && day < localTime->tm_mday)){
		throw string("Cannot make appointments in the past.");
	}
	else if(month < 1 || month > 12){
		throw string("Please input a valid month.");
	}
	else if(day < 1 || day > this->daysInMonth()){
		throw string("Please input a valid day.");
	}
	this->offDay = offDay;
	this->day = day;
	this->month = month;
	this->year = year;
	this->timeSlot = timeSlot;
	this->worker = worker;
	this->visitor = new Visitor(visitorName, visitorID);
	//The appointments are always added to the end of the linked list. A new appointment should always
	//have a Null next appointment. 
	this->nextAppointment = NULL;
}

Appointment::~Appointment(){
	//Do not delete the worker because it may be attached to other appointments.
	delete visitor;
}
