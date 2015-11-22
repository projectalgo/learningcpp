//
//  FIFOTwoRW.cpp
//  LearningCPPProject
//
//  Created by Yeduguri, Amulya on 9/5/15.
//  Copyright (c) 2015 Yeduguri, Amulya. All rights reserved.
//

#include "FIFOTwoRW.h"
#include <boost/lexical_cast.hpp>
using namespace std;

FIFOTwoRW::FIFOTwoRW() {
 
}

/*
 *Push a string into queue
 *Acquire lock to update queue
 *Try acquiring lock to update condition variable(pass try_lo_lock to the constructor), need not be blocking 
 * as failing to lock indicates that other thread is updating the data_ready to true
 */
void FIFOTwoRW::push(const char* name, const int count) {
    string s(name);
    s += " " + boost::lexical_cast<std::string>(count);
    {
        boost::mutex::scoped_lock localLock(queueMutex);
        cout<<"Inserting "<<s<<endl;
        myQ.push(s);
    }
    {
        boost::unique_lock<boost::mutex> lock(data_ready_mutex, boost::try_to_lock);//unique _lock calls lock upon initialization, try_lock
        if(lock && !data_ready) {
            data_ready = true;
            data_ready_cond.notify_all();
        }

    }
}

/*
 *Read and pop from queue
 *Use scoped lock to wait on data ready.
 *Use lock to pop from queue
 */
void FIFOTwoRW::pop() {
    
    while(1) {
        //locks queueMutex access to queue
        boost::unique_lock<boost::mutex> lock(data_ready_mutex);
        if(!data_ready) {
            //wait will add this thread in the queue of threads waiting for conditional variable.
            //Wait also unlocks the mutex queueMutex until its notified, when it is notified it locked again
            data_ready_cond.wait(lock);//wait(data_ready_mutex);
        }
        {
            boost::mutex::scoped_lock localLock(queueMutex);
            while(!myQ.empty()){
                    cout<<myQ.front()<<endl;
                    myQ.pop();
            }
        }
        data_ready = false;
    }
    
}


/*
 *Each thread pushes 10 elements each
 */
void FIFOTwoRW::addToQueue(const char* name) {
    int count = 0;
    while(count<10) {
        count++;
        push(name,count);
    }
}

void FIFOTwoRW::forkTwoThreads() {
    cout<<"Parent Thread running\n";
    boost::thread t1(&FIFOTwoRW::addToQueue, this, "Thread A");
    boost::thread t2(&FIFOTwoRW::addToQueue, this, "Thread B");
    //boost::thread t3(&FIFOTwoRW::pop, this);
    pop();
    t1.join();
    t2.join();
    //t3.join();
    cout<<"Parent Thread done.\n";
    
}