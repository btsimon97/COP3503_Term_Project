class AppointmentLinkedList{
public:
	void printAppointments();
	Appointment* getHeadAppointment();
	Appointment* getTailAppointment();
	void setHeadAppointment(Appointment* head);
	void setTailAppointment(Appointment* tail);
	//Add and cancel functions added to the linked list different from UML diagram because they seemed more 
	//appropriate in the AppointmentLinkedList class.
	//To add an appointment, the class needs a date and worker as well as visitor information. Changed from UML
	//diagram.
	void addAppointment(string name, int id, int day, int month, int time, Worker* worker);
	void cancelAppointment(string name, int id);
	void cancelAppointment(int day, int month, int time);
	AppointmentLinkedList();
	~AppointmentLinkedList();
private:
	Appointment* head;
	Appointment* tail;
};
