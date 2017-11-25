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

void addAppointment(string name, int id, int day, int month, int timeSlot, Worker* worker){
	if(this->slotFree(new Appointment (month, day, timeSlot, worker, name, id))){
		this->tail->setNextAppointment(new Appointment(month, day, timeSlot, worker, name, id));
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

void cancelAppointment(int day, int month, int time){
	Appointment* current = head;
	if(current->getMonth() == month && current->getDay() == day && current->getTimeSlot() == time){
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

bool AppointmentLinkedList:: slotFree(Appointment* attemptedAddition){
	current = this->head;
	while(current != NULL){
		if(*current == *attemptedAddition){
			return false;
		}
		current = current->getNextAppointment();
	}
	return true;
}
