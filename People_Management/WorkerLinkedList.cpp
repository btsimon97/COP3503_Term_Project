/*
 * WorkerLinkedList.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: David
 */

#include "WorkerLinkedList.h"

namespace std {
	 struct node
	  {
	    int data;
	    node *next;
	  };
class WorkerLinkedList() {
private:
	    node *head, *tail;
public:
	    WorkerLinkedList(){
	      head= NULL;
	      tail= NULL;
	    }
};

} /* namespace std */
