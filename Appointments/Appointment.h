#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include "Visitor.h"
#include "Worker.h"
using namespace std;

class Worker;
class Appointment{
public:
	Appointment* getNextAppointment();
	void setNextAppointment(Appointment* nextAppointment);
	Visitor* getVisitor();
	Worker* getWorker();
	int getDay();
	int getMonth();
	int daysInMonth();
	int getYear();
	bool getOffDay();
	int getTimeSlot();
	void printAppointment();
	//Used to check if an appointment slot is already full.
	bool operator == (const Appointment compared);
	Appointment(bool offDay, int day, int month, int year, int timeSlot, Worker* worker, string visitorName, int visitorID);
	~Appointment();
private:
	bool offDay;
	int day;
	int month;
	int year;
	int timeSlot;
	Visitor* visitor;
	Worker* worker;
	Appointment* nextAppointment;
};
#endif /* APPOINTMENT_H */