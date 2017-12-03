/*
 * Visitor.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: David
 */

#include "Visitor.h"

using namespace std;

Visitor::Visitor(int id, string name){
	this->visitorName = name;
	this->visitorID = id;
}

int Visitor::getVisitorID(){
	return visitorID;
}

string Visitor::getVisitorName(){
	return visitorName;
}

