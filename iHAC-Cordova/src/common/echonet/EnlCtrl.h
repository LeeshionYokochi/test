//
//  EnlCtrl.h
//
//  Created by Shion Lee Yokochi on 2017/11/26.
//  Copyright © 2017年 Shion Lee Yokochi. All rights reserved.
//

#ifndef EnlCtrl_h
#define EnlCtrl_h

#ifndef Boolean
#define Boolean int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// ノードプロファイルオブジェクトコード
#define nodeProfileObj 0x0EF001

#include <stdio.h>
#include "uecho/uecho.h"
#include "../common/DBManager.h"

Boolean enlInitialize();
const char *getEnlDeviceList();
void freeEnlDeviceList(char* deviceListAdd);

#endif /* EnlCtrl_h */
