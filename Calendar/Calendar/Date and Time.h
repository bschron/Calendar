//
//  Date and Time.h
//  Calendar
//
//  Created by Bruno Chroniaris on 11/9/14.
//  Copyright (c) 2014 Universidade Federal De Alagoas. All rights reserved.
//

#ifndef __Calendar__Date_and_Time__
#define __Calendar__Date_and_Time__

#include "Headers.h"

/*Takes a pointer to a Date structure and attributtes the current time values to it. Allocates a new Date if the provided pointer is NULL and if there is some failure attributing the current time, returns a Date with empty values flags.*/
Date* getDate (Date *date);
/*takes two pointers to Date as argument, returns a pointer to the furthest in time date, from both. Returns NULL if any of the provided pointers is NULL. returns pointer to date2 if both dates are equal*/
Date* maxDate (Date *date1, Date *date2);
/*takes two pointers to Date as argument, returns a pointer to the less furthest in time date, from both. Returns NULL if any of the provided pointers is NULL. returns pointer to date2 if both dates are equal*/
Date* minDate (Date *date1, Date *date2);
/*takes a integer representing a year as a argument and returns 1 if it's a leap year, else, returns 0*/
int leapYear (int year);
/*takes two integers as argument, the first is the less year and the other is the greater year, returns a int with the number of leap years between both. if one or more of the years provided as an argument is a leap year it self will not add to that number, only the years BETWEEN*/
int leapsYearsBetween (int year1, int year2);
/*takes a integer as an argument, representing a month of the year, returns the number of days on that month. Wont even consider leap years. If month is invalid, returns -1*/
int daysInMonth (int month);
/*takes two integers as argument, representing two months of the year and returns the number of days BETWEEN them. the first argument must be the first month , the other must be the second month. Does not count the days in the month.*/
int daysBetweenMonths (int month1, int month2);
/*takes two integers as argument, the first representing the less year and the second the furthest year, will also count leap years days. Only count days BETWEEN years, not days from the provided years. returns the nubmer of days between that years.*/
int daysBetweenYears (int year1, int year2);
/*takes two Dates as argument, returns a int with the number of days between those two dates. if any of the dates is NULL, will return -1. Returns 0 if dates are both equal*/
int daysTimeDistance (Date *date1, Date *date2);
/*takes a integer representing a year as argument, returns the century number of that year. If the year is lesser than 100, returns -1.*/
int centuryNumber (int year);
/*takes a pointer to a string and a pointer do a Date as argument. prints the name of the day of week of that date to the provided char pointer and returns the weekday value as a int. returns -1 if the pointer to Date is NULL. Won't print the day fo the week to str if the provided pointer to str is NULL*/
int dayOfWeek (char *dest, Date *date);
/*takes a integer representing the month and another integer representing the year as argument, returns a integer representing the month table number of that month. returns -1 if provided arguments are invalid.*/
int monthTableNumber (int month, int year);
/*takes a pointer to a str and a integer representing a day of the week as a argument. prints the day of the week to the provided pointer to str. prints a "" empty str if it's a invalid day*/
void weekDayIntToStr (char *dest, int day);
/*takes a pointer to a str and a integer that represents the month, prints the name of the day on the provided strin str. If the pointer is NULL, returns without changes. If the month nubmer is invalid, prints "" to str*/
void monthIntToStr (char *dest, int month);
/*takes a pointer to Date as argument, returns the number of remaining days in that week. Returns -1 if provided pointer is NULL;*/
int remainingDaysInWeek (Date *date);
/*takes a pointer to Date as argument, pulls it's value to next day and returns a pointer to it. Returns NULL if provided pointer is NULL;*/
Date* increaseDate (Date *date);
/*takes a pointer to Date as argument, returns the number of remaining days in that month. Returns -1 if provided pointer is NULL;*/
int remainingDaysInMonth (Date *date);
/*takes a pointer to Date and a integer as argument. This function calls increaseDate(), increases the provided Date by one and recursively repeats the process, until the Date is increased by the provided n of days. This function returns the date unchanged if the provided n is 0 and returns NULL if the provided pointer to Date is NULL.*/
Date* increaseDateByNDays (Date *date, int n);
/*Takes a pointer to integer and a integer as argument. The pointer to integer must be a pointer to a at least 7 positions array, that has all days marked with 1 or 0 as ocurrence flags. The integer represents the number of the day of week of the nextDay. nextDay must never be the current day, because if current day is marked as 1, the function will return the currentDay. The function returns the number of the day in the week when this event is next gonna occur.*/
int nextDayOfWeekToOccur (int *frequency, int nextDay);
/*takes a pointer to Date and a integer as argument. The integer represents a day of week, thi function will increase the day of week and recursively repeats the process until the day of week is equal to the provided n. If the provided pointer to Date is NULL, will get the current time of the computer. Returns the provided pointer to date unchanged if the provided integer is not a valid day of week.*/
Date* advanceToNextNWeekDay (Date *date, int n);
/*Takes a pointer to integer and a pointer to Date as argument. The pointer to integer must be a pointer to a at least 31 positions array, that has all days marked with 1 or 0 as ocurrence flags. The Date represents the current day. This functions increases the provided date recursively until it represents a ocurrence day marked by the provided frequency table and returns it. If the provided pointer to Date is NULL, will get the computers current time. */
Date* nextDayOfMonthToOccur (int *frequency, Date *current);
/*Takes a pointer to integer and a pointer to Date as argument. The pointer to integer must be a array with at least 2 positions that is filled with dd/mm. The frequency positions represent the date of year when this event will occur. The provided Date will be increased until it maches the date provided by the frequency array. Returns a pointer to the Date. */
Date* nextDayOfYearToOccur (int *frequency, Date *current);
/*Takes a pointer to Date as argument. Compares provided date with current time and returns 1 if date has passes and 0 if not. Retuns 0 if provided pointer to Date is NULL.*/
int passedDate (Date *date);
/*Takes a integer representing the event recurrency and a pointer to a integer array representing the event frequency. Calculates when is the next ocurrency of the event, from the current date, and returns a Date to that occurrence.*/
Date nextTimeToOccur (int recurrency, int *frequency);
/*Takes two pointer to Date as arguments. Calculates and returns the number of days between those two dates. returns -1 if any of provided pointer is NULL. Returns 0 if first pointer is equal to the second pointer.*/
int daysBetweenDates (Date *first, Date *second);

#endif /* defined(__Calendar__Date_and_Time__) */
