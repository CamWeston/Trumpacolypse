//
//  stopwatch.hpp
//  graphicsTesting
//
//  Created by Cam Weston on 12/4/16.
//  Copyright © 2016 Cam Weston. All rights reserved.
//

#ifndef stopwatch_hpp
#define stopwatch_hpp

#define _SCL_SECURE_NO_WARNINGS
#pragma warning(disable:4996) 
#include <time.h>
#include <stdio.h>

#include <ctime>
class Stopwatch{
public:
    Stopwatch();
    void start();
    void end();
    int timeElapsed();
private:
    time_t currentTime;
    struct tm *localTime;
    int day,month,year,startSecond,startMinute,startHour,endSecond,endMinute,endHour,totalSecondsElapsed,startTotalSeconds;
};




#endif /* stopwatch_hpp */
