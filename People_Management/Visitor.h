/*
 * Visitor.h
 *
 *  Created on: Nov 30, 2017
 *      Author: David
 */

#include <string>
using namespace std;
#ifndef VISITOR_H
#define VISITOR_H
class Visitor {
private:
	string visitorName;
	int visitorID;
public:
	int getVisitorID();
	string getVisitorName();
	Visitor(int id, string name);
};

#endif /* VISITOR_H */
