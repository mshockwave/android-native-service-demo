package com.test.nativeservice;

import android.graphics.Color;
import android.os.Handler;
import android.os.IBinder;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;


public class MainActivity extends ActionBarActivity {
    private static final String TAG = "MainActivity";

    private IMyLight mMyLight = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initBinder();
        if(mMyLight == null){
            Log.e(TAG, "Get MyLight interface failed");
        }else{
            Log.i(TAG, "Successfully get MyLight interface");
        }
    }

    private void initBinder(){
        IBinder serviceBinder = ServiceManager.getService("my_light");
        if(serviceBinder == null){
            Log.e(TAG, "Get service binder failed");
        }else{
            Log.i(TAG, "Get service binder");
            mMyLight = IMyLight.Stub.asInterface(serviceBinder);
        }
    }

    public void startBlinkingOnClick(View v){
        if(mMyLight == null) return;
        try {
            mMyLight.flashOn(50, 500, Color.GREEN);
        } catch (RemoteException e) {
            Log.e(TAG, "Blinking failed");
            e.printStackTrace();
        }
    }
    public void stopLighting(View v){
        if(mMyLight == null) return;
        try {
            mMyLight.turnOff();
        } catch (RemoteException e) {
            Log.e(TAG, "Turning off failed");
            e.printStackTrace();
        }
    }

}
