#include <IMyLight.h>
#include <binder/Parcel.h>

#include <hardware/hardware.h>
#include <hardware/lights.h>

#undef LOG_TAG
#define LOG_TAG "MyLight"

using namespace android;

class BpMyLight : public BpInterface<IMyLight> {

public:
    BpMyLight(const sp<IBinder>& remote) : BpInterface<IMyLight>(remote) { }

    //We don't have to implement it
    //Since we want to call from AIDL
    virtual void flashOn(int32_t onMs, int32_t offMs, int32_t color) { }
    virtual void turnOff(void) { }
};
IMPLEMENT_META_INTERFACE(MyLight, "com.test.nativeservice.IMyLight");

class BnMyLight : public BnInterface<IMyLight> {

public:
    virtual status_t onTransact( uint32_t code,
                                 const Parcel& data,
                                 Parcel* reply,
                                 uint32_t flags = 0){
        ALOGD("BnMyLight::onTransact invoked");
        //CHECK_INTERFACE(IMyLight, data, reply);
        switch(code){
            case INTERFACE_TRANSACTION: {
                reply -> writeString16( IMyLight::getInterfaceDescriptor() );
                return NO_ERROR;
                } break;

            case TRANSACTION_flashOn: {
                int32_t _onMs, _offMs, _color;
                _onMs = data.readInt32();
                _offMs = data.readInt32();
                _color = data.readInt32();
                flashOn(_onMs, _offMs, _color);
                return NO_ERROR;
                } break;

            case TRANSACTION_turnOff: {
                turnOff();
                return NO_ERROR;
                } break;

            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }
};

class MyLightService : public BnMyLight {

private:
    hw_module_t *mModule;
    struct light_device_t *mNotifyDevice;

    int getModule(){
        if( hw_get_module(LIGHTS_HARDWARE_MODULE_ID, (hw_module_t const**)&mModule) != 0){
            ALOGE("Error getting hardware module");
            return -1;
        }
        return 0;
    }

    void getNotifyDevice(){
        if( (mModule -> methods -> open(mModule, LIGHT_ID_NOTIFICATIONS, (hw_device_t**)&mNotifyDevice)) != 0){
            ALOGE("Error getting notification device");
            mNotifyDevice = NULL;
        }else{
            ALOGI("Successfully get notification device");
        }
    }

public:
    MyLightService() {
        //Open hardware and devices
        if(getModule() == 0){
            getNotifyDevice();
        }
    }

    virtual void flashOn(int32_t onMs, int32_t offMs, int32_t color){
        if(mNotifyDevice != NULL){
            struct light_state_t lightMode;
            lightMode.color = (unsigned int)color;
            lightMode.flashMode = LIGHT_FLASH_TIMED;
            lightMode.flashOnMS = onMs;
            lightMode.flashOffMS = offMs;
            lightMode.brightnessMode = BRIGHTNESS_MODE_SENSOR;

            int err = mNotifyDevice -> set_light(mNotifyDevice, &lightMode);
            if(err == 0){
                ALOGI("set_light succeed");
            }else{
                ALOGE("set_light failed");
            }
        }
    }

    virtual void turnOff(){
        if(mNotifyDevice != NULL){
            struct light_state_t lightMode;
            lightMode.color = 0;
            lightMode.flashMode = LIGHT_FLASH_NONE;
            lightMode.brightnessMode = BRIGHTNESS_MODE_SENSOR;

            int err = mNotifyDevice -> set_light(mNotifyDevice, &lightMode);
            if(err == 0){
                ALOGI("turnOff succeed");
            }else{
                ALOGE("turnOff failed");
            }
        }
    }
};