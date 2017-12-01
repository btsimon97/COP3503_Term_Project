#include "ScheduleManager.h"
#include "Appointment.h"
#include "Worker.h"
#include "Visitor.h"
using namespace std;

ScheduleManager::ScheduleManager(int appointmentLength){
	//Avoid divide-by-zero error by checking = 0.
	if(appointmentLength <= 0 || appointmentLength > (dayLength*60)){
		throw string("Please enter a valid appointment length.");
	}
	this->appointmentLength = appointmentLength;
}

void ScheduleManager::addAppointment(bool offDay, int day, int month, int year, int appointmentTime, Worker* worker, string name, int id, const char* DBFilePath){
	string appointmentDate = to_string(month) + "//";
	if(numberOfDigits(day) == 1){
		appointmentDate += ("0" + to_string(day));
	}
	else{
		appointmentDate += to_string(day);
	}
	appointmentDate +=  ("//" +  to_string(year));
	if(countMatchingAppointments(DBFilePath, worker->getWorkerID(), appointmentDate.c_str(), appointmentTime) == 0){
		addNewAppointment(DBFilePath, id, appointmentDate.c_str(), appointmentTime);
	}
	else{
		cout << "An appointment has already been scheduled for this time." << endl;
	}
}

void ScheduleManager::cancelAppointment(int id, const char* DBFilePath){
	//Do not know which function to use to find appointments with a visitor name string and id.
	int size = countMatchingAppointments(DBFilePath, id);
	if(size == 0){
		cout << "No appointment was found" << endl;
	}
	else{
		Appointment** matchedAppointments = new Appointment*[size];
		for(int i = 0; i < size; i++){
			removeAppointment(matchedAppontments[i]->getAppointmentID());
		}
	}
}

void ScheduleManager::cancelAppointment(int day, int month, int year, int appointmentTime, const char* DBFilePath){
	string appointmentDate = to_string(month) + "//";
	if(numberOfDigits(day) == 1){
		appointmentDate += ("0" + to_string(day));
	}
	else{
		appointmentDate += to_string(day);
	}
	appointmentDate +=  ("//" +  to_string(year));
	int size = countMatchingAppointments(DBFilePath, appointmentDate, appointmentTime);
	if(size == 0){
		cout << "No such appointment found. "
	}
	else{
		Appointment** matchedAppointments = new Appointment*[size];
		for(int i = 0; i < size; i++){
			removeAppointment(DBFilePath, matchedAppointments[i]->getAppointmentID());
		}
	}
}

void ScheduleManager::printWorkerWeekSchedule(){

}

void ScheduleManager::printWorkerDaySchedule(Worker* worker, int day, int month, int year, const char* DBFilePath){
	string appointmentDate = to_string(month) + "//";
	if(numberOfDigits(day) == 1){
		appointmentDate += ("0" + to_string(day));
	}
	else{
		appointmentDate += to_string(day);
	}
	appointmentDate +=  ("//" +  to_string(year));
	int meetingNumber = countMatchingAppointments(DBFilePath, worker->getWorkerID(), appointmentDate.c_str());
	if(meetingNumber == 0){
		cout << "No appointments on " << appointmentDate << endl;
	}
	else{
		Appointment** dayAppointments = new Appointment*[meetingNumber];
		findAppointments(DBFilePath, worker->getWorkerID(), appointmentDate.c_str(), dayAppoinments);
		for(int i = 0; i < meetingNumber; i++){
			dayAppointments[i]->printAppointment();
		}
	}
	return;
}

void ScheduleManager::scheduleNearestAppointment(){

}

void ScheduleManager::numberOfDigits(int i){
	//The inputted value will have at least one digit.
	int digitNumber = 1;
	while(i/10 != 0){
		digitNumber++;
		i /= 10;
	}
	return digitNumber;
}