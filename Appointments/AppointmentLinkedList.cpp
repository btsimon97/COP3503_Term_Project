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

void addAppointment(string name, int id, int day, int month, int time, Worker* worker){
	this->tail->setNextAppointment(new Appointment(month, day, time, worker, name, id));
	this->tail = tail->getNextAppointment();
	if(this->head == NULL){
		this->head = this->tail;
	}
	//Can be used for debugging and confirmation of addition to user.
	cout << "Successfully added appointment." << endl;
	return;
}

void cancelAppointment(string name, int id){
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
