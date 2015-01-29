#include <binder/IInterface.h>
#include <binder/IBinder.h>
#include <binder/Binder.h>

using namespace android;

class IMyLight : public IInterface {

public:
    DECLARE_META_INTERFACE(MyLight);

    virtual void flashOn(int32_t onMs, int32_t offMs, int32_t color) = 0;
    virtual void turnOff(void) = 0;
};

#define TRANSACTION_flashOn (IBinder::FIRST_CALL_TRANSACTION + 0)
#define TRANSACTION_turnOff (IBinder::FIRST_CALL_TRANSACTION + 1)