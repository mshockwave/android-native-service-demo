#include <MyLightService.h>

#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

using namespace android;

int main(int argc, char **argv){
    //Register Service
    defaultServiceManager() -> addService(String16("my_light"), new MyLightService());

    //Start thread pool and join to it
    ProcessState::self() -> startThreadPool();
    ALOGI("Service my_light started");
    IPCThreadState::self() -> joinThreadPool();

    return 0;
}