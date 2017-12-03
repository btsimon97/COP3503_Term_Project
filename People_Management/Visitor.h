/*
 * Visitor.h
 *
 *  Created on: Nov 30, 2017
 *      Author: David
 */


#ifndef VISiTOR_H_
#define VISiTOR_H_
#include <string>

namespace std {

class Visitor {
private:
	std::string visitorName;
	int visitorID;
public:
	void printVisitorInfo();
	int getVisitorId();
	std::string& getVisitorName();
	Visitor(std::string name, int id);
};

}

#endif /* VISiTOR_H_ */
