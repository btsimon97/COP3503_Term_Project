//
//  WorkerLinkedList.cpp
//  Group_Project
//
//  Created by Mark Lawrence on 11/7/17.
//  Copyright © 2017 Mark Lawrence. All rights reserved.
//

#include "WorkerLinkedList.hpp"
#include <string>
using namespace std;


WorkerLinkedList::WorkerLinkedList(){
    head = NULL;
    tail = NULL;
}

void WorkerLinkedList::printWorkerWeekSchedule(string name, int id, int month, int weekOfMonth){
    
}

Worker* WorkerLinkedList::getHeadWorker(){
    return head;
}

Worker* WorkerLinkedList::getTailWorker(){
    return tail;
}

WorkerLinkedList ~WorkerLinkedList(){
    Worker* currentWorker = head;
    while(currentWorker != NULL){
        Worker nextWorker = currentWorker->getNextWorker();
        delete currentWorker;
        currentWorker = nextWorker;
    }
}
