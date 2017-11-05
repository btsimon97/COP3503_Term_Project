class AppointmentLinkedList{
public:
	void printAppointment();
	Appointment* getHeadAppointment();
	Appointment* getTailAppointment();
	AppointmentLinkedList();
	~AppointmentLinkedList();
private:
	Appointment* head;
	Appointment* tail;
};