/**
 * Vibrate when use answer a call which is outgoing
 * Author: yurenjimi@gmail.com
 * Version: 1.0
 * Date: 2010-09-09
 */

/**
* http://na.blackberry.com/eng/devjournals/resources/journals/jan_2005/api_spotlight_phone.jsp#phone_addPhoneListener
* A very good demo. you can extend it by yourself.; 0)
*/

//
package src;

import net.rim.blackberry.api.phone.*;
//import net.rim.device.api.ui.container.FlowFieldManager;
//import net.rim.device.api.ui.component.LabelField;
//import net.rim.device.api.ui.component.Status;
//import net.rim.device.api.ui.UiApplication;
import net.rim.device.api.system.*;

public final class BaseApp extends Application
  implements PhoneListener
{
    private boolean _isOutCall;
    static public void main(String[] args)
    {
        BaseApp plSample = new BaseApp();
        plSample.enterEventDispatcher();
    }
    
    private BaseApp()
    {
        //System.out.println("###PhoneCallListenerSample: Registering listener...");
        Phone.addPhoneListener(this);
        //System.out.println("###PhoneCallListenerSample:  Listener registered.");
        _isOutCall = false;
    }
    
    private void showPhoneEvent(String reason, int callId)
    {
        /*
        Status.show("Phone event: " + reason + "\n" + "CallID: " + callId,
            Bitmap.getPredefinedBitmap(Bitmap.EXCLAMATION), 4000,
            Status.GLOBAL_STATUS, true, false, 2);
        
        System.out.println("###PhoneCallListenerSample: Phone event: " +
          reason + " for callID: " + callId);
       */
    }
    
    // A call has been added to a conference call
    public void callAdded(int callId)
    {
        showPhoneEvent("Call Added", callId);
    }
    
    // User answered a call
    public void callAnswered(int callId)
    {
        showPhoneEvent("Call Answered", callId);
    }
    
    // Conference call established
    public void callConferenceCallEstablished(int callId)
    {
        showPhoneEvent("Conference Call Established", callId);
    }
    
    // Network indicates a connected event
    public void callConnected(int callId)
    {
        showPhoneEvent("Call Connected", callId);
                
        // Vibrate When use answered a call
        if (_isOutCall)
            net.rim.device.api.system.Alert.startVibrate(500);
        _isOutCall = false;
    }
    
    // Direct-connect call connected
    public void callDirectConnectConnected(int callId)
    {
        showPhoneEvent("DirectConnect Connected", callId);
    }
    
    // Direct-connect call disconnected
    public void callDirectConnectDisconnected(int callId)
    {
        showPhoneEvent("DirectConnect Disconnected", callId);
    }
    
    // Call disconnected
    public void callDisconnected(int callId)
    {
        showPhoneEvent("Call Disconnected", callId);
    }
    
    // User ended call
    public void callEndedByUser(int callId)
    {
        showPhoneEvent("Call Ended By User", callId);
    }
    
    // Call has been placed on "hold"
    public void callHeld(int callId)
    {
        showPhoneEvent("Call Held", callId);
    }
    
    // New call has arrived
    public void callIncoming(int callId)
    {
        showPhoneEvent("Call Incoming", callId);
    }
    
        
    // Outbound call initiated by the handheld
    public void callInitiated(int callid)
    {
        showPhoneEvent("Call Initiated", callid);
        _isOutCall = true;
    }
    
    // Call removed from a conference call
    public void callRemoved(int callId)
    {
        showPhoneEvent("Call Removed", callId);
    }
    
    // Call taken off of "hold"
    public void callResumed(int callId)
    {
        showPhoneEvent("Call Resumed", callId);
        _isOutCall = false;
    }
    
    // Call is waiting
    public void callWaiting(int callid)
    {
        showPhoneEvent("Call Waiting", callid);
    }
    
    // Conference call has been terminated
    // (all members disconnected)
    public void conferenceCallDisconnected(int callId)
    {
        showPhoneEvent("Conference Call Disconnected", callId);
    }
        
    
    // Call failed
    public void callFailed(int callId, int reason)
    {
        _isOutCall = false;
        /*
        String errMsg = "Call Failed due to ";

        // determine reason
        switch( reason )
        {
            case PhoneListener.CALL_ERROR_AUTHORIZATION_FAILURE:
                showPhoneEvent(errMsg + "Authorization Error", callId);
            break;

            case PhoneListener.CALL_ERROR_CALL_REPLACED_BY_STK:
                showPhoneEvent(errMsg + "Call Replaced By Stack", callId);
            break;

            case PhoneListener.CALL_ERROR_CONGESTION:
                showPhoneEvent(errMsg + "Congestion", callId);
            break;

            case PhoneListener.CALL_ERROR_CONNECTION_DENIED_BY_NETWORK:
                showPhoneEvent(errMsg + "Connection Denied", callId);
            break;

            case PhoneListener.CALL_ERROR_DUE_TO_FADING:
                showPhoneEvent(errMsg + "Fading", callId);
            break;

            case PhoneListener.CALL_ERROR_EMERGENCY_CALLS_ONLY:
                showPhoneEvent(errMsg + "Emergency Calls Only", callId);
            break;

            case PhoneListener.CALL_ERROR_FDN_MISMATCH:
                showPhoneEvent(errMsg + "FDN Mismatch", callId);
            break;

            case PhoneListener.CALL_ERROR_GENERAL:
                showPhoneEvent(errMsg + "General Error", callId);
            break;

            case PhoneListener.CALL_ERROR_HOLD_ERROR:
                showPhoneEvent(errMsg + "Hold Error", callId);
            break;

            case PhoneListener.CALL_ERROR_INCOMING_CALL_BARRED:
                showPhoneEvent(errMsg + "Incoming Call Barred", callId);
            break;

            case PhoneListener.CALL_ERROR_LOST_DUE_TO_FADING:
                showPhoneEvent(errMsg + "Lost Due To Fading", callId);
            break;

            case PhoneListener.CALL_ERROR_MAINTENANCE_REQUIRED:
                showPhoneEvent(errMsg + "Maintenance", callId);
            break;

            case PhoneListener.CALL_ERROR_NUMBER_NOT_IN_SERVICE:
                showPhoneEvent(errMsg + "Number Not In Service", callId);
            break;

            case PhoneListener.CALL_ERROR_NUMBER_UNOBTAINABLE:
                showPhoneEvent(errMsg + "Number Unobtainable", callId);
            break;

            case PhoneListener.CALL_ERROR_OUTGOING_CALLS_BARRED:
                showPhoneEvent(errMsg + "Outgoing Calls Barred", callId);
            break;

            case PhoneListener.CALL_ERROR_PLEASE_TRY_LATER:
                showPhoneEvent(errMsg + "Try Later", callId);
            break;

            case PhoneListener.CALL_ERROR_RADIO_PATH_UNAVAILABLE:
                showPhoneEvent(errMsg + "Radio Path Unavailable", callId);
            break;

            case PhoneListener.CALL_ERROR_SERVICE_CONFLICT:
                showPhoneEvent(errMsg + "Service Conflict", callId);
            break;

            case PhoneListener.CALL_ERROR_SERVICE_NOT_AVAILABLE:
                showPhoneEvent(errMsg + "Service Not Available", callId);
            break;

            case PhoneListener.CALL_ERROR_SUBSCRIBER_BUSY:
                showPhoneEvent(errMsg + "Subscriber Busy", callId);
            break;

            case PhoneListener.CALL_ERROR_SYSTEM_BUSY_TRY_LATER:
                showPhoneEvent(errMsg + "System Busy", callId);
            break;

            case PhoneListener.CALL_ERROR_TRY_AGAIN:
                showPhoneEvent(errMsg + "Try Again", callId);
            break;

            case PhoneListener.CALL_ERROR_USER_BUSY_IN_DATA:
                showPhoneEvent(errMsg + "User Busy In Data", callId);
            break;

            case PhoneListener.CALL_ERROR_USER_BUSY_IN_PRIVATE:
                showPhoneEvent(errMsg + "User Busy In Private", callId);
            break;

            case PhoneListener.CALL_ERROR_USER_NOT_AUTHORIZED:
                showPhoneEvent(errMsg + "Not Authorized", callId);
            break;

            case PhoneListener.CALL_ERROR_USER_NOT_AVAILABLE:
                showPhoneEvent(errMsg + "User Not Available", callId);
            break;

            case PhoneListener.CALL_ERROR_USER_NOT_REACHABLE:
                showPhoneEvent(errMsg + "User Not Reachable", callId);
            break;
    }*/
    
    }
}
