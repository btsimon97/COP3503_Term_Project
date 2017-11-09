Appointment* Appointment::getNextAppointment(){
	return nextAppointment;
}

Visitor* Appointment::getVisitor(){
	return visitor;
}

Worker* Appointment::getWorker(){
	return worker;
}

int Appointment::getMonth(){
	return month;
}

int Appointment::getDay(){
	return day;
}

int Appointment::getTimeSlot(){
	return timeSlot;
}

//This requires #include <iostream>
void Appointment::printAppointment(){
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
	return;
}

Appointment::Appointment(int month, int day, int timeSlot, Worker* worker, string visitorName, int visitorID){
	month = month;
	day = day;
	timeSlot = timeSlot;
	worker = worker;
	visitor = new Visitor(visitorName, visitorID);
	//The appointments are always added to the end of the linked list. A new appointment should always
	//have a Null next appointment. 
	nextAppointment = NULL;
}

Appointment::~Appointment(){
	//Do not delete the worker because it may be attached to other appointments.
	delete visitor;
}