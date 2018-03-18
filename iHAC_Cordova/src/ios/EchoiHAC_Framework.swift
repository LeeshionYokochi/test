import Foundation

@objc(iHAC_Cordova) class iHAC_Cordova : CDVPlugin {
    func GetDeviceList(_ command: CDVInvokedUrlCommand) {
        var pluginResult = CDVPluginResult(
            status: CDVCommandStatus_ERROR
        )
        
        initialize()
        let msg = String(cString: getDeviceList())as? String ?? ""
        
        if msg.characters.count > 0 {
            pluginResult = CDVPluginResult(
                status: CDVCommandStatus_OK,
                messageAs: msg
            )
        }
        
        self.commandDelegate!.send(
            pluginResult,
            callbackId: command.callbackId
        )
    }
}
