#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "TimeFormat.h"


/**
 * @Name: Counter
 * @Description:
 *      This class represents a simple counter that can be provided a start and end time. It would count
 *      up or down, and stop counting when it reaches its limit. If no limit is set, LONG_MAX is used
 * @Extends: 
 *      public TimeFormat
 *      public sf::Clock
 *  
 */
class Counter : public TimeFormat, public sf::Clock{
private:
    long StartVal;      // Starting clock value (e.g 0, -100 , 1000 , 867, etc.)
    long StopVal;       // Stopping value (when clock is finished) (e.g 0, -100 , 1000 , 867, etc.)
    string Format;      // Format to return clock: HH:MM , MM:SS, SS, SSS, SSSS , MM:SS:mm (default SS)
    bool Finished;      // Has clock reached its limit
    string ClockString; // String version of clock value 
    bool Increment;


    /**
     * @Name: _init
     * @Description: 
     *     Common init function for all overloaded constructors
     * @Params:
     * 
     * start <long> : starting value for counter
     * stop <long> : ending value for counter
     * format <string> : what format to return counter in
     */
    void _init(long start,long stop,string format){
        StartVal = start;
        StopVal = stop;
        Format = format;
        Increment = true;  
        if(start>stop){
            Increment = false;
        }

        restart(); // sf::Clock method
    }

public:
    /**
     * Default Constructor
     * @Params: None
     */
    Counter(){
        _init(0,LONG_MAX,"SS");
    }

    /**
     * Constructor
     * @Params:
     *     start <long>    : starting value for counter
     *     stop <long>     : ending value for counter
     *     format <string> : format to print counter 
     */
    Counter(long start,long stop,string format="SS"){
        _init(start,stop,format);
    }

    /**
     * @Name: setLimits
     * @Params: 
     *     start <long> : starting counter value
     *     stop <long> : ending counter value
     */
    void setLimits(long start,long stop){
        StartVal = start;
        StopVal = stop;
        _init(start,stop,Format);
    }

    /**
     * @Name: setFormat - Allows user to pick format SSS, HHMMSS, SS, DDHHMMSS, ETC .
     *                    Not all implemented in format class. You can do that.
     * @Params: 
     *     format <string> : pick your format
     */
    void setFormat(string format){
        Format = format;
        cout<<Format<<endl;
    }

    /**
     * @Name: getCurrent
     * @Params: None
     * @Returns: Formatted string 
     */
    string getCurrent(){
        
        if(Finished){
            return ClockString;
        }

        long current;

        if(Increment){
                      // sf::Clock method
            current = getElapsedTime().asSeconds() + StartVal;
            if (current >= StopVal){
                Finished = true;
            }
        }else{
                                // sf::Clock method
            current = StartVal - getElapsedTime().asSeconds();
            if (current <= StopVal){
                Finished = true;
            }
        }

        ClockString = getFormattedTime(Format,current);

        return ClockString;
    }

    /**
     * @Name: isFinished
     * @Description: Has the counter reached the stopping value
     * @Params: None
     * @Returns: bool true = counter has finished
     */
    bool isFinished(){
        return Finished;
    }

    /**
     * @Name: resetCounter
     * @Description: Restarts counter to initial value
     * @Params: None
     * @Returns: None
     */
    void resetCounter(){
        restart(); // sf::Clock method
    }
};