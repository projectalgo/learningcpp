//
//  FIFOTwoRW.h
//  LearningCPPProject
//
//  Created by Yeduguri, Amulya on 9/5/15.
//  Copyright (c) 2015 Yeduguri, Amulya. All rights reserved.
//

#ifndef __LearningCPPProject__FIFOTwoRW__
#define __LearningCPPProject__FIFOTwoRW__

#include <iostream>
#include <queue>
#include <string>
#include <boost/thread.hpp>

class FIFOTwoRW {
    
private:
    std::queue<std::string> myQ;
    boost::mutex queueMutex;//mutex for pusing into queue
    
    
    boost::condition_variable   data_ready_cond;//condition variable for communicating that data is ready
    boost::mutex                data_ready_mutex;//mutex to synchronize access to data_ready
    bool                        data_ready = false;
    
    //void pushAndPop(const char*);
    void addToQueue(const char*);
    void push(const char*, const int count);
    void pop();
 
public:
    FIFOTwoRW();
    void forkTwoThreads();
    
};

#endif /* defined(__LearningCPPProject__FIFOTwoRW__) */
