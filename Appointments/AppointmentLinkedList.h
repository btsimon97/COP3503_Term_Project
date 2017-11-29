#ifndef APPOINTMENTLINKEDLIST_H
#define APPOINTMENTLINKEDLIST_H

#include <string>
#include "Appointment.h"
#include "Visitor.h"
#include "Worker.h"
#include "AppointmentLinkedList.h"
using namespace std;

class Appointment;
class Visitor;
class Worker;
class AppointmentLinkedList{
public:
	void printAppointments();
	Appointment* getHeadAppointment();
	Appointment* getTailAppointment();
	//Add and cancel functions added to the linked list different from UML diagram because they seemed more 
	//appropriate in the AppointmentLinkedList class.
	//To add an appointment, the class needs a date and worker as well as visitor information. Changed from UML
	//diagram.
	void addAppointment(bool offDay, int day, int month, int year, int timeSlot, Worker* worker, string name, int id);
	void cancelAppointment(string name, int id);
	void cancelAppointment(int day, int month, int year, int time);
	void printVisitorInfo(string visitorName, int visitorID);
	void printVisitorInfo(int day, int month, int year,  int timeSlot);
	AppointmentLinkedList();
	~AppointmentLinkedList();
private:
	Appointment* head;
	Appointment* tail;
	//Extra function to check if appointment slot already full. Used with addAppointment function.
	bool slotFree(Appointment attemptedAddition);
};
#endif /*APPOINTMENTLINKEDLIST_H */