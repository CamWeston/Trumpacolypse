//
//  stopwatch.cpp
//  graphicsTesting
//
//  Created by Cam Weston on 12/4/16.
//  Copyright © 2016 Cam Weston. All rights reserved.
//

#include "stopwatch.hpp"
#include <iostream>
using namespace::std;


Stopwatch::Stopwatch(){
    cout << "Stopwatch created" << endl;
}
void Stopwatch::start(){
    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time
    day    = localTime->tm_mday;
    month  = localTime->tm_mon + 1;
    year   = localTime->tm_year + 1900;
    startHour   = localTime->tm_hour;
    startMinute = localTime->tm_min;
    startSecond = localTime->tm_sec;

	
    startTotalSeconds = (startHour * 60 * 60) + (startMinute * 60) + startSecond;
    
}
void Stopwatch::end(){
    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time
    endHour = localTime->tm_hour;
    endMinute = localTime->tm_min;
    endSecond = localTime->tm_sec;
   
}
int Stopwatch::timeElapsed(){
    time( &currentTime );                   // Get the current time
    localTime = localtime( &currentTime );  // Convert the current time to the local time
    int currentHour = localTime->tm_hour;
    int currentMinute = localTime->tm_min;
    int currentSecond = localTime->tm_sec;
    totalSecondsElapsed =((currentHour * 60 * 60) + (currentMinute * 60) + currentSecond) - startTotalSeconds;
    
    return totalSecondsElapsed;
}