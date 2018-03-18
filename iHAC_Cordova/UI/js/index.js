/* 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
var app = {
    // Application Constructor
    initialize: function() {
        document.addEventListener('deviceready', this.onDeviceReady.bind(this), false);
    },

    // deviceready Event Handler
    //
    // Bind any cordova events here. Common events are:
    // 'pause', 'resume', etc.
    onDeviceReady: function() {
        this.receivedEvent('deviceready');
        
        iHAC_Cordova.
        GetDeviceList(
                      'Plugin Ready!',
                      function(msg) {
                        //JSON形式の文字列をオブジェクトとして返す
                        var setText = "";
                        var data = eval("("+msg+")");
                      
                      
                        // 登録済みデバイスの個数
                        var regDeviceCount = 0;
                        for (var i=0; i<data.regDeviceList.length; i++) {
                            regDeviceCount++;
                        }
                      
                        // 登録済みデバイス表示
                        for (var i=0; i<data.locationList.length; i++) {
                            var deviceCount = 0;
                      
                            // 部屋のアイコン
                            var locationTypeClass = '';
                            switch (data.locationList[i].locationName) {
                                case 'リビング':
                                    locationTypeClass = 'fa-home';
                                    break;
                                case '寝室':
                                    locationTypeClass = 'fa-bed';
                                    break;
                            }
                      
                            // 部屋名
                            setText += '<h2 class="regDevice"><i class="fa ' + locationTypeClass + '"></i>&nbsp;' + data.locationList[i].locationName + '</h2>';
                      
                            setText += '<div class="list-group">';
                            for (var j=deviceCount; j<regDeviceCount; j++) {
                                if (data.regDeviceList[j].locationId != data.locationList[i].locationId) {
                                    continue;
                                }
                      
                                // デバイスのアイコン
                                var deviceTypeClass = '';
                                switch (data.regDeviceList[j].deviceType) {
                                    case 'server':
                                        deviceTypeClass = 'fa-server';
                                        break;
                                    case 'television':
                                        deviceTypeClass = 'fa-television';
                                        break;
                                    case 'recorder':
                                        deviceTypeClass = 'fa-hdd-o';
                                        break;
                                    case 'airConditioner':
                                        deviceTypeClass = 'fa-sun-o';
                                        break;
                                    case 'airCleaner':
                                        deviceTypeClass = 'fa-sun-o';
                                        break;
                                    case 'light':
                                        deviceTypeClass = 'fa-lightbulb-o';
                                        break;
                                }
                      
                      
                                // アイコン，デバイス名を表示
                                setText += '<a class="list-group-item" href=""><i class="fa ' + deviceTypeClass + ' fa-fw"></i>&nbsp; ' + data.regDeviceList[j].deviceName + '</a>';
                                deviceCount++;
                            }
                            setText += '</div>';
                        }
                      
                      
                      // 未登録デバイスを表示
                      setText += '<h2 class="question">未登録デバイス</h2><div class="list-group">';
                      for (var i=0; i<data.unRegDeviceList.length; i++) {
                        setText += '<a class="list-group-item" href="">' + data.unRegDeviceList[i].ipAdd + '</a>';
                      }
                      
                      document
                      .getElementById('deviceready')
                      .querySelector('.received')
                      .innerHTML = setText;
                      },
                      function(err) {
                        document
                        .getElementById('deviceready')
                        .innerHTML = '<p class="event received">' + err + '</p>';
                      }
                      );
        },

        // Update DOM on a Received Event
        receivedEvent: function(id) {
        var parentElement = document.getElementById(id);
        var receivedElement = parentElement.querySelector('.received');

        receivedElement.setAttribute('style', 'display:block;');

        console.log('Received Event: ' + id);
    }
};

app.initialize();
