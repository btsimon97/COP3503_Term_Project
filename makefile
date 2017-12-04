AppointmentManager: obj/sqlite.o obj/schedule.o obj/worker.o obj/vistor.o obj/appointment.o obj/main.o obj/backup.o obj/column.o obj/database.o obj/exception.o obj/statement.o obj/transaction.o obj/information.o
	g++ -o AppointmentManager obj/sqlite.o obj/schedule.o obj/worker.o obj/vistor.o obj/appointment.o obj/main.o obj/column.o obj/database.o obj/exception.o obj/statement.o obj/transaction.o obj/information.o
obj/schedule.o:
	g++ -c -std=c++11 -I Info_Management/include/ Info_Management/ScheduleManager.cpp -o obj/schedule.o
obj/worker.o:
	g++ -c -std=c++11 People_Management/Worker.cpp -o obj/worker.o
obj/vistor.o:
	g++ -c -std=c++11 People_Management/Visitor.cpp -o obj/vistor.o
obj/appointment.o:
	g++ -c -std=c++11 Appointments/Appointment.cpp -o obj/appointment.o
obj/information.o:
	g++ -c -std=c++11 -I Info_Management/include/ Info_Management/Information_Management.cpp -o obj/information.o
obj/main.o:
	g++ -c -std=c++11 -I Info_Management/include/ main.cpp -o obj/main.o
obj/backup.o:
	g++ -c -std=c++11 -I Info_Management/include/ Info_Management/Libraries/SQLiteCpp/Backup.cpp -o obj/backup.o
obj/column.o:
	g++ -c -std=c++11 -I Info_Management/include/ Info_Management/Libraries/SQLiteCpp/Column.cpp -o obj/column.o
obj/database.o:
	g++ -c -std=c++11 -I Info_Management/include/ Info_Management/Libraries/SQLiteCpp/Database.cpp -o obj/database.o
obj/exception.o:
	g++ -c -std=c++11 -I Info_Management/include/ Info_Management/Libraries/SQLiteCpp/Exception.cpp -o obj/exception.o
obj/statement.o:
	g++ -c -std=c++11 -I Info_Management/include/ Info_Management/Libraries/SQLiteCpp/Statement.cpp -o obj/statement.o
obj/transaction.o:
	g++ -c -std=c++11 -I Info_Management/include/ Info_Management/Libraries/SQLiteCpp/Transaction.cpp -o obj/transaction.o
obj/sqlite.o:
	gcc -c -I Info_Management/include/ Info_Management/Libraries/SQLite/sqlite3.c -o obj/sqlite.o
