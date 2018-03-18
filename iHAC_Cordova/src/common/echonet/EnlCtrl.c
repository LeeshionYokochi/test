// 
//  EnlCtrl.c
//
//  Created by Shion Lee Yokochi on 2017/11/26.
//  Copyright © 2017年 Shion Lee Yokochi. All rights reserved.
//

#include "EnlCtrl.h"

const int UECHO_TEST_SEARCH_WAIT_MTIME = 200;
//Echonet コントローラ変数
uEchoController *ctrl;

/**
 * @brief Echonet 初期化
 * Echonet コントローラの準備を行い，ローカルエリアのノード探索を行う
 * ノードが存在しない場合，偽の値を返す
 * @retval 初期化完了通知
 */
Boolean enlInitialize(){
    //Echonet_controllerの作成・起動
    ctrl = uecho_controller_new();
    if (!ctrl)
        return FALSE;
    if (!uecho_controller_start(ctrl))
        return FALSE;
    
    //ローカルエリア内のノードを探索
    uecho_controller_searchallobjects(ctrl);
    uecho_sleep(UECHO_TEST_SEARCH_WAIT_MTIME);
    return TRUE;
}

/**
 * @brief Echonet デバイスリスト取得
 * @retval Echonet デバイスリスト
 *
 * IPアドレスとオブジェクトコードを取得し，それらを元にEchonet用DBからデータを引っ張る
 */
const char *getEnlDeviceList(){
    uEchoNode *node;
    uEchoObject *obj;
    
    const char *deviceInfo;
    char bufferList[2048];
    char regDeviceList[1024] = "\"regDeviceList\":[";
    char unRegDeviceList[1024] = "\"unRegDeviceList\":[";
    unsigned long unRegDeviceListLength, regDeviceListLength;
    
        for (node = uecho_controller_getnodes(ctrl); node; node = uecho_node_next(node)) {
            if (uecho_node_getobjectcount(node) <= 0) {
                continue;
            }
            for (obj = uecho_node_getobjects(node); obj; obj = uecho_object_next(obj)) {
                //IPアドレス，オブジェクトコードを取得
                const char *ipAdd = uecho_node_getaddress(node);
                int objCode = uecho_object_getcode(obj);
                // objCodeの値がノードプロファイルオブジェクトでは無い場合
                if (objCode != nodeProfileObj) {
                    printf("search_IP : %s, search_objCode : %d\n",ipAdd, objCode);
                    //取得した情報を元にDBから関連データを取得
                    const char *nothingData = "";
                    deviceInfo = getEnlDeviceInfo(objCode);
                    if (strlen(deviceInfo) != strlen(nothingData)) {
                        //登録済みデバイスリストに追加
                        sprintf(bufferList, "{%s,\"ipAdd\":\"%s\",\"objCode\":\"%d\",\"protocol\":\"echonet\"},",deviceInfo, ipAdd, objCode);
                        strcat(regDeviceList, bufferList);
                    } else {
                        //未登録デバイスリストに追加
                        sprintf(bufferList, "{\"ipAdd\":\"%s\",\"objCode\":\"%d\",\"protocol\":\"echonet\"},", ipAdd, objCode); //malloc宣言した変数に入れ替え
                        strcat(unRegDeviceList,bufferList);
                    }
                }
            }
        }
    
    //Echonet_controllerの終了，削除
    uecho_controller_stop(ctrl);
    uecho_controller_delete(ctrl);
    
    // 返り値となる文字列の領域を確保
    regDeviceListLength = strlen(regDeviceList);
    unRegDeviceListLength = strlen(unRegDeviceList);
    char *enlJsonData = (char *)malloc( regDeviceListLength + unRegDeviceListLength + 1);
    // 登録済み・未登録機器リストを結合
    sprintf(enlJsonData, "%s],%s]", regDeviceList, unRegDeviceList);
    strcat(enlJsonData,"\0");
    return enlJsonData;
}

/**
 * @brief malloc 領域の機器リストを解放
 */
void freeEnlDeviceList(char *deviceListAdd)
{
    free(deviceListAdd);
}
