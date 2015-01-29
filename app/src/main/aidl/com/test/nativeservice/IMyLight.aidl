// IMyLight.aidl
package com.test.nativeservice;

// Declare any non-default types here with import statements

interface IMyLight {

    void flashOn(int onMs, int offMs, int color);
    void turnOff();
}
