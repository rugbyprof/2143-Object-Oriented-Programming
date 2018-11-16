#pragma once
#include <iostream>
#include <string>

using namespace std;


const int MINUTE    = 60;
const int HOUR      = MINUTE * 60;
const int DAY       = HOUR * 24;
const int WEEK      = DAY * 7;
const int MONTH     = WEEK * 4;
const int YEAR      = WEEK * 52;

/**
 * @Class: TimeFormat
 * @Description:
 *     Accepts an integer time value and returns a string formatted as specified.
 */
class TimeFormat{
public:
    TimeFormat(){}

    /**
     * Possible formats: 
     *      Accepts any combination of : Y M W D H I S (year,  month, week, day, hour, minute, second)
     *      Example: HH:II:SS 
     *               III:SSS
     *               IIII
     *               SSSS
     *          
     */ 
    string getFormattedTime(string format,long seconds){
        string negative = "";
        string delimeter = "";

        if(seconds < 0){
            negative = "-";
            seconds *= -1;
        }

        int padY = 0;  //years
        int padM = 0;  //months
        int padD = 0;  //days
        int padH = 0;  //hours
        int padI = 0;  //minutes
        int padS = 0;  //seconds

        int Y = 0;  //years
        int M = 0;  //months
        int D = 0;  //days
        int H = 0;  //hours
        int I = 0;  //minutes
        int S = 0;  //seconds

        string result = "";

        for(int j=0;j<format.length();j++){
            switch(tolower(format[j])){
                case 'y': padY++; break;
                case 'm': padM++; break;
                case 'd': padD++; break;
                case 'h': padH++; break;
                case 'i': padI++; break;
                case 's': padS++; break;
                default: delimeter = format[j];
            }
        }

        if(padY>0){
            Y = getYears(seconds);
            seconds = remYears(seconds);
            result +=  _padVal(padY,Y) + delimeter;
            
        }
        if(padM>0){
            M = getMonths(seconds);
            seconds = remMonths(seconds);
            result += _padVal(padM,M) + delimeter;
        }
        if(padD>0){
            D = getDays(seconds);
            seconds = remDays(seconds);
            result += _padVal(padD,D) + delimeter;
        }
        if(padH>0){
            H = getHours(seconds);
            seconds = remHours(seconds);
            result += _padVal(padH,H) + delimeter;
        }
        if(padI>0){
            I = getMinutes(seconds);
            seconds = remMinutes(seconds);
            result += _padVal(padI,I) + delimeter;
        }
        if(padS>0){
            result += _padVal(padS,seconds);
        }

        return negative + result;

    }
    
private:

    string _padVal(int pad_size,long seconds){
        string sSeconds = "";

        for(int i=0;i<pad_size;i++){
            sSeconds += "0";
        }

        if(seconds == 0){
            return sSeconds;
        }

        int digits = getNumDigits(seconds);

        sSeconds = "";

        if(digits >= pad_size){
            return to_string(seconds);
        }else{
            pad_size = pad_size - digits;

            for(int i=0;i<pad_size;i++){
                sSeconds += "0";
            }
        }
        return sSeconds + to_string(seconds);

    }

    int getNumDigits(long seconds){
        int digits = 0;
        int divisor = 1;

        while((seconds / divisor) > 0){
            digits++;
            divisor *= 10;
        }
        return digits;
    }

    int getYears(int seconds){
        return seconds / YEAR;
    }

    int remYears(int seconds){
        return seconds % YEAR;
    }

    int getMonths(int seconds){
        return seconds / MONTH;
    }

    int remMonths(int seconds){
        return seconds % MONTH;
    }

    int getWeeks(int seconds){
        return seconds / WEEK;
    }

    int remWeeks(int seconds){
        return seconds % WEEK;
    }

    int getDays(int seconds){
        return seconds / DAY;
    }

    int remDays(int seconds){
        return seconds % DAY;
    }

    int getHours(int seconds){
        return seconds / HOUR;
    }

    int remHours(int seconds){
        return seconds % HOUR;
    }

    int getMinutes(int seconds){
        return seconds / MINUTE;
    }

    int remMinutes(int seconds){
        return seconds % MINUTE;
    }

};