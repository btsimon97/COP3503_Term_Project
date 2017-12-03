/*
Author: J Sheldon
Description: Functions to check validity of workers and appointments before writing them to a data base, removing from the data base, and printing.
*/

#include "ScheduleManager.h"
//For printing the week.
#include <ctime>
#include <stdlib.h>
#include <iostream>
using namespace std;

void ScheduleManager::addAppointment(bool offDay, int day, int month, int year, int appointmentTime, int workerID, int visitorID, string DBFilePath){
	//To check time inputs.
	time_t t = time(0);
	struct tm* localTime = localtime(&t);
	Worker* worker = &getWorker(DBFilePath, workerID);
	//tm_year starts counting from 1900 and tm_mon starts months at 0.
	if(year < (localTime->tm_year + 1900) || ((year == localTime->tm_year + 1900) && month < (localTime->tm_mon + 1)) || ((month == localTime->tm_mon + 1) && day < localTime->tm_mday)){
		cout << "Cannot make appointments in the past." << endl;
		return;
	}
	else if(month < 1 || month > 12){
		cout << "Please input a valid month." << endl;
		return;
	}
	else if(day < 1 || day > this->daysInMonth(month, year)){
		cout << "Please input a valid day." << endl;
		return;
	}
	time_t = time(0);
	//Set up a time to get a day of the week for that date.
	struct tm* potentialAppointmentDate;
	potentialAppointmentDate->tm_mday = day;
	potentialAppointmenDate->tm_mon = month - 1;
	potentialAppointmentDate->tm_year = year - 1900;
	char weekDay;
	switch(potentialAppointment->tm_wday){
		case 0:
		weekDay = 'U';
		break;
		case 1:
		weekDay = 'M';
		break;
		case 2:
		weekDay = 'T';
		break;
		case 3:
		weekDay = 'W';
		break;
		case 4:
		weekDay = 'R';
		break;
		case 5: 
		weekDay = 'F';
		break;
		case 6:
		weekDay = 'S';
		break;
	}
	int dayInWorkWeek = worker->getWorkingDays().find(weekDay);
	//find returns -1 if the character is not found in the string.
	if(dayInWorkWeek == -1){
		cout << "The worker has this day off." << endl;
		return;
	}
	string appointmentDate = to_string(month) + "//";
	//Date value needs to have two digits for manipulation.
	//.length() gives unsigned integer, which causes issues with comparisons.
	int dayDigits = to_string(day).length();
	if(dayDigits == 1){
		appointmentDate += ("0" + to_string(day));
	}
	else{
		appointmentDate += to_string(day);
	}
	appointmentDate +=  ("//" +  to_string(year));
	if(countMatchingAppointments(DBFilePath, workerID, appointmentDate.c_str(), appointmentTime) == 0){
		int appointmentID = appointmentIDGenerator();
		addNewAppointment(DBFilePath, appointmentID,appointmentDate.c_str(), appointmentTime, workerID, visitorID, offDay);
	}
	else{
		cout << "An appointment has already been scheduled for this time." << endl;
	}
	delete worker;
	return;
}

void ScheduleManager::cancelAppointment(int day, int month, int year, int appointmentTime, string DBFilePath){
	string appointmentDate = to_string(month) + "//";
	if(numberOfDigits(day) == 1){
		appointmentDate += ("0" + to_string(day));
	}
	else{
		appointmentDate += to_string(day);
	}
	appointmentDate +=  ("//" +  to_string(year));
	int size = countMatchingAppointments(DBFilePath, appointmentDate.c_str(), appointmentTime);
	if(size == 0){
		cout << "No such appointment found." << endl;
	}
	else{
		Appointment** matchedAppointments = new Appointment*[size];
		findAppointments(DBFilePath, appointmentDate.c_str(), matchedAppointments);
		for(int i = 0; i < size; i++){
			removeAppointment(DBFilePath, matchedAppointments[i]->getAppointmentID());
		}
	}
}

//Prints the worker's schedule for the current week.
void ScheduleManager::printWorkerWeekSchedule(int workerID, string DBFilePath){
	//Find the current week.
	time_t t = time(0);
	struct tm* localTime = localtime(&t);
	Worker* worker = &getWorker(DBFilePath, workerID);
	//daysPastSunday is between 0 and 6 corresponding to Sunday to Saturday.
	int daysPastSunday = localTime->tm_wday;
	int startDay;
	int startMonth;
	int startYear;
	if(localTime->tm_mday - daysPastSunday <= 0){
		if(localTime->tm_mon == 0){
			startMonth = 12;
			startYear = localTime->tm_year +1900 - 1;
			startDay = daysInMonth(12, startYear) - daysPastSunday;
		}
		else{
			//Don't need to subtract a month because the months start from 0 in tm and will use months starting from 1.
			startMonth = localTime->tm_mon;
			startYear = localTime->tm_year + 1900;
			startDay = daysInMonth(startMonth, startYear) - daysPastSunday;
		}
	}
	else{
		startMonth = localTime->tm_mon + 1;
		startDay = localTime->tm_mday - daysPastSunday;
		startYear = localTime->tm_year + 1900;
	}
	cout << worker->getWorkerName() << "'s Schedule for the week of " << startMonth<< "/" << startDay << "/" << startYear << ":" << endl;
	for(int i = 0; i < 7; i++){
		switch(daysPastSunday){
			case 0:
			cout << "Sunday Appointments:" << endl;
			break;
			case 1:
			cout << "Monday Appointments:" << endl;
			break;
			case 2:
			cout << "Tuesday Appointments:" << endl;
			break;
			case 3:
			cout << "Wednesday Appointments:" << endl;
			break;
			case 4:
			cout << "Thursday Appointments:" << endl;
			break;
			case 5:
			cout << "Friday Appointments:" << endl;
			break;
			case 6:
			cout << "Saturday Appointments:" << endl;
			break;
		}
		printWorkerDaySchedule(workerID, startDay, startMonth, startYear, DBFilePath);
		if(startDay + 1 > daysInMonth(startMonth)){
			if(startMonth == 12){
				startYear++;
				startMonth = 1;
			}
			else{
				startMonth++;
			}
			startDay = 1;
		}
		else{
			startDay++;
		}
	}
	return;
	delete worker;
}

void ScheduleManager::printWorkerDaySchedule(int workerID, int day, int month, int year, string DBFilePath){
	Worker* worker = &getWorker(DBFilePath, workerID);
	string appointmentDate = to_string(month) + "//";
	if(numberOfDigits(day) == 1){
		appointmentDate += ("0" + to_string(day));
	}
	else{
		appointmentDate += to_string(day);
	}
	appointmentDate +=  ("//" +  to_string(year));
	int meetingNumber = countMatchingAppointments(DBFilePath, workerID, appointmentDate.c_str());
	if(meetingNumber == 0){
		cout << "No appointments on " << appointmentDate << endl;
	}
	else{
		cout << worker->getWorkerName() << " has the following appointments on " << appointmentDate << ": " << endl;
		Appointment** dayAppointments = new Appointment*[meetingNumber];
		//findAppointments is sorted by appointment ID, not chronologically.
		findAppointments(DBFilePath, workerID, appointmentDate.c_str(), dayAppointments);
		chronologicalSort(dayAppointments, meetingNumber);
		for(int i = 0; i < meetingNumber; i++){
			dayAppointments[i]->printAppointmentTimeAndVisitor();
		}
	}
	delete worker;
	return;
}

void ScheduleManager::chronologicalSort(Appointment** unsorted, int unsortedSize){
	//The array is already sorted if it has one element. Avoid out of bounds errors.
	if(unsortedSize > 1){
		for(int i = unsortedSize - 1; i >= 0; i--){
			for(int j = 0; j < unsortedSize - i - 1; j++){
				if(unsorted[j]->getAppointmentTime() > unsorted[i]->getAppointmentTime() && (unsorted[j]->getYear() >= unsorted[i]->getYear() && (unsorted[j]->getDay() >= unsorted[j]->getDay() || unsorted[j]->getMonth() > unsorted[i]->getMonth())){
					Appointment* temp = unsorted[j];
					unsorted[j] = unsorted[i];
					unsorted[i] = temp;
				}
			}
		}
	}
	return;
}

int ScheduleManager::appointmentIDGenerator(){
	int appointmentID = 0;
	srand(time(NULL));
	while(countMatchingAppointments(appointmentID) != 0){
		appointmentID = rand();
	}
	return appointmentID;
}

void ScheduleManager::addWorker(int workerID, string workerName, string daysAvailable, int startHour, int startMinute, int stopHour, int stopMinute, string DBFilePath){
	if(countMatchingWorkers(DBFilePath, workerName.c_str()) != 0){
		cout << "Worker by the name " << workerName << " already employed here." << endl;
		return;
	}
	else if(startHour > 24 || startHour < 0 || stopHour > 24 || stopHour < 0){
		cout << "Invalid hour entry." << endl;
		return;
	}
	else if(startMinute < 0 || startMinute >= 60 || stopMinute < 0 || stopMinute >= 60){
		cout << "Invalid minute entry." << endl;
		return;
	}
	addNewWorker(DBFilePath, workerID, workerName.c_str(), daysAvailable.c_str(), startHour, startMinute, stopHour, stopMinute);
	return;
}

void ScheduleManager::fireWorker(string DBFilePath, int workerID){
	removeWorker(DBFilePath, workerID);
	return;
}

int ScheduleManager::daysInMonth(int month, int year){
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

bool ScheduleManager::isBlank(string checkedString){
	bool isBlank = true;
	signed int size = checkedString.length();
	for(int i = 0; i < size; i++){
		if(checkedString.at(i) != ' '){
			isBlank = false;
		}
	}
	return isBlank;
}

void ScheduleManager::printAllWorkerAppointments(int workerID, string DBFilePath){
	int count = countMatchingAppointments(DBFilePath, workerID, true);
	Worker* worker = &getWorker(DBFilePath, workerID);
	if(count == 0){
		cout << worker->getWorkerName() << " has no appointments scheduled." << endl;
	}
	else{
		Appointment** matchedAppointments = new Appointment*[count];
		findAppointments(DBFilePath, workerID, true, matchedAppointments);
		chronologicalSort(matchedAppointments, count);
		cout << worker->getWorkerName() << " has the following appointments scheduled." << endl;
		for(int i = 0; i < count; i++){
			matchedAppointments[i]->printAppointmentTimeDateAndVisitor();
		}
	}
	return;
}

void ScheduleManager::printAppointmentsOnDateAndTime(int day, int month, int year, int appointmentTime, string DBFilePath){
	string appointmentDate = to_string(month) + "//";
	if(numberOfDigits(day) == 1){
		appointmentDate += ("0" + to_string(day));
	}
	else{
		appointmentDate += to_string(day);
	}
	appointmentDate +=  ("//" +  to_string(year));
	int count = countMatchingAppointments(DBFilePath, appointmentDate, appointmentTime);
	if(count == 0){
		cout << "No appointments found on this date and time." << endl;
	}
	else{
		cout << "The following appointments are scheduled on " << appointmentDate << " at " << appointmentTime << " hours:" < endl;
		Appointment** matchedAppointments = new Appointment*[count];
		findAppointments(DBFilePath, appointmentDate, appointmentTime);
		for(int i = 0; i < count, i++){
			matchingAppointments[i]->printWorkerAndVisitor();
		}
	}
	return;
}

void ScheduleManager::printVisitorAppointments(int visitorID, string DBFilePath){
	int count = countMatchingAppointments(DBFilePath, visitorID, false);
	if(count == 0){
		cout << "No appointments found for this visitor." << endl;
	}
	else{
		string name = getVisitorName(DBFilePath, visitorID);
		cout << "The following appointments are scheduled with " << name << ":" << endl;
		Appointment** matchedAppointments = new Appointment*[count];
		findAppointments(DBFilePath, name.c_str(), matchedAppointments);
		for(int i = 0; i < count, i++){
			matchingAppointments[i]->printAppointmentDateTimeAndWorker();
		}
	}
	return;
}

