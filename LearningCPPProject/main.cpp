//
//  main.cpp
//  LearningCPPProject
//
//  Created by Yeduguri, Amulya on 9/5/15.
//  Copyright (c) 2015 Yeduguri, Amulya. All rights reserved.
//

#include <iostream>
#include <boost/thread.hpp>
//#include <boost/date_time.hpp>
#include "FIFOTwoRW.h"
using namespace std;

/*void workerFunc() {
    cout<<"Worker thread running"<<endl;
    boost::posix_time::seconds duration(5);
    boost::this_thread::sleep(duration);
    cout<<"Worker thread finished"<<endl;
    return;
}*/

int main() {
    
   /* cout<<"Main thread running"<<endl;
    boost::thread worker(workerFunc);
    cout<<"Main thread waiting"<<endl;
    worker.join();
    cout<<"Main thread done"<<endl;*/
    FIFOTwoRW f;
    f.forkTwoThreads();
    
    
    
    
    return 0;
}
/*
void worker() {
    
    boost::posix_time::seconds duration(3);
    cout<<"Worker thread: running"<<endl;
    boost::this_thread::sleep(duration);
    cout<<"Worker thread: finished"<<endl;
}

int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Main Thread running\n";
    
    boost::thread workerThread(worker);
    std::cout << "Main Thread waiting\n";
    workerThread.join();
    std::cout << "Main Thread Done\n";
    
    return 0;
}*/

