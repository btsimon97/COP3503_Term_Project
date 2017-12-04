/*
Author: J Sheldon
Description: Functions to manipulate an appointment object.
*/
#include <string>
#include "../People_Management/Visitor.h"
#include "../People_Management/Worker.h"

using namespace std;

#ifndef APPOINTMENT_H
#define APPOINTMENT_H



class Worker;
class Appointment{
public:
	Visitor* getVisitor();
	Worker* getWorker();
	int getDay();
	int getMonth();
	int getYear();
	bool getOffDay();
	int getAppointmentID();
	int getAppointmentTime();
	//Different print functions to avoid reprinting same information for each appointment in a certain category.
	//Use with worker week schedule.
	void printAppointmentTimeAndVisitor();
	//Use when searching by visitor.
	void printAppointmentDateTimeAndWorker();
	//Use when searching by date and time.
	void printAppointmentWorkerAndVisitor();
	//Use when searching by worker, date, and time.
	void printAppointmentVisitor();
	void printAppointmentTimeDateAndVisitor();
	Appointment(bool offDay, int day, int month, int year, int appointmentTime, Worker* worker, string visitorName, int visitorID, int appointmentID);
	~Appointment();
private:
	bool offDay;
	int day;
	int month;
	int year;
	int appointmentID;
	int appointmentTime;
	Visitor* visitor;
	Worker* worker;
};
#endif /* APPOINTMENT_H */
