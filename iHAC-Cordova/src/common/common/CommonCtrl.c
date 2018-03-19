//
//  CommonCtrl.c
//
//  Created by Shion Lee Yokochi on 2017/11/26.
//  Copyright © 2017年 Shion Lee Yokochi. All rights reserved.
//

#include "CommonCtrl.h"

/** 
 * @brief 初期化
 * @retval TRUE 初期化完了通知
 * @retval FALSE エラー通知
 */
Boolean initialize(){
    //Echonet Lite 初期化
    if (enlInitialize() != TRUE)
        return FALSE;
    
    //DB 初期化
    if (dbInitialize() != TRUE) {
        return FALSE;
    }
    return TRUE;
}

/**
 * @brief デバイスリスト取得
 * @retval デバイスリスト
 */
const char *getDeviceList(){
    // Echonetデバイスリスト取得
    const char *enlDeviceList = getEnlDeviceList();
    // 位置情報リスト取得
    const char *locationList = getLocationList();
    // 各種リストを一つに統一
    char *deviceList = (char *)malloc( strlen(enlDeviceList) + strlen(locationList) + 1);
    sprintf(deviceList, "{%s,%s}", enlDeviceList, locationList);
    strcat(deviceList,"\0");
    
    // mallocで確保した領域を解放
    freeEnlDeviceList(enlDeviceList);
    freeLocationList(locationList);
    
    return deviceList;
}
