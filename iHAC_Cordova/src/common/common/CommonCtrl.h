//
//  CommonCtrl.h
//
//  Created by Shion Lee Yokochi on 2017/11/26.
//  Copyright © 2017年 Shion Lee Yokochi. All rights reserved.
//

#ifndef CommonCtrl_h
#define CommonCtrl_h

#ifndef Boolean
#define Boolean int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#include <stdio.h>
#include "../echonet/EnlCtrl.h"
#include "DBManager.h"

Boolean initialize();
const char *getDeviceList();

#endif /* CommonCtrl_h */
