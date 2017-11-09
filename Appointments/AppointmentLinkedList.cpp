//Some confusion about what this program must do specifically. Currently prints all of a worker's appointments.
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

//Added a constructor to ensure head and tail are NULL when the list is first created.
AppointmentLinkedList::AppointmentLinkedList(){
	head = NULL;
	tail = NULL;
}

AppointmentLinkedList::~AppointmentLinkedList(){
	Appointment* currentAppointment = head;
	while(currentAppointment != NULL){
		Appointment nextAppointment = currentAppointment->getNextAppointment();
		delete currentAppointment;
		currentAppointment = nextAppointment;
	}
}