//
//  DBManager.c
//
//  Created by Shion Lee Yokochi on 2017/11/26.
//  Copyright © 2017年 Shion Lee Yokochi. All rights reserved.
//

#include "DBManager.h"

// DBオブジェクト
sqlite3 *pDB = NULL;


/**
 * @brief DB 初期化
 * DB内にテーブルが存在しない場合作成する
 *
 * @retval TRUE 初期化完了通知
 * @retval FALSE エラー通知
 */
Boolean dbInitialize(){
    char *errMsg = NULL;
    int err = 0;
    
    // DBファイルが存在または作成されると 0（SQLITE_OK）を受け取る
    if ((err = sqlite3_open(fileName, &pDB)) != SQLITE_OK) {
        return FALSE;
    }
    
    // テーブルが存在しない場合，作成
    err = sqlite3_exec(pDB,
                       "CREATE TABLE IF NOT EXISTS enl_db (id INTEGER PRIMARY KEY, deviceName CHAR(32), locationId INTEGER, deviceType CHAR(32), objCode INTEGER)",
                       NULL, NULL, &errMsg);
    if (err != SQLITE_OK) {
        sqlite3_free(errMsg);
        errMsg = NULL;
        return FALSE;
    }
    
    err = sqlite3_exec(pDB,
                       "CREATE TABLE IF NOT EXISTS location_db (locationId INTEGER PRIMARY KEY, locationName CHAR(32))",
                       NULL, NULL, &errMsg);
    if (err != SQLITE_OK) {
        sqlite3_free(errMsg);
        errMsg = NULL;
        return FALSE;
    }
    
    if ((err = sqlite3_close(pDB)) != SQLITE_OK)
        return  FALSE;
    
    return TRUE;
}


/**
 * @brief 登録済みデータを取得
 * 引数で与えられたデータを元にDBを検索する
 * 既に登録されていた場合，関連データを返す
 * @retval 関連データ
 */
const char *getEnlDeviceInfo(int objCode){
    int deviceId, locationId, db_objeCode;
    const unsigned char *deviceName, *deviceType;
    char bufDeviceInfo[512] = "";
    
    int err = sqlite3_open(fileName, &pDB);
    if (err != SQLITE_OK) {
        return FALSE;
    }
    // ステートメントオブジェクト
    sqlite3_stmt *pStmt = NULL;
    // ステートメントの用意
    err = sqlite3_prepare_v2(pDB,
                                 "SELECT * FROM enl_db", 64,
                                 &pStmt, NULL);
    
    if (err != SQLITE_OK) {
        return FALSE;
    } else {
        // データの抽出
        while (SQLITE_ROW == (err = sqlite3_step(pStmt))) {
            deviceId = sqlite3_column_int(pStmt, 0);
            deviceName = sqlite3_column_text(pStmt, 1);
            locationId = sqlite3_column_int(pStmt, 2);
            deviceType = sqlite3_column_text(pStmt, 3);
            db_objeCode = sqlite3_column_int(pStmt, 4);
            
            if (objCode == db_objeCode) {
                sprintf(bufDeviceInfo, "\"deviceId\":\"%d\",\"deviceName\":\"%s\",\"locationId\":\"%d\",\"deviceType\":\"%s\"", deviceId, deviceName, locationId, deviceType);
                break;
            }
        }
        if (err != SQLITE_DONE) {
            return FALSE;
        }
    }
    
    // ステートメントの解放
    sqlite3_finalize(pStmt);
    // DBのクローズ
    err = sqlite3_close(pDB);
    if (err != SQLITE_OK) {
        return FALSE;
    }
    
    char *deviceInfo = (char *)malloc( strlen(bufDeviceInfo) + 1);
    sprintf(deviceInfo, "%s", bufDeviceInfo);
    return deviceInfo;
}

/**
 * @brief 位置情報リストを取得
 * @retval 位置情報リスト
 */
const char *getLocationList(){
    int locationId;
    const unsigned char *locationName;
    char bufLocationList[256] = "\"locationList\":[", buffer[256];
    
    int err = sqlite3_open(fileName, &pDB);
    if (err != SQLITE_OK) {
        return FALSE;
    }
    // ステートメントオブジェクト
    sqlite3_stmt *pStmt = NULL;
    // ステートメントの用意
    err = sqlite3_prepare_v2(pDB,
                             "SELECT * FROM location_db", 64,
                             &pStmt, NULL);
    
    if (err != SQLITE_OK) {
        return FALSE;
    } else {
        // データの抽出
        while (SQLITE_ROW == (err = sqlite3_step(pStmt))) {
            locationId = sqlite3_column_int(pStmt, 0);
            locationName = sqlite3_column_text(pStmt, 1);
            sprintf(buffer, "{\"locationId\":\"%d\",\"locationName\":\"%s\"},", locationId, locationName);
            strcat(bufLocationList,buffer);
        }
        if (err != SQLITE_DONE) {
            return FALSE;
        }
    }
    
    // ステートメントの解放
    sqlite3_finalize(pStmt);
    // DBのクローズ
    err = sqlite3_close(pDB);
    if (err != SQLITE_OK) {
        return FALSE;
    }
    
    char *locationList = (char *)malloc( strlen(bufLocationList) + 1);
    sprintf(locationList, "%s]", bufLocationList);
    return locationList;
}

/**
 * @brief malloc 領域の関連データを解放
 */
void freeDeviceInfo(char *deviceInfoAdd)
{
    free(deviceInfoAdd);
}

/**
 * @brief malloc 領域の位置情報リストを解放
 */
void freeLocationList(char *locationListAdd)
{
    free(locationListAdd);
}
