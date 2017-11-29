#include "AppointmentLinkedList.h"
#include <iostream>
using namespace std;
void AppointmentLinkedList::printAppointments(){
	Appointment* currentAppointment = head;
	while(currentAppointment != NULL){
		currentAppointment->printAppointment();
		currentAppointment = currentAppointment->getNextAppointment();
		cout << endl;
	}
	return;
}

Appointment* AppointmentLinkedList::getHeadAppointment(){
	return head;
}

Appointment* AppointmentLinkedList::getTailAppointment(){
	return tail;
}

void AppointmentLinkedList::addAppointment(bool offDay, int day, int month, int year, int timeSlot, Worker* worker, string name, int id){
	if(this->slotFree(Appointment (offDay, day, month, year, timeSlot, worker, name, id))){
		try{
			this->tail->setNextAppointment(new Appointment(offDay, day, month, year, timeSlot, worker, name, id));
		}
		catch(string message){
			cout << message << endl;
		}
		this->tail = tail->getNextAppointment();
		if(this->head == NULL){
			this->head = this->tail;
		}
	//Can be used for debugging and confirmation of addition to user.
		cout << "Successfully added appointment." << endl;
	}
	else{
		cout << "Time slot already full. Could not make appointment." << endl;
	}
	return;
}

void AppointmentLinkedList::cancelAppointment(string name, int id){
	Appointment* current = head;
	if(current->getVisitor()->getVisitorName() == name && current->getVisitor()->getVisitorID() == id){
		if(current == this->tail){
			tail = current->getNextAppointment();
		}
		this->head = current->getNextAppointment();
		delete  current;
		cout << "Successfully cancelled appointment." << endl;
		return;
	}
	else{
		//Need to check from the next appointment to relink the list.
		while(current->getNextAppointment() != NULL){
			if(current->getNextAppointment()->getVisitor()->getVisitorName() == name && current->getNextAppointment()->getVisitor()->getVisitorID() == id){
				Appointment* next = current->getNextAppointment()->getNextAppointment();
				delete current->getNextAppointment();
				current->setNextAppointment(next);
				if(next == NULL){
					this->tail = current;
				}
				cout << "Successfully cancelled appointment." << endl;
				return;
			}
			current = current->getNextAppointment();
		}
	}
	cout << "Appointment not found." << endl;
	return;
}

void AppointmentLinkedList::cancelAppointment(int day, int month, int year, int time){
	Appointment* current = head;
	if(current->getMonth() == month && current->getDay() == day && current->getYear() == year && current->getTimeSlot() == time){
		if(current == this->tail){
			tail = current->getNextAppointment();
		}
		this->head = current->getNextAppointment();
		delete  current;
		cout << "Successfully cancelled appointment." << endl;
		return;
	}
	else{
		//Need to check from the next appointment to relink the list.
		while(current->getNextAppointment() != NULL){
			if(current->getNextAppointment()->getMonth() == month && current->getNextAppointment()->getDay() == day && current->getNextAppointment()->getTimeSlot() == time){
				Appointment* next = current->getNextAppointment()->getNextAppointment();
				delete current->getNextAppointment();
				current->setNextAppointment(next);
				if(next == NULL){
					this->tail = current;
				}
				cout << "Successfully cancelled appointment." << endl;
				return;
			}
			current = current->getNextAppointment();
		}
	}
	cout << "Appointment not found." << endl;
	return;
}

void AppointmentLinkedList::printVisitorInfo(string visitorName, int visitorID){
	Appointment* current = head;
	while(current != NULL){
		if(current->getVisitor()->getVisitorName() == visitorName && current->getVisitor()->getVisitorID() == visitorID){
			cout << "Visitor name: " << visitorName << endl; 
			cout << "Visitor ID: " << visitorID << endl;
			return;
		}
		current = current->getNextAppointment();
	}
	cout << "No such visitor found in the system. " << endl;
	return;
}

void AppointmentLinkedList::printVisitorInfo(int day, int month, int year, int timeSlot){
	Appointment* current = head;
	while(current != NULL){
		if(current->getDay() == day && current->getMonth() == month && current->getYear() == year && current->getTimeSlot() == timeSlot){
			cout << "Visitor name: " << current->getVisitor()->getVisitorName()<< endl; 
			cout << "Visitor ID: " << current->getVisitor()->getVisitorID()<< endl;
			return;
		}
		current = current->getNextAppointment();
	}
	cout << "No visitor found to have an appointment on this date. " << endl;
	return;
}

//Added a constructor to ensure head and tail are NULL when the list is first created.
AppointmentLinkedList::AppointmentLinkedList(){
	head = NULL;
	tail = NULL;
}

AppointmentLinkedList::~AppointmentLinkedList(){
	Appointment* currentAppointment = head;
	while(currentAppointment != NULL){
		Appointment* nextAppointment = currentAppointment->getNextAppointment();
		delete currentAppointment;
		currentAppointment = nextAppointment;
	}
}

bool AppointmentLinkedList:: slotFree(Appointment attemptedAddition){
	Appointment* current = this->head;
	while(current != NULL){
		if(*current == attemptedAddition){
			return false;
		}
		current = current->getNextAppointment();
	}
	return true;
}
