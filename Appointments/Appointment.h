//Class requires #include <string> to function.
class Appointment{
public:
	Appointment* getNextAppointment();
	Visitor* getVisitor();
	Worker* getWorker();
	int getMonth();
	int getDay();
	int getTimeSlot();
	void printAppointment();
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