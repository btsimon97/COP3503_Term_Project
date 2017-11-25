//Class requires #include <string> to function.
class Appointment{
public:
	Appointment* getNextAppointment();
	void setNextAppointment(Appointment* nextAppointment);
	Visitor* getVisitor();
	Worker* getWorker();
	int getMonth();
	int getDay();
	int getTimeSlot();
	void printAppointment();
	//Used to check if an appointment slot is already full.
	bool operator == (const Appointment compared);
	Appointment(int month, int day, int time, Worker* worker, string visitorName, int visitorID);
	~Appointment();
private:
	int month;
	int day;
	int timeSlot;
	Visitor* visitor;
	Worker* worker;
	Appointment* nextAppointment;
};
