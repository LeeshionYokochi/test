//
//  DBManager.h
//
//  Created by Shion Lee Yokochi on 2017/11/26.
//  Copyright © 2017年 Shion Lee Yokochi. All rights reserved.
//

#ifndef DBManager_h
#define DBManager_h

#ifndef Boolean
#define Boolean int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// DBファイル名
#define fileName "sq/iHAC_DB.db"

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "../sqlite/sqlite3.h"

Boolean dbInitialize();
const char *getEnlDeviceInfo(int objCode);
const char *getLocationList();
void freeDeviceInfo(char *deviceInfoAdd);
void freeLocationList(char *locationListAdd);


#endif /* DBManager_h */
