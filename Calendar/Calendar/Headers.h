//
//  Headers.h
//  calendar
//
//  Created by Bruno Chroniaris on 11/5/14.
//  Copyright (c) 2014 UNIUM automação. All rights reserved.
//

#ifndef calendar_Headers_h
#define calendar_Headers_h

#define Max 100
#define description 300
#define SearchTableSize 661
#define not_in_use -1
#define SearchHpSize 100
#define MainDir "/Documents/spyridonsCalendar"
#define MainCalendar "calendar"
#define CalendarFileExtension ".spyridon"
#define SearchingLimit 10
#define NumberOfRecurrences 31
#define ERROR -999999

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mach/mach_time.h>
#include <time.h>
#include <sys/time.h>
#include "/usr/local/Cellar/cunit/2.1-2/include/CUnit/Basic.h"

#include "Structs.h"

SearchTable *titleSearchTable;
SearchTable *descriptionSearchTable;
SearchTable *dateSearchTable;
int loadState, loadDelay;

#include "Main.h"
#include"Events List.h"
#include"Search Table.h"
#include"Binary Search Tree.h"
#include"Support Functions.h"
#include "Lists Management.h"
#include "Searching Heap.h"
#include "File Management.h"
#include "Date and Time.h"
#include"Output.h"
#include "User Interaction Module.h"
#include "Event Queue.h"
#include "Event Capsule.h"
#include "Object Priority Queue.h"
#include "Object List.h"

#include "Testing.h"
#include "AVL test cases.h"
#include "Priority Queue Test Cases.h"

#endif
