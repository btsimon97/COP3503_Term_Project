/*
 * WorkerLinkedList.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: David
 */

#include "WorkerLinkedList.h"

namespace std {
class WorkerLinkedList {
private:
	Worker *head;
	Worker *tail;
public:
	void printWorkerWeekSchedule(std::string name,int id,int year, int month, int weekOfMonth){
		Worker* cursor = head;
		while(cursor->workerID!=id){
			cursor = cursor->getNextWorkerInList();
		}
		if(cursor->getNextWorkerInList()==NULL){
			cout << "Could not find the worker with that id"<<endl;
		}
		else{
			int firstDayToScan;
			int lastDayToScan;
			int lastMonthToScan=month;
			int lastYearToScan=year;
			firstDayToScan=((weekOfMonth-1)*7)+1;
			int lastDayToScan=firstDayToScan+6;
			if(lastDayToScan>Appointment::daysInMonth()){
				lastDayToScan = lastDayToScan- Appointment::daysInMonth();
				lastMonthToScan++;
				if(lastMonthToScan==13){
					lastYearToScan++;
					lastMonthToScan=1;
				}
			}
			Appointment currentAppointment = Worker::appointments.head;
			if(((currentAppointment.Appointment::getDay()>=firstDayToScan)&&(currentAppointment.Appointment::getMonth()==month))||(
					(currentAppointment.Appointment::getDay()<=lastDayToScan)&&
					(currentAppointment.Appointment::getMonth()==lastMonthToScan)&&
					(currentAppointment.Appointment::getYear()==lastYearToScan))
					){
				currentAppointment.printAppointment();
			}
			while(currentAppointment.getNextAppointment()!=NULL){
				if(((currentAppointment.Appointment::getDay()>=firstDayToScan)&&(currentAppointment.Appointment::getMonth()==month))||(
									(currentAppointment.Appointment::getDay()<=lastDayToScan)&&
									(currentAppointment.Appointment::getMonth()==lastMonthToScan)&&
									(currentAppointment.Appointment::getYear()==lastYearToScan))
									){
					currentAppointment.printAppointment();
				}
			}

		}

	}
	Worker* getHeadWorker(){
		return head;
	}
	Worker* getTailWorker(){
		return tail;
	}
	WorkerLinkedList(){
		head= NULL;
		tail= NULL;
	}
};

}
