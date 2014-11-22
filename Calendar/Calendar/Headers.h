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
#define SearchHpSize 600
#define MainDir "/Documents/spyridonsCalendar"
#define MainCalendar "calendar"
#define CalendarFileExtension ".spyridon"
#define SearchingLimit 1000
#define NumberOfRecurrences 31

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

#include "Structs.h"

SearchTable *titleSearchTable;
SearchTable *descriptionSearchTable;
SearchTable *dateSearchTable;

#include "Main.h"
#include"Events Tree.h"
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
