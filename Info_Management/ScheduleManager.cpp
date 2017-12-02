#include "ScheduleManager.h"
//For printing the week.
#include <ctime>
using namespace std;

void ScheduleManager::addAppointment(bool offDay, int day, int month, int year, int appointmentTime, Worker* worker, string name, int id, const char* DBFilePath){
	//To check time inputs.
	time_t t = time(0);
	struct tm* localTime = localtime(&t);
	//tm_year starts counting from 1900 and tm_mon starts months at 0.
	if(year < (localTime->tm_year + 1900) || ((year == localTime->tm_year + 1900) && month < (localTime->tm_mon + 1)) || ((month == localTime->tm_mon + 1) && day < localTime->tm_mday)){
		cout << "Cannot make appointments in the past." << endl;
		return;
	}
	else if(month < 1 || month > 12){
		cout << "Please input a valid month." << endl;
		return;
	}
	else if(day < 1 || day > this->daysInMonth()){
		cout << "Please input a valid day." << endl;
		return;
	}
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
	return;
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
		findAppointments(DBFilePath, worker->getWorkerID(), appointmentDate.c_str(), matchedAppointments);
		for(int i = 0; i < size; i++){
			removeAppointment(DBFilePath, matchedAppointments[i]->getAppointmentID());
		}
	}
}

//Prints the worker's schedule for the current week.
void ScheduleManager::printWorkerWeekSchedule(Worker* worker, const char* DBFilePath){
	//Find the current week.
	time_t t = time(0);
	struct tm* localTime = localtime(&t);
	//daysPastSunday is between 0 and 6 corresponding to Sunday to Saturday.
	int daysPastSunday = localTime->tm_wday;
	int startDay;
	int startMonth;
	int startYear;
	if(localTime->tm_mday - daysPastSunday <= 0){
		if(localTime->tm_mon == 0){
			startMonth = 12;
			startDay = daysInMonth(12) - daysPastSunday;
			startYear = localTime->tm_year +1900 - 1;
		}
		else{
			//Don't need to subtract a month because the months start from 0 in tm and will use months starting from 1.
			startMonth = localTime->tm_mon;
			startDay = daysInMonth(startMonth) - daysPastSunday;
			startYear = localTime->tm_year + 1900;
		}
	}
	else{
		startMonth = localTime->tm_mon + 1;
		startDay = localTime->tm_mday - daysPastSunday;
		startYear = localTime->tm_year + 1900;
	}
	cout << worker->getWorkerName() << "'s Schedule for the week of " << startDay<< "/" << startMonth << "/" << localTime->tm_year << ":" << endl;
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
		printWorkerDaySchedule(worker, startDay, startMonth, startYear, DBFilePath);
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
		cout << worker->getWorkerName() << " has the following appointments on " << appointmentDate << ": " << endl;
		Appointment** dayAppointments = new Appointment*[meetingNumber];
		//findAppointments is sorted by appointment ID, not chronologically.
		findAppointments(DBFilePath, worker->getWorkerID(), appointmentDate.c_str(), dayAppoinments);
		chronologicalSort(dayAppointments);
		for(int i = 0; i < meetingNumber; i++){
			dayAppointments[i]->printAppointment();
		}
	}
	return;
}

void ScheduleManager::chronologicalSort(Appointment** unsorted, int unsortedSize){
	//The array is already sorted if it has one element. Avoid out of bounds errors.
	if(unsortedSize > 1){
		for(int i = unsortedSize - 1; i >= 0, i--){
			for(int j = 0; j < unsortedSize - i - 1; j++){
				if(unsorted[j]->getAppointmentTime() > unsorted[i]->getAppointmentTime()){
					Appointment* temp = unsorted[j];
					unsorted[j] = unsorted[i];
					unsorted[i] = temp;
				}
			}
		}
	}
	return;
}
//Ensure days of month have two digits for proper formatting.
void ScheduleManager::numberOfDigits(int i){
	//The inputted value will have at least one digit.
	int digitNumber = 1;
	while(i/10 != 0){
		digitNumber++;
		i /= 10;
	}
	return digitNumber;
}

int ScheduleManager::daysInMonth(int month){
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