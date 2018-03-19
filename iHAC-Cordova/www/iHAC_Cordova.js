var exec = require('cordova/exec');

exports.GetDeviceList = function(arg0, success, error) {
    exec(success, error, "iHAC_Cordova", "GetDeviceList", [arg0]);
};
