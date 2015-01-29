LOCAL_PATH :=   $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_LDLIBS += -L$(LOCAL_PATH)/lib
LOCAL_LDLIBS += -lbinder -lcutils -lutils -llog -lhardware

LOCAL_SRC_FILES +=  service/mainService.cpp
LOCAL_MODULE := myLightService

#Build native service
include $(BUILD_EXECUTABLE)

