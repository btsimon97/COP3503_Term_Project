/*
Author: J Sheldon
Description: Functions to manipulate an appointment object.
*/
#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>
#include "Visitor.h"
#include "Worker.h"
using namespace std;

class Worker;
class Appointment{
public:
	Visitor* getVisitor();
	Worker* getWorker();
	int getDay();
	int getMonth();
	int getYear();
	bool getOffDay();
	int getTimeSlot();
	int getAppointmentID();
	void printAppointment();
	Appointment(bool offDay, int day, int month, int year, int appointmentTime, Worker* worker, string visitorName, int visitorID);
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