//
//  WorkerLinkedList.hpp
//  Group_Project
//
//  Created by Mark Lawrence on 11/7/17.
//  Copyright © 2017 Mark Lawrence. All rights reserved.
//

#ifndef WorkerLinkedList_hpp
#define WorkerLinkedList_hpp

#include <stdio.h>
#include <string>
using namespace std;

class WorkerLinkedList{
public:
    void printWorkerWeekSchedule(string name, int id, int month, int weekOfMonth);
    Worker* getHeadWorker();
    Worker* getTailWorker();
    ~WorkerLinkedList();
    

private:
    Worker* head;
    Worker* tail;
};

#endif /* WorkerLinkedList_hpp */
