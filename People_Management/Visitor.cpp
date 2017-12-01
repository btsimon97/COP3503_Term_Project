/*
 * Visitor.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: David
 */

#include "Visitor.h"

namespace std {

class Visitor {
private:
	std::string visitorName;
	int visitorID;
public:
	void printVisitorInfo();
	int getVisitorId() const {
		return visitorID;
	}
	const std::string& getVisitorName() const {
		return visitorName;
	}
	Visitor(std::string name, int id);
};
}

