class AppointmentLinkedList{
public:
	void printAppointments();
	Appointment* getHeadAppointment();
	Appointment* getTailAppointment();
	void addAppointment(string name, int id);
	void cancelAppointment(string name, int id);
	void cancelAppointment(int day, int month, int time);
	AppointmentLinkedList();
	~AppointmentLinkedList();
private:
	Appointment* head;
	Appointment* tail;
};
