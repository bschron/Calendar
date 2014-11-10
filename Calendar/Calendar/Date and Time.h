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
#endif /* defined(__Calendar__Date_and_Time__) */
